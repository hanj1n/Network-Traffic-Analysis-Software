#pragma once
#include <QThread>
#include <QMutex>
#include <vector>
#include "pcap.h"
//packet count
struct COUNT {
	int ipv4;
	int ipv6;
	int arp;
	int tcp;
	int udp;
};
//packet info struct
class Internet_packet_info {
public:
	int ipv4_check;
};
class Transmission_packet_info {
public:
	int tcp_check;
	int arp_check;
	int udp_check;
	Transmission_packet_info() {
		this->arp_check = 0;
		this->tcp_check = 0;
		this->udp_check = 0;
	}
};
class IPv4_info:public Internet_packet_info {
public:
	IPv4_info() { this->ipv4_check = 1; }
	int ipv4_ver;
	int ipv4_hl;
	int ipv4_stype;
	int ipv4_plen;
	int ipv4_pidentify;
	int ipv4_flag_offset;
	int ipv4_ttl;
	int ipv4_pro;
	int ipv4_crc;
	int ipv4_sourpa[4];
	int ipv4_destpa[4];
};
class IPv6_info :public Internet_packet_info {
public:
	IPv6_info() { this->ipv4_check = 0; }
	int ipv6_ver;
	int ipv6_hl_priority;
	int label;//0x
	int ipv6_plen;
	int ipv6_nextheader;
	int ipv6_limits;
	int ipv6_sourpa[8];
	int ipv6_destpa[8];
};
class TCP_info :public Transmission_packet_info {
public:
	TCP_info() { this->tcp_check = 1; this->arp_check = 0; this->udp_check = 0; }
	int tcp_sourport;
	int tcp_destport;
	u_long tcp_seqnu;
	u_long tcp_acknu;
	int tcp_hlen;
	u_char tcp_reserved;
	u_short tcp_window;
	u_short tcp_chksum;
	u_short tcp_urgpoint;
};
class UDP_info :public Transmission_packet_info {
public:
	UDP_info() { this->tcp_check = 0; this->arp_check = 0; this->udp_check = 1; }
	u_short udp_sourport;
	u_short udp_destport;
	u_short udp_hlen;
	u_short udp_crc;//0x
};
class PacketInfo {
public:
	Internet_packet_info*internet_packet_info;
	Transmission_packet_info*transmission_packet_info;
	PacketInfo(){}
	void setTransPacket(TCP_info* &packet) {
		transmission_packet_info = (Transmission_packet_info*)packet;
	}
	void setTransPacket(UDP_info* &packet) {
		transmission_packet_info = (Transmission_packet_info*)packet;
	}
	void setInterPacket(IPv4_info* &packet) {
		internet_packet_info = (Internet_packet_info*)packet;
	}
	void setInterPacket(IPv6_info*packet) {
		internet_packet_info = (Internet_packet_info*)packet;
	}
};
class ARP_info :public Transmission_packet_info
{
public:
	ARP_info() { this->arp_check = 1; this->tcp_check = 0; }
	u_short arp_hrd;
	u_short arp_pro;//0x
	u_short operation_code;
	int arp_hsize;
	int arp_psize;
	int arp_senderMAC[6];//0x
	int arp_senderIP[4];
	int arp_targetMAC[6];//0x
	int arp_targetIP[4];
};

class Thread :public QThread
{
	Q_OBJECT
public:
	Thread();
	void init(pcap_t* &);
	void import(char*);
	void close();
	void tcontinue();
	void run();
	void TCP_PROTOCOL_CALLBACK(PacketInfo*& packet_info,const struct pcap_pkthdr *header, const u_char *packet_data);
	void UDP_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data);
	void IPV4_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data);
	void IPV6_PROTOCOL_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data);
	void ARP_PROTOC0L_CALLBACK(PacketInfo*& packet_info, const struct pcap_pkthdr *header, const u_char *packet_data);
	//std::vector<PacketInfo*> loadPacket(int&currlen);
	PacketInfo* findPacket(int pos, char* rule);
	bool filerPacket(char* rule);
	COUNT count;
	pcap_dumper_t *dumpfile;
protected:
	int test;	
	int import_flag;
	pcap_t* adhandle;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	QMutex mutex;//ª•≥‚¡ø
signals:
	void new_packet(PacketInfo*);
};

