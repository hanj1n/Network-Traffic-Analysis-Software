#include "Thread.h"
#include <QtDebug>

/*��̫��֡ͷ��ʽ�ṹ�� 14���ֽ�*/
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

/*��ARP�ֶνṹ�� 28���ֽ�*/
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

/*ARP���Ľṹ�� 42���ֽ�*/
typedef struct arp_packet {
	ETHER_HEADER etherHeader;
	ARP_HEADER   arpHeader;
}ARPPACKET, *PARPPACKET;

/*IPv4��ͷ�ṹ�� 20���ֽ�*/
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

/*IPv6��ͷ�ṹ�� 40���ֽ�*/
typedef struct ipv6_header {
	u_short ipv6_ver_hl_priority;
	u_short ipv6_lable;//4+8+20
	u_short ipv6_plen;
	u_char  ipv6_nextheader;
	u_char  ipv6_limits;
	in6_addr ipv6_sourpa;
	in6_addr ipv6_destpa;
}IPV6_HEADER, *PIPV6_HEADER;

/*UDP��ͷ�ṹ�� 8���ֽ�*/
typedef struct udp_header {
	u_short udp_sourport;
	u_short udp_destport;
	u_short udp_hlen;
	u_short udp_crc;
}UDP_HEADER, *PUDP_HEADER;

/*TCP��ͷ�ṹ�� 20���ֽ�*/
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

//TCP���ݱ�����
void Thread::TCP_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	TCP_HEADER *tcp_protocol = (PTCP_HEADER)(packet_data + 14 + 20);

	u_short tcp_destport = ntohs(tcp_protocol->tcp_destport);
	u_char  tcp_reserved = tcp_protocol->tcp_reserved;
	TCP_info*tcp_info = new TCP_info;
	//printf("----------- TCPЭ��    -----------\n");
	//printf("Դ�˿ڣ�");
	tcp_info->tcp_sourport = ntohs(tcp_protocol->tcp_sourport);
	//printf("%d\n", ntohs(tcp_protocol->tcp_sourport));
	//printf("Ŀ�Ķ˿ڣ�");
	tcp_info->tcp_destport = tcp_destport;
	//printf("%d\n", tcp_destport);
	/*switch (tcp_destport)
	{
	case 80:
		printf("�ϲ�Э�飺HTTPЭ��\n");
		break;
	case 21:
		printf("�ϲ�Э�飺FTPЭ��\n");
		break;
	case 23:
		printf("�ϲ�Э�飺TELNETЭ��\n");
		break;
	case 25:
		printf("�ϲ�Э�飺SMTPЭ��\n");
		break;
	case 110:
		printf("�ϲ�Э��POP3Э��\n");
		break;
	default:
		break;
	}*/
	tcp_info->tcp_seqnu = ntohl(tcp_protocol->tcp_seqnu);
	tcp_info->tcp_acknu = ntohl(tcp_protocol->tcp_acknu);
	tcp_info->tcp_hlen = tcp_protocol->tcp_hlen;
	tcp_info->tcp_reserved = tcp_reserved;
	//printf("�����룺%u\n", ntohl(tcp_protocol->tcp_seqnu));
	//printf("ȷ�Ϻţ�%u\n", ntohl(tcp_protocol->tcp_acknu));
	//printf("�ײ��������ȣ�%d\n", tcp_protocol->tcp_hlen);
	/*printf("��ǣ�");
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
	//printf("���ڴ�С:%d\n", ntohs(tcp_protocol->tcp_window));
	//printf("У���:%x\n", ntohs(tcp_protocol->tcp_chksum));
	//printf("����ָ��:%d\n", ntohs(tcp_protocol->tcp_urgpoint));
}

//UDP���ݱ�����
void Thread::UDP_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	IPV4_HEADER *ih = (IPV4_HEADER *)(packet_data + 14); //��̫��ͷ������
	/* ���UDP�ײ���λ�� */
	u_int ip_len = ( 0x45 & 0xf) * 4;
	UDP_HEADER *udp_protocol = (PUDP_HEADER)((u_char*)ih + ip_len);
	u_short udp_destport = ntohs(udp_protocol->udp_destport);
	UDP_info*udp_info = new UDP_info;
	udp_info->udp_sourport = ntohs(udp_protocol->udp_sourport);
	udp_info->udp_destport = ntohs(udp_protocol->udp_destport);
	//printf("----------- UDPЭ��    -----------\n");
	//printf("Դ�˿ڣ�");
	//printf("%d\n", ntohs(udp_protocol->udp_sourport));
	//printf("Ŀ�Ķ˿ڣ�");
	//printf("%d\n", ntohs(udp_protocol->udp_destport));
	/*switch (udp_destport)
	{
	case 80:
		printf("�ϲ�Э�飺HTTPЭ��\n");
		break;
	case 21:
		printf("�ϲ�Э�飺FTPЭ��\n");
		break;
	case 23:
		printf("�ϲ�Э�飺TELNETЭ��\n");
		break;
	case 25:
		printf("�ϲ�Э�飺SMTPЭ��\n");
		break;
	case 110:
		printf("�ϲ�Э��POP3Э��\n");
		break;
	default:
		break;
	}*/
	udp_info->udp_hlen = udp_protocol->udp_hlen;
	udp_info->udp_crc = ntohs(udp_protocol->udp_crc);
	packet_info->transmission_packet_info = udp_info;
	//printf("UDP�ܳ��ȳ��ȣ�%d\n", udp_protocol->udp_hlen);
	//printf("У���:%x\n", ntohs(udp_protocol->udp_crc));
}

//IPV4���ݱ�����
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
	/*printf("----------- IPV4Э��    -----------\n");
	printf("�汾��:%d\n", ip_protocol->ipv4_ver);
	printf("�ײ�����:%d\n", ip_protocol->ipv4_hl);
	printf("��������:%d\n", ip_protocol->ipv4_stype);
	printf("�ܳ���:%d\n", ntohs(ip_protocol->ipv4_plen));
	printf("��ʶ:%d\n", ntohs(ip_protocol->ipv4_pidentify));
	printf("ƫ��:%d\n", (ntohs(ip_protocol->ipv4_flag_offset) & 0x1fff) * 8);
	printf("����ʱ��:%d\n", ip_protocol->ipv4_ttl);
	printf("Э������:%d\n", ip_protocol->ipv4_pro);
	switch (ip_protocol->ipv4_pro)
	{
	case 0x01:
		printf("�ϲ�Э�����ͣ�ICMPЭ��\n");
		break;
	case 0x02:
		printf("�ϲ�Э�����ͣ�IGMPЭ��\n");
		break;
	case 0x06:
		printf("�ϲ�Э�����ͣ�TCPЭ��\n");
		break;
	case 0x11:
		printf("�ϲ�Э�����ͣ�UDPЭ��\n");
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
	//printf("У��ͣ�%d\n", ntohs(ip_protocol->ipv4_crc));
	//printf("ԴIP��ַ��");
	//memcpy(&addr, &ip_protocol->ipv4_sourpa, 4);
	//printf("%s\n", inet_ntoa(addr));
	//printf("Ŀ��IP��ַ��");
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

//IPV6���ݱ�����
void Thread::IPV6_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct in6_addr addr;
	IPV6_HEADER *ip_protocol = (PIPV6_HEADER)(packet_data + 14);
	IPv6_info*ipv6_info = new IPv6_info;
	//printf("----------- IPV6Э��    -----------\n");
	u_short ipv6_ver_hl_priority = ntohs(ip_protocol->ipv6_ver_hl_priority);
	ipv6_info->ipv6_ver = (ipv6_ver_hl_priority & 0xf000) >> 12;
	ipv6_info->ipv6_hl_priority = (ipv6_ver_hl_priority & 0x0ff0) >> 4;
	//printf("�汾��:%d\n", (ipv6_ver_hl_priority & 0xf000) >> 12);
	//printf("�����ȼ�:%d\n", (ipv6_ver_hl_priority & 0x0ff0) >> 4);
	u_int label = int(ipv6_ver_hl_priority & 0x000f) * 0x10000 + ntohs(ip_protocol->ipv6_lable);
	ipv6_info->label = label;
	ipv6_info->ipv6_plen = ntohs(ip_protocol->ipv6_plen);
	ipv6_info->ipv6_nextheader = int(ip_protocol->ipv6_nextheader);
	ipv6_info->ipv6_limits = ip_protocol->ipv6_limits;
	/*printf("����ǩ:%x\n", label);
	printf("��Ч�غ�:%d\n", ntohs(ip_protocol->ipv6_plen));
	printf("��һ���ײ�:%d\n", int(ip_protocol->ipv6_nextheader));
	printf("��������:%d\n", ip_protocol->ipv6_limits);
	printf("Э������:%d\n", int(ip_protocol->ipv6_nextheader));
	switch (int(ip_protocol->ipv6_nextheader))
	{
	case 0x01:
		printf("�ϲ�Э�����ͣ�ICMPЭ��\n");
		break;
	case 0x02:
		printf("�ϲ�Э�����ͣ�IGMPЭ��\n");
		break;
	case 0x06:
		printf("�ϲ�Э�����ͣ�TCPЭ��\n");
		break;
	case 0x11:
		printf("�ϲ�Э�����ͣ�UDPЭ��\n");
		break;
	default:
		break;
	}*/
	for (int i = 0; i < 8; i++) {
		ipv6_info->ipv6_sourpa[i] = ntohs(ip_protocol->ipv6_sourpa.u.Word[i]);
		ipv6_info->ipv6_destpa[i] = ntohs(ip_protocol->ipv6_destpa.u.Word[i]);
	}
	packet_info->internet_packet_info = ipv6_info;
	/*printf("ԴIPv6��ַ��%x:%x:%x:%x:%x:%x:%x:%x\n", ntohs(ip_protocol->ipv6_sourpa.u.Word[0]), ntohs(ip_protocol->ipv6_sourpa.u.Word[1]), ntohs(ip_protocol->ipv6_sourpa.u.Word[2]), ntohs(ip_protocol->ipv6_sourpa.u.Word[3]), ntohs(ip_protocol->ipv6_sourpa.u.Word[4]), ntohs(ip_protocol->ipv6_sourpa.u.Word[5]), ntohs(ip_protocol->ipv6_sourpa.u.Word[6]), ntohs(ip_protocol->ipv6_sourpa.u.Word[7]));
	printf("ԴIPv6��ַ��%x:%x:%x:%x:%x:%x:%x:%x\n", ntohs(ip_protocol->ipv6_destpa.u.Word[0]), ntohs(ip_protocol->ipv6_destpa.u.Word[1]), ntohs(ip_protocol->ipv6_destpa.u.Word[2]), ntohs(ip_protocol->ipv6_destpa.u.Word[3]), ntohs(ip_protocol->ipv6_destpa.u.Word[4]), ntohs(ip_protocol->ipv6_destpa.u.Word[5]), ntohs(ip_protocol->ipv6_destpa.u.Word[6]), ntohs(ip_protocol->ipv6_destpa.u.Word[7]));*/
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

//ARP���ݱ�����
void Thread::ARP_PROTOC0L_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct in_addr addr;
	ARP_HEADER* ah = (PARP_HEADER)(packet_data + 14);
	ARP_info*arp_info = new ARP_info;
	arp_info->operation_code = ntohs(ah->arp_op);
	arp_info->arp_hrd = ntohs(ah->arp_hrd);
	arp_info->arp_pro = ntohs(ah->arp_pro);
	//printf("----------- ARPЭ��    -----------\n");
	//u_short operation_code = ntohs(ah->arp_op);
	//printf("Ӳ�����ͣ�%d\n", ntohs(ah->arp_hrd));
	//printf("Э�����ͣ�0x%x", ntohs(ah->arp_pro));
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
	/*printf("Ӳ����ַ���ȣ�%d\n", int(ah->arp_hsize));
	printf("Э���ַ���ȣ�%d\n", int(ah->arp_psize));
	printf("�������ͣ�");
	switch (operation_code)
	{
	case 1:
		printf("%d ARP����Э��\n", operation_code);
		break;
	case 2:
		printf("%d ARPӦ��Э��\n", operation_code);
		break;
	case 3:
		printf("%d ARP����Э��\n", operation_code);
		break;
	case 4:
		printf("%d RARPӦ��Э��\n", operation_code);
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
	/*printf("ԴMAC��ַ:%x:%x:%x:%x:%x:%x\n",int(ah->arp_senderMAC.d1), int(ah->arp_senderMAC.d2), int(ah->arp_senderMAC.d3), int(ah->arp_senderMAC.d4), int(ah->arp_senderMAC.d5), int(ah->arp_senderMAC.d6));
	printf("ԴIP��ַ:%d.%d.%d.%d\n",int(ah->arp_senderIP.d1), int(ah->arp_senderIP.d2), int(ah->arp_senderIP.d3), int(ah->arp_senderIP.d4));
	printf("Ŀ��MAC��ַ:%x:%x:%x:%x:%x:%x\n", int(ah->arp_targetMAC.d1), int(ah->arp_targetMAC.d2), int(ah->arp_targetMAC.d3), int(ah->arp_targetMAC.d4), int(ah->arp_targetMAC.d5), int(ah->arp_targetMAC.d6));
	printf("Ŀ��IP��ַ:%d.%d.%d.%d\n", int(ah->arp_targetIP.d1), int(ah->arp_targetIP.d2), int(ah->arp_targetIP.d3), int(ah->arp_targetIP.d4));*/
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
		//this->sleep(0.1);//sleep�ý�������
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
	/* ������WinPcap�﷨����һ��Դ�ַ��� */
	if (pcap_createsrcstr(source,         // Դ�ַ���
		PCAP_SRC_FILE,  // ����Ҫ�򿪵��ļ�
		NULL,           // Զ������
		NULL,           // Զ�������˿�
		path,        // ����Ҫ�򿪵��ļ���
		errbuf          // ���󻺳���
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
		return;
	}
	/* �򿪲����ļ� */
	if ((fp = pcap_open(source,         // �豸��
		65536,          // Ҫ��׽�����ݰ��Ĳ���
						// 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		PCAP_OPENFLAG_PROMISCUOUS,     // ����ģʽ
		1000,              // ��ȡ��ʱʱ��
		NULL,              // Զ�̻�����֤
		errbuf         // ���󻺳��
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
//����洫ָ����ŵ�����
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
	/* ������WinPcap�﷨����һ��Դ�ַ��� */
	if (pcap_createsrcstr(source,         // Դ�ַ���
		PCAP_SRC_FILE,  // ����Ҫ�򿪵��ļ�
		NULL,           // Զ������
		NULL,           // Զ�������˿�
		"./data.pac",        // ����Ҫ�򿪵��ļ���
		errbuf          // ���󻺳���
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
	}
	/* �򿪲����ļ� */
	if ((fp = pcap_open(source,         // �豸��
		65536,          // Ҫ��׽�����ݰ��Ĳ���
						// 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		PCAP_OPENFLAG_PROMISCUOUS,     // ����ģʽ
		1000,              // ��ȡ��ʱʱ��
		NULL,              // Զ�̻�����֤
		errbuf         // ���󻺳��
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file %s.\n", source);
	}
	if (pcap_compile(fp, &fcode, rule, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
	}
	//���ù�����
	if (pcap_setfilter(fp, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
	}
	/* ���ļ���ȡ���ݰ� */
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
//���˰�
bool Thread::filerPacket(char* rule) {
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	char source[PCAP_BUF_SIZE];
	u_int netmask;
	struct bpf_program fcode;
	/* ������WinPcap�﷨����һ��Դ�ַ��� */
	if (pcap_createsrcstr(source,         // Դ�ַ���
		PCAP_SRC_FILE,  // ����Ҫ�򿪵��ļ�
		NULL,           // Զ������
		NULL,           // Զ�������˿�
		"./data.pac",        // ����Ҫ�򿪵��ļ���
		errbuf          // ���󻺳���
	) != 0)
	{
		fprintf(stderr, "\nError creating a source string\n");
		return false;
	}
	/* �򿪲����ļ� */
	if ((adhandle = pcap_open(source,         // �豸��
		65536,          // Ҫ��׽�����ݰ��Ĳ���
						// 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		PCAP_OPENFLAG_PROMISCUOUS,     // ����ģʽ
		1000,              // ��ȡ��ʱʱ��
		NULL,              // Զ�̻�����֤
		errbuf         // ���󻺳��
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
	//���ù�����
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		return false;
	}
	this->adhandle = adhandle;
	this->import_flag = 1;
	return true;
}
