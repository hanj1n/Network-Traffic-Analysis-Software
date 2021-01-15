#include "Detail.h"
#include "Thread.h"
#pragma execution_character_set("utf-8")
Detail::Detail(QWidget *parent) :
	QDialog(parent), ui(new Ui::Detail)
{
	ui->setupUi(this);
	ui->textBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");
}
Detail::~Detail()
{
	delete ui;
}
void Detail::loadData(int n,char* rule) {
	QString show_text = "Packet " + QString::number(n + 1, 10) + "\n";
	Thread* thread = new Thread;
	PacketInfo* packet_info = thread->findPacket(n,rule);
	if (packet_info->transmission_packet_info->arp_check == 1) {
		ARP_info*arp_info = static_cast<ARP_info*>(packet_info->transmission_packet_info);
		show_text = show_text + "----------- ARPЭ��    -----------\n";
		show_text = show_text + "Ӳ�����ͣ�" + QString::number(arp_info->arp_hrd, 10) + "\n";
		show_text = show_text + "Э�����ͣ�0x" + QString::number(arp_info->arp_pro, 16);
		switch (arp_info->arp_pro)
		{
		case 0x800:
			show_text = show_text + " (IPv4)\n";
			break;
		case 0x806:
			show_text = show_text + " (ARP)\n";
			break;
		default:
			show_text = show_text + "\n";
			break;
		}
		show_text = show_text + "Ӳ����ַ���ȣ�" + QString::number(arp_info->arp_hsize, 10) + "\n";
		show_text = show_text + "Э���ַ���ȣ�" + QString::number(arp_info->arp_psize, 10) + "\n";
		show_text = show_text + "�������ͣ�" + QString::number(arp_info->operation_code, 10);
		switch (arp_info->operation_code)
		{
		case 1:
			show_text = show_text + " (ARP����Э��)\n";
			break;
		case 2:
			show_text = show_text + " (ARPӦ��Э��)\n";
			break;
		case 3:
			show_text = show_text + " (RARP����Э��)\n";
			break;
		case 4:
			show_text = show_text + " (RARPӦ��Э��)\n";
			break;
		default:
			break;
		}
		show_text = show_text + "ԴMAC��ַ��" + QString::number(arp_info->arp_senderMAC[0], 16) + ":" + QString::number(arp_info->arp_senderMAC[1], 16) + ":" + QString::number(arp_info->arp_senderMAC[2], 16) + ":" + QString::number(arp_info->arp_senderMAC[3], 16) + ":" + QString::number(arp_info->arp_senderMAC[4], 16) + ":" + QString::number(arp_info->arp_senderMAC[5], 16) + "\n";
		show_text = show_text + "ԴIP��ַ��" + QString::number(arp_info->arp_senderIP[0], 10) + "." + QString::number(arp_info->arp_senderIP[1], 10) + "." + QString::number(arp_info->arp_senderIP[2], 10) + "." + QString::number(arp_info->arp_senderIP[3], 10) + "\n";
		show_text = show_text + "Ŀ��MAC��ַ��" + QString::number(arp_info->arp_targetMAC[0], 16) + ":" + QString::number(arp_info->arp_targetMAC[1], 16) + ":" + QString::number(arp_info->arp_targetMAC[2], 16) + ":" + QString::number(arp_info->arp_targetMAC[3], 16) + ":" + QString::number(arp_info->arp_targetMAC[4], 16) + ":" + QString::number(arp_info->arp_targetMAC[5], 16) + "\n";
		show_text = show_text + "Ŀ��IP��ַ��" + QString::number(arp_info->arp_targetIP[0], 10) + "." + QString::number(arp_info->arp_targetIP[1], 10) + "." + QString::number(arp_info->arp_targetIP[2], 10) + "." + QString::number(arp_info->arp_targetIP[3], 10) + "\n";
		this->ui->textBrowser->setText(show_text);
		return;
	}
	else if (packet_info->transmission_packet_info->tcp_check == 1) {
		TCP_info*tcp_info = static_cast<TCP_info*>(packet_info->transmission_packet_info);
		show_text = show_text + "----------- TCPЭ��    -----------\n";
		show_text = show_text + "Դ�˿ڣ�" + QString::number(tcp_info->tcp_sourport, 10) + "\n";
		u_short tcp_destport = tcp_info->tcp_destport;
		show_text = show_text + "Ŀ�Ķ˿ڣ�" + QString::number(tcp_destport, 10) + "\n";
		switch (tcp_destport)
		{
		case 80:
			show_text = show_text + "�ϲ�Э�飺HTTPЭ��\n";
			break;
		case 21:
			show_text = show_text + "�ϲ�Э�飺FTPЭ��\n";
			break;
		case 23:
			show_text = show_text + "�ϲ�Э�飺TELNETЭ��\n";
			break;
		case 25:
			show_text = show_text + "�ϲ�Э�飺SMTPЭ��\n";
			break;
		case 110:
			show_text = show_text + "�ϲ�Э�飺POP3Э��\n";
			break;
		default:
			break;
		}
		show_text = show_text + "�����룺"+ QString::number(tcp_info->tcp_seqnu,10) + "\n";
		show_text = show_text + "ȷ�Ϻţ�" + QString::number(tcp_info->tcp_acknu, 10) + "\n";
		show_text = show_text +"�ײ��������ȣ�"+ QString::number(tcp_info->tcp_hlen, 10) + "\n";
		show_text = show_text + "��ǣ�";
		if (tcp_info->tcp_reserved & 32)
			show_text = show_text + " UGR";
		if (tcp_info->tcp_reserved & 16)
			show_text = show_text + " ACK";
		if (tcp_info->tcp_reserved & 8)
			show_text = show_text + " PSH";
		if (tcp_info->tcp_reserved & 4)
			show_text = show_text + " RST";
		if (tcp_info->tcp_reserved & 2)
			show_text = show_text + " SYN";
		if (tcp_info->tcp_reserved & 1)
			show_text = show_text + " FIN";
		show_text = show_text + "\n";
		show_text = show_text + "���ڴ�С��" + QString::number(tcp_info->tcp_window, 10) + "\n";
		show_text = show_text + "У��ͣ�" + QString::number(tcp_info->tcp_chksum, 16) + "\n";
		show_text = show_text + "����ָ�룺" + QString::number(tcp_info->tcp_urgpoint, 10) + "\n";
	}
	else if (packet_info->transmission_packet_info->udp_check == 1) {
		UDP_info*udp_info = static_cast<UDP_info*>(packet_info->transmission_packet_info);
		show_text = show_text + "----------- UDPЭ��    -----------\n";
		show_text = show_text + "Դ�˿ڣ�" + QString::number(udp_info->udp_sourport, 10) + "\n";
		u_short udp_destport = udp_info->udp_destport;
		show_text = show_text + "Ŀ�Ķ˿ڣ�" + QString::number(udp_destport, 10) + "\n";
		switch (udp_destport)
		{
		case 80:
			show_text = show_text + "�ϲ�Э�飺HTTPЭ��\n";
			break;
		case 21:
			show_text = show_text + "�ϲ�Э�飺FTPЭ��\n";
			break;
		case 23:
			show_text = show_text + "�ϲ�Э�飺TELNETЭ��\n";
			break;
		case 25:
			show_text = show_text + "�ϲ�Э�飺SMTPЭ��\n";
			break;
		case 110:
			show_text = show_text + "�ϲ�Э�飺POP3Э��\n";
			break;
		default:
			break;
		}
		show_text = show_text + "UDP�ܳ��ȣ�" + QString::number(udp_info->udp_hlen, 10) + "\n";
		show_text = show_text + "У��ͣ�" + QString::number(udp_info->udp_crc, 16) + "\n";
	}
	if (packet_info->internet_packet_info->ipv4_check == 1) {
		IPv4_info* ipv4_info = static_cast<IPv4_info*>(packet_info->internet_packet_info);
		show_text = show_text + "----------- IPv4Э��    -----------\n";
		show_text = show_text + "�汾�ţ�" + QString::number(ipv4_info->ipv4_ver, 10) + "\n";
		show_text = show_text + "�ײ����ȣ�" + QString::number(ipv4_info->ipv4_stype, 10) + "\n";
		show_text = show_text + "�ܳ��ȣ�" + QString::number(ipv4_info->ipv4_plen, 10) + "\n";
		show_text = show_text + "��ʶ��" + QString::number(ipv4_info->ipv4_pidentify, 10) + "\n";
		show_text = show_text + "ƫ�ƣ�" + QString::number(ipv4_info->ipv4_flag_offset, 10) + "\n";
		show_text = show_text + "����ʱ�䣺" + QString::number(ipv4_info->ipv4_ttl, 10) + "\n";
		show_text = show_text + "�ϲ�Э�����ͣ�" + QString::number(ipv4_info->ipv4_pro, 10);
		switch (ipv4_info->ipv4_pro)
		{
		case 0x01:
			show_text = show_text + " (ICMPЭ��)\n";
			break;
		case 0x02:
			show_text = show_text + " (IGMPЭ��)\n";
			break;
		case 0x06:
			show_text = show_text + " (TCPЭ��)\n";
			break;
		case 0x11:
			show_text = show_text + " (UDPЭ��)\n";
			break;
		default:
			break;
		}
		show_text = show_text + "У��ͣ�" + QString::number(ipv4_info->ipv4_crc, 10) + "\n";
		show_text = show_text + "ԴIP��ַ��" + QString::number(ipv4_info->ipv4_sourpa[0], 10) + "." + QString::number(ipv4_info->ipv4_sourpa[1], 10) + "." + QString::number(ipv4_info->ipv4_sourpa[2], 10) + "." + QString::number(ipv4_info->ipv4_sourpa[3], 10) + "\n";
		show_text = show_text + "Ŀ��IP��ַ��" + QString::number(ipv4_info->ipv4_destpa[0], 10) + "." + QString::number(ipv4_info->ipv4_destpa[1], 10) + "." + QString::number(ipv4_info->ipv4_destpa[2], 10) + "." + QString::number(ipv4_info->ipv4_destpa[3], 10) + "\n";;
	}
	else {
		IPv6_info* ipv6_info = static_cast<IPv6_info*>(packet_info->internet_packet_info);
		show_text = show_text + "----------- IPv6Э��    -----------\n";
		show_text = show_text + "�汾�ţ�" + QString::number(ipv6_info->ipv6_ver, 10) + "\n";
		show_text = show_text + "�����ȼ���" + QString::number(ipv6_info->ipv6_hl_priority, 10) + "\n";
		show_text = show_text + "����ǩ��" + QString::number(ipv6_info->label, 16) + "\n";
		show_text = show_text + "��Ч�غɣ�" + QString::number(ipv6_info->ipv6_plen, 10) + "\n";
		show_text = show_text + "��һ���ײ���" + QString::number(ipv6_info->ipv6_nextheader, 10) + "\n";
		show_text = show_text + "�������ƣ�" + QString::number(ipv6_info->ipv6_limits, 10) + "\n";
		switch (ipv6_info->ipv6_nextheader)
		{
		case 0x01:
			show_text = show_text + "�ϲ�Э�����ͣ�ICMPЭ��\n";
			break;
		case 0x02:
			show_text = show_text + "�ϲ�Э�����ͣ�IGMPЭ��\n";
			break;
		case 0x06:
			show_text = show_text + "�ϲ�Э�����ͣ�TCPЭ��\n";
			break;
		case 0x11:
			show_text = show_text + "�ϲ�Э�����ͣ�UDPЭ��\n";
			break;
		default:
			break;
		}
		show_text = show_text + "ԴIPv6��ַ��" + QString::number(ipv6_info->ipv6_sourpa[0], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[1], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[2], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[3], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[4], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[5], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[6], 16) + ":" + QString::number(ipv6_info->ipv6_sourpa[7], 16) + "\n";
		show_text = show_text + "Ŀ��IPv6��ַ��" + QString::number(ipv6_info->ipv6_destpa[0], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[1], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[2], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[3], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[4], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[5], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[6], 16) + ":" + QString::number(ipv6_info->ipv6_destpa[7], 16) + "\n";
	}
	this->ui->textBrowser->setText(show_text);
}