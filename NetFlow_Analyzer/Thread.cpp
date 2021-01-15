#include "Thread.h"
#include <QtDebug>

/*以太网帧头格式结构体 14个字节*/
typedef struct ether_header {
	unsigned char ether_dhost[6];
	unsigned char ether_shost[6];
	unsigned short ether_type;
}ETHER_HEADER, *PETHER_HEADER;

struct MAC
{
	unsigned char d1;
	unsigned char d2;
	unsigned char d3;
	unsigned char d4;
	unsigned char d5;
	unsigned char d6;
};
struct IP
{
	unsigned char d1;
	unsigned char d2;
	unsigned char d3;
	unsigned char d4;
};

/*以ARP字段结构体 28个字节*/
typedef struct arp_header {
	unsigned short arp_hrd;
	unsigned short arp_pro;
	unsigned char arp_hsize;
	unsigned char arp_psize;
	unsigned short arp_op;
	MAC arp_senderMAC;
	IP arp_senderIP;
	MAC arp_targetMAC;
	IP arp_targetIP;
}ARP_HEADER, *PARP_HEADER;

/*ARP报文结构体 42个字节*/
typedef struct arp_packet {
	ETHER_HEADER etherHeader;
	ARP_HEADER   arpHeader;
}ARPPACKET, *PARPPACKET;

/*IPv4报头结构体 20个字节*/
typedef struct ipv4_header {
	unsigned char ipv4_hl : 4;
	unsigned char ipv4_ver : 4;
	unsigned char ipv4_stype;
	unsigned short ipv4_plen;
	unsigned short ipv4_pidentify;
	unsigned short ipv4_flag_offset;
	unsigned char ipv4_ttl;
	unsigned char ipv4_pro;
	unsigned short ipv4_crc;
	IP  ipv4_sourpa;
	IP  ipv4_destpa;
}IPV4_HEADER, *PIPV4_HEADER;

/*IPv6报头结构体 40个字节*/
typedef struct ipv6_header {
	u_short ipv6_ver_hl_priority;
	u_short ipv6_lable;//4+8+20
	u_short ipv6_plen;
	u_char  ipv6_nextheader;
	u_char  ipv6_limits;
	in6_addr ipv6_sourpa;
	in6_addr ipv6_destpa;
}IPV6_HEADER, *PIPV6_HEADER;

/*UDP报头结构体 8个字节*/
typedef struct udp_header {
	u_short udp_sourport;
	u_short udp_destport;
	u_short udp_hlen;
	u_short udp_crc;
}UDP_HEADER, *PUDP_HEADER;

/*TCP报头结构体 20个字节*/
typedef struct tcp_header {
	u_short tcp_sourport;
	u_short tcp_destport;
	u_long  tcp_seqnu;
	u_long  tcp_acknu;
	u_char  tcp_hlen;
	u_char  tcp_reserved;
	u_short tcp_window;
	u_short tcp_chksum;
	u_short tcp_urgpoint;
}TCP_HEADER, *PTCP_HEADER;

//TCP数据报分析
void Thread::TCP_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	TCP_HEADER *tcp_protocol = (PTCP_HEADER)(packet_data + 14 + 20);

	u_short tcp_destport = ntohs(tcp_protocol->tcp_destport);
	u_char  tcp_reserved = tcp_protocol->tcp_reserved;
	TCP_info*tcp_info = new TCP_info;
	//printf("----------- TCP协议    -----------\n");
	//printf("源端口：");
	tcp_info->tcp_sourport = ntohs(tcp_protocol->tcp_sourport);
	//printf("%d\n", ntohs(tcp_protocol->tcp_sourport));
	//printf("目的端口：");
	tcp_info->tcp_destport = tcp_destport;
	//printf("%d\n", tcp_destport);
	/*switch (tcp_destport)
	{
	case 80:
		printf("上层协议：HTTP协议\n");
		break;
	case 21:
		printf("上层协议：FTP协议\n");
		break;
	case 23:
		printf("上层协议：TELNET协议\n");
		break;
	case 25:
		printf("上层协议：SMTP协议\n");
		break;
	case 110:
		printf("上层协议POP3协议\n");
		break;
	default:
		break;
	}*/
	tcp_info->tcp_seqnu = ntohl(tcp_protocol->tcp_seqnu);
	tcp_info->tcp_acknu = ntohl(tcp_protocol->tcp_acknu);
	tcp_info->tcp_hlen = tcp_protocol->tcp_hlen;
	tcp_info->tcp_reserved = tcp_reserved;
	//printf("序列码：%u\n", ntohl(tcp_protocol->tcp_seqnu));
	//printf("确认号：%u\n", ntohl(tcp_protocol->tcp_acknu));
	//printf("首部保留长度：%d\n", tcp_protocol->tcp_hlen);
	/*printf("标记：");
	if (tcp_reserved & 32)
		printf(" UGR");
	if (tcp_reserved & 16)
		printf(" ACK");
	if (tcp_reserved & 8)
		printf(" PSH");
	if (tcp_reserved & 4)
		printf(" RST");
	if (tcp_reserved & 2)
		printf(" SYN");
	if (tcp_reserved & 1)
		printf(" FIN");
	printf("\n");*/
	tcp_info->tcp_window = ntohs(tcp_protocol->tcp_window);
	tcp_info->tcp_chksum = ntohs(tcp_protocol->tcp_chksum);
	tcp_info->tcp_urgpoint = ntohs(tcp_protocol->tcp_urgpoint);
	packet_info->transmission_packet_info = tcp_info;
	//printf("窗口大小:%d\n", ntohs(tcp_protocol->tcp_window));
	//printf("校验和:%x\n", ntohs(tcp_protocol->tcp_chksum));
	//printf("紧急指针:%d\n", ntohs(tcp_protocol->tcp_urgpoint));
}

//UDP数据报分析
void Thread::UDP_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	IPV4_HEADER *ih = (IPV4_HEADER *)(packet_data + 14); //以太网头部长度
	/* 获得UDP首部的位置 */
	u_int ip_len = ( 0x45 & 0xf) * 4;
	UDP_HEADER *udp_protocol = (PUDP_HEADER)((u_char*)ih + ip_len);
	u_short udp_destport = ntohs(udp_protocol->udp_destport);
	UDP_info*udp_info = new UDP_info;
	udp_info->udp_sourport = ntohs(udp_protocol->udp_sourport);
	udp_info->udp_destport = ntohs(udp_protocol->udp_destport);
	//printf("----------- UDP协议    -----------\n");
	//printf("源端口：");
	//printf("%d\n", ntohs(udp_protocol->udp_sourport));
	//printf("目的端口：");
	//printf("%d\n", ntohs(udp_protocol->udp_destport));
	/*switch (udp_destport)
	{
	case 80:
		printf("上层协议：HTTP协议\n");
		break;
	case 21:
		printf("上层协议：FTP协议\n");
		break;
	case 23:
		printf("上层协议：TELNET协议\n");
		break;
	case 25:
		printf("上层协议：SMTP协议\n");
		break;
	case 110:
		printf("上层协议POP3协议\n");
		break;
	default:
		break;
	}*/
	udp_info->udp_hlen = udp_protocol->udp_hlen;
	udp_info->udp_crc = ntohs(udp_protocol->udp_crc);
	packet_info->transmission_packet_info = udp_info;
	//printf("UDP总长度长度：%d\n", udp_protocol->udp_hlen);
	//printf("校验和:%x\n", ntohs(udp_protocol->udp_crc));
}

//IPV4数据报分析
void Thread::IPV4_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct in_addr addr1,addr2;
	IPV4_HEADER *ip_protocol = (PIPV4_HEADER)(packet_data + 14);
	IPv4_info* ipv4_info = new IPv4_info;
	ipv4_info->ipv4_ver = ip_protocol->ipv4_ver;
	ipv4_info->ipv4_hl = ip_protocol->ipv4_hl;
	ipv4_info->ipv4_stype = ip_protocol->ipv4_stype;
	ipv4_info->ipv4_plen = ntohs(ip_protocol->ipv4_plen);
	ipv4_info->ipv4_pidentify = ntohs(ip_protocol->ipv4_pidentify);
	ipv4_info->ipv4_flag_offset = (ntohs(ip_protocol->ipv4_flag_offset) & 0x1fff) * 8;
	ipv4_info->ipv4_pro = ip_protocol->ipv4_pro;
	ipv4_info->ipv4_ttl = ip_protocol->ipv4_ttl;
	/*printf("----------- IPV4协议    -----------\n");
	printf("版本号:%d\n", ip_protocol->ipv4_ver);
	printf("首部长度:%d\n", ip_protocol->ipv4_hl);
	printf("服务质量:%d\n", ip_protocol->ipv4_stype);
	printf("总长度:%d\n", ntohs(ip_protocol->ipv4_plen));
	printf("标识:%d\n", ntohs(ip_protocol->ipv4_pidentify));
	printf("偏移:%d\n", (ntohs(ip_protocol->ipv4_flag_offset) & 0x1fff) * 8);
	printf("生存时间:%d\n", ip_protocol->ipv4_ttl);
	printf("协议类型:%d\n", ip_protocol->ipv4_pro);
	switch (ip_protocol->ipv4_pro)
	{
	case 0x01:
		printf("上层协议类型：ICMP协议\n");
		break;
	case 0x02:
		printf("上层协议类型：IGMP协议\n");
		break;
	case 0x06:
		printf("上层协议类型：TCP协议\n");
		break;
	case 0x11:
		printf("上层协议类型：UDP协议\n");
		break;
	default:
		break;
	}*/
	ipv4_info->ipv4_crc = ntohs(ip_protocol->ipv4_crc);
	ipv4_info->ipv4_sourpa[0] = int(ip_protocol->ipv4_sourpa.d1);
	ipv4_info->ipv4_sourpa[1] = int(ip_protocol->ipv4_sourpa.d2);
	ipv4_info->ipv4_sourpa[2] = int(ip_protocol->ipv4_sourpa.d3);
	ipv4_info->ipv4_sourpa[3] = int(ip_protocol->ipv4_sourpa.d4);
	ipv4_info->ipv4_destpa[0] = int(ip_protocol->ipv4_destpa.d1);
	ipv4_info->ipv4_destpa[1] = int(ip_protocol->ipv4_destpa.d2);
	ipv4_info->ipv4_destpa[2] = int(ip_protocol->ipv4_destpa.d3);
	ipv4_info->ipv4_destpa[3] = int(ip_protocol->ipv4_destpa.d4);
	packet_info->internet_packet_info = ipv4_info;
	//IPv4_info*x = static_cast<IPv4_info*>(packet_info->internet_packet_info);
	//printf("校验和：%d\n", ntohs(ip_protocol->ipv4_crc));
	//printf("源IP地址：");
	//memcpy(&addr, &ip_protocol->ipv4_sourpa, 4);
	//printf("%s\n", inet_ntoa(addr));
	//printf("目的IP地址：");
	//memcpy(&addr, &ip_protocol->ipv4_destpa, 4);
	//printf("%s\n", inet_ntoa(addr));
	switch (ip_protocol->ipv4_pro)
	{
	case 0x06:
		packet_info->transmission_packet_info = new TCP_info;
		this->TCP_PROTOCOL_CALLBACK(packet_info,header, packet_data);
		this->count.tcp++;
		break;
	case 0x11:
		packet_info->transmission_packet_info = new UDP_info;
		this->UDP_PROTOCOL_CALLBACK(packet_info,header, packet_data);
		this->count.udp++;
		break;
	default:
		packet_info->transmission_packet_info = new Transmission_packet_info;
		break;
	}
}

//IPV6数据报分析
void Thread::IPV6_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct in6_addr addr;
	IPV6_HEADER *ip_protocol = (PIPV6_HEADER)(packet_data + 14);
	IPv6_info*ipv6_info = new IPv6_info;
	//printf("----------- IPV6协议    -----------\n");
	u_short ipv6_ver_hl_priority = ntohs(ip_protocol->ipv6_ver_hl_priority);
	ipv6_info->ipv6_ver = (ipv6_ver_hl_priority & 0xf000) >> 12;
	ipv6_info->ipv6_hl_priority = (ipv6_ver_hl_priority & 0x0ff0) >> 4;
	//printf("版本号:%d\n", (ipv6_ver_hl_priority & 0xf000) >> 12);
	//printf("流量等级:%d\n", (ipv6_ver_hl_priority & 0x0ff0) >> 4);
	u_int label = int(ipv6_ver_hl_priority & 0x000f) * 0x10000 + ntohs(ip_protocol->ipv6_lable);
	ipv6_info->label = label;
	ipv6_info->ipv6_plen = ntohs(ip_protocol->ipv6_plen);
	ipv6_info->ipv6_nextheader = int(ip_protocol->ipv6_nextheader);
	ipv6_info->ipv6_limits = ip_protocol->ipv6_limits;
	/*printf("流标签:%x\n", label);
	printf("有效载荷:%d\n", ntohs(ip_protocol->ipv6_plen));
	printf("下一个首部:%d\n", int(ip_protocol->ipv6_nextheader));
	printf("跳数限制:%d\n", ip_protocol->ipv6_limits);
	printf("协议类型:%d\n", int(ip_protocol->ipv6_nextheader));
	switch (int(ip_protocol->ipv6_nextheader))
	{
	case 0x01:
		printf("上层协议类型：ICMP协议\n");
		break;
	case 0x02:
		printf("上层协议类型：IGMP协议\n");
		break;
	case 0x06:
		printf("上层协议类型：TCP协议\n");
		break;
	case 0x11:
		printf("上层协议类型：UDP协议\n");
		break;
	default:
		break;
	}*/
	for (int i = 0; i < 8; i++) {
		ipv6_info->ipv6_sourpa[i] = ntohs(ip_protocol->ipv6_sourpa.u.Word[i]);
		ipv6_info->ipv6_destpa[i] = ntohs(ip_protocol->ipv6_destpa.u.Word[i]);
	}
	packet_info->internet_packet_info = ipv6_info;
	/*printf("源IPv6地址：%x:%x:%x:%x:%x:%x:%x:%x\n", ntohs(ip_protocol->ipv6_sourpa.u.Word[0]), ntohs(ip_protocol->ipv6_sourpa.u.Word[1]), ntohs(ip_protocol->ipv6_sourpa.u.Word[2]), ntohs(ip_protocol->ipv6_sourpa.u.Word[3]), ntohs(ip_protocol->ipv6_sourpa.u.Word[4]), ntohs(ip_protocol->ipv6_sourpa.u.Word[5]), ntohs(ip_protocol->ipv6_sourpa.u.Word[6]), ntohs(ip_protocol->ipv6_sourpa.u.Word[7]));
	printf("源IPv6地址：%x:%x:%x:%x:%x:%x:%x:%x\n", ntohs(ip_protocol->ipv6_destpa.u.Word[0]), ntohs(ip_protocol->ipv6_destpa.u.Word[1]), ntohs(ip_protocol->ipv6_destpa.u.Word[2]), ntohs(ip_protocol->ipv6_destpa.u.Word[3]), ntohs(ip_protocol->ipv6_destpa.u.Word[4]), ntohs(ip_protocol->ipv6_destpa.u.Word[5]), ntohs(ip_protocol->ipv6_destpa.u.Word[6]), ntohs(ip_protocol->ipv6_destpa.u.Word[7]));*/
	switch (ip_protocol->ipv6_nextheader)
	{
	case 0x06:
		packet_info->transmission_packet_info = new TCP_info;
		this->TCP_PROTOCOL_CALLBACK(packet_info, header, packet_data);
		this->count.tcp++;
		break;
	case 0x11:
		packet_info->transmission_packet_info = new UDP_info;
		this->UDP_PROTOCOL_CALLBACK(packet_info, header, packet_data);
		this->count.udp++;
		break;
	default:
		packet_info->transmission_packet_info = new Transmission_packet_info;
		break;
	}
}

//ARP数据报分析
void Thread::ARP_PROTOC0L_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct in_addr addr;
	ARP_HEADER* ah = (PARP_HEADER)(packet_data + 14);
	ARP_info*arp_info = new ARP_info;
	arp_info->operation_code = ntohs(ah->arp_op);
	arp_info->arp_hrd = ntohs(ah->arp_hrd);
	arp_info->arp_pro = ntohs(ah->arp_pro);
	//printf("----------- ARP协议    -----------\n");
	//u_short operation_code = ntohs(ah->arp_op);
	//printf("硬件类型：%d\n", ntohs(ah->arp_hrd));
	//printf("协议类型：0x%x", ntohs(ah->arp_pro));
	/*switch (ntohs(ah->arp_pro))
	{
	case 0x800:
		printf(" IPv4\n");
		break;
	case 0x806:
		printf(" ARP\n");
		break;
	default:
		printf("\n");
		break;
	}*/
	arp_info->arp_hsize = int(ah->arp_hsize);
	arp_info->arp_psize = int(ah->arp_psize);
	/*printf("硬件地址长度：%d\n", int(ah->arp_hsize));
	printf("协议地址长度：%d\n", int(ah->arp_psize));
	printf("操作类型：");
	switch (operation_code)
	{
	case 1:
		printf("%d ARP请求协议\n", operation_code);
		break;
	case 2:
		printf("%d ARP应答协议\n", operation_code);
		break;
	case 3:
		printf("%d ARP请求协议\n", operation_code);
		break;
	case 4:
		printf("%d RARP应答协议\n", operation_code);
		break;
	default:
		break;
	}*/
	arp_info->arp_senderMAC[0] = int(ah->arp_senderMAC.d1);
	arp_info->arp_senderMAC[1] = int(ah->arp_senderMAC.d2);
	arp_info->arp_senderMAC[2] = int(ah->arp_senderMAC.d3);
	arp_info->arp_senderMAC[3] = int(ah->arp_senderMAC.d4);
	arp_info->arp_senderMAC[4] = int(ah->arp_senderMAC.d5);
	arp_info->arp_senderMAC[5] = int(ah->arp_senderMAC.d6);
	arp_info->arp_targetMAC[0] = int(ah->arp_targetMAC.d1);
	arp_info->arp_targetMAC[1] = int(ah->arp_targetMAC.d2);
	arp_info->arp_targetMAC[2] = int(ah->arp_targetMAC.d3);
	arp_info->arp_targetMAC[3] = int(ah->arp_targetMAC.d4);
	arp_info->arp_targetMAC[4] = int(ah->arp_targetMAC.d5);
	arp_info->arp_targetMAC[5] = int(ah->arp_targetMAC.d6);
	arp_info->arp_senderIP[0] = int(ah->arp_senderIP.d1);
	arp_info->arp_senderIP[1] = int(ah->arp_senderIP.d2);
	arp_info->arp_senderIP[2] = int(ah->arp_senderIP.d3);
	arp_info->arp_senderIP[3] = int(ah->arp_senderIP.d4);
	arp_info->arp_targetIP[0] = int(ah->arp_targetIP.d1);
	arp_info->arp_targetIP[1] = int(ah->arp_targetIP.d2);
	arp_info->arp_targetIP[2] = int(ah->arp_targetIP.d3);
	arp_info->arp_targetIP[3] = int(ah->arp_targetIP.d4);
	packet_info->transmission_packet_info = arp_info;
	packet_info->internet_packet_info = nullptr;
	/*printf("源MAC地址:%x:%x:%x:%x:%x:%x\n",int(ah->arp_senderMAC.d1), int(ah->arp_senderMAC.d2), int(ah->arp_senderMAC.d3), int(ah->arp_senderMAC.d4), int(ah->arp_senderMAC.d5), int(ah->arp_senderMAC.d6));
	printf("源IP地址:%d.%d.%d.%d\n",int(ah->arp_senderIP.d1), int(ah->arp_senderIP.d2), int(ah->arp_senderIP.d3), int(ah->arp_senderIP.d4));
	printf("目标MAC地址:%x:%x:%x:%x:%x:%x\n", int(ah->arp_targetMAC.d1), int(ah->arp_targetMAC.d2), int(ah->arp_targetMAC.d3), int(ah->arp_targetMAC.d4), int(ah->arp_targetMAC.d5), int(ah->arp_targetMAC.d6));
	printf("目标IP地址:%d.%d.%d.%d\n", int(ah->arp_targetIP.d1), int(ah->arp_targetIP.d2), int(ah->arp_targetIP.d3), int(ah->arp_targetIP.d4));*/
}

Thread::Thread(){
	this->count.arp = 0;
	this->count.tcp = 0;
	this->count.udp = 0;
	this->count.ipv4 = 0;
	this->count.ipv6 = 0;
}

//main
void Thread::run() {
	int res; int typ = 0;
	PacketInfo* packet_info;
	while ((res = pcap_next_ex(this->adhandle, &this->header, &this->pkt_data)) >= 0) {
		typ = 0;
		if (res == 0)
			continue;
		this->mutex.lock();
		if (this->import_flag == 0) {
			pcap_dump((unsigned char *)this->dumpfile, this->header, this->pkt_data);
		}
		packet_info = new PacketInfo;
		ETHER_HEADER* eh = (ETHER_HEADER*)this->pkt_data;
		u_short type = ntohs(eh->ether_type);
		switch (type)
		{
		case 0x0800://ipv4
			packet_info->internet_packet_info = new IPv4_info;
			IPV4_PROTOCOL_CALLBACK(packet_info, header, this->pkt_data);
			this->count.ipv4++;
			//emit new_packet(packet_info);
			break;
		case 0x86DD://ipv6
			packet_info->internet_packet_info = new IPv6_info;
			IPV6_PROTOCOL_CALLBACK(packet_info, header, this->pkt_data);
			this->count.ipv6++;
			//emit new_packet(packet_info);
			break;
		case 0x0806://arp
			packet_info->transmission_packet_info = new ARP_info;
			ARP_PROTOC0L_CALLBACK(packet_info, header, this->pkt_data);
			this->count.arp++;
			//emit new_packet(packet_info);
			break;
		default:
			typ = 1;
			break;
		}
		this->mutex.unlock();
		if (typ == 0)
			emit new_packet(packet_info);
		//this->sleep(0.1);//sleep让进程休眠
	}
	//delete packet_info;
}
void Thread::init(pcap_t*& adhandle) {
	this->adhandle = adhandle;
	this->count.arp = 0;
	this->count.tcp = 0;
	this->count.udp = 0;
	this->count.ipv4 = 0;
	this->count.ipv6 = 0;
	this->import_flag = 0;
	FILE* f = fopen("./data.pac", "w+");
	fclose(f);
	this->dumpfile = pcap_dump_open(adhandle, "./data.pac");
}
void Thread::tcontinue() {
	this->mutex.unlock();
}
void Thread::close() {
	this->mutex.lock();
}
void Thread::import(char* path) {
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	char source[PCAP_BUF_SIZE];
	/* 根据新WinPcap语法创建一个源字符串 */
	if (pcap_createsrcstr(source,         // 源字符串
		PCAP_SRC_FILE,  // 我们要打开的文件
		NULL,           // 远程主机
		NULL,           // 远程主机端口
		path,        // 我们要打开的文件名
		errbuf          // 错误缓冲区
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
		return;
	}
	/* 打开捕获文件 */
	if ((fp = pcap_open(source,         // 设备名
		65536,          // 要捕捉的数据包的部分
						// 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,     // 混杂模式
		1000,              // 读取超时时间
		NULL,              // 远程机器验证
		errbuf         // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file %s.\n", source);
		return;
	}
	this->adhandle = fp;
	this->count.arp = 0;
	this->count.tcp = 0;
	this->count.udp = 0;
	this->count.ipv4 = 0;
	this->count.ipv6 = 0;
	this->import_flag = 1;
}
//向界面传指定编号的数据
PacketInfo* Thread::findPacket(int pos,char* rule) {
	PacketInfo* packet_info;
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	char source[PCAP_BUF_SIZE];
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	u_int netmask;
	struct bpf_program fcode;
	int i = 0;
	int res;
	/* 根据新WinPcap语法创建一个源字符串 */
	if (pcap_createsrcstr(source,         // 源字符串
		PCAP_SRC_FILE,  // 我们要打开的文件
		NULL,           // 远程主机
		NULL,           // 远程主机端口
		"./data.pac",        // 我们要打开的文件名
		errbuf          // 错误缓冲区
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
	}
	/* 打开捕获文件 */
	if ((fp = pcap_open(source,         // 设备名
		65536,          // 要捕捉的数据包的部分
						// 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,     // 混杂模式
		1000,              // 读取超时时间
		NULL,              // 远程机器验证
		errbuf         // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file %s.\n", source);
	}
	if (pcap_compile(fp, &fcode, rule, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
	}
	//设置过滤器
	if (pcap_setfilter(fp, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
	}
	/* 从文件获取数据包 */
	while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
	{
		if (res == 0)
			continue;
		if (i == pos) {
			packet_info = new PacketInfo;
			ETHER_HEADER* eh = (ETHER_HEADER*)pkt_data;
			u_short type = ntohs(eh->ether_type);
			switch (type)
			{
			case 0x0800://ipv4
				packet_info->internet_packet_info = new IPv4_info;
				IPV4_PROTOCOL_CALLBACK(packet_info, header, pkt_data);
				break;
			case 0x86DD://ipv6
				packet_info->internet_packet_info = new IPv6_info;
				IPV6_PROTOCOL_CALLBACK(packet_info, header, pkt_data);
				break;
			case 0x0806://arp
				packet_info->transmission_packet_info = new ARP_info;
				ARP_PROTOC0L_CALLBACK(packet_info, header, pkt_data);
				break;
			default:
				break;
			}
			break;
		}
		i++;
	}
	return packet_info;
}
//过滤包
bool Thread::filerPacket(char* rule) {
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	char source[PCAP_BUF_SIZE];
	u_int netmask;
	struct bpf_program fcode;
	/* 根据新WinPcap语法创建一个源字符串 */
	if (pcap_createsrcstr(source,         // 源字符串
		PCAP_SRC_FILE,  // 我们要打开的文件
		NULL,           // 远程主机
		NULL,           // 远程主机端口
		"./data.pac",        // 我们要打开的文件名
		errbuf          // 错误缓冲区
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
		return false;
	}
	/* 打开捕获文件 */
	if ((adhandle = pcap_open(source,         // 设备名
		65536,          // 要捕捉的数据包的部分
						// 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,     // 混杂模式
		1000,              // 读取超时时间
		NULL,              // 远程机器验证
		errbuf         // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file %s.\n", source);
		return false;
	}
	if (pcap_compile(adhandle, &fcode, rule, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		return false;
	}
	//设置过滤器
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		return false;
	}
	this->adhandle = adhandle;
	this->import_flag = 1;
	return true;
}
