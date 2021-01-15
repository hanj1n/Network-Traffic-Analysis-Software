#pragma warning (disable: 4996)
#include "Home.h"
#include "chart.h"
#include "Port.h"
#include<stdio.h>
#include<qfiledialog.h>
#include<qdebug.h>
#include<qdatetime.h>
#include<qmessagebox.h>
#include<string.h>
#include <cstdlib>
#include <stdio.h>  
#include <stdlib.h>
#include <pcap/pcap.h>
#pragma execution_character_set("utf-8")

Home::Home(QWidget *parent)
	: QMainWindow(parent)
{
	this->filter_clicked = 0;
	this->stop_clicked = 0;
	ui.setupUi(this);
	this->inum=-1;
	this->thread = new Thread();
	//表格初始化
	this->ui.tableWidget_search->setColumnCount(4);
	this->ui.tableWidget_search->setColumnWidth(0, 100);
	this->ui.tableWidget_search->setColumnWidth(1, 100);
	this->ui.tableWidget_search->setColumnWidth(2, 60);
	this->ui.tableWidget_search->setColumnWidth(3, 320);
	QStringList header;
	header << "源地址" << "目的地址" << "协议" << "信息";
	this->ui.tableWidget_search->setHorizontalHeaderLabels(header);
	this->count.arp = 0;
	this->count.tcp = 0;
	this->count.udp = 0;
	this->count.ipv4 = 0;
	this->count.ipv6 = 0;
	connect(this->thread, SIGNAL(new_packet(PacketInfo*)), this, SLOT(handleTimeout(PacketInfo*)), Qt::BlockingQueuedConnection);
	connect(this->ui.tableWidget_search, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(packet_detail(int,int)));
	connect(this->ui.btn_search, SIGNAL(clicked()), this, SLOT(packet_search()));
}
Home::~Home() {
	this->thread->terminate();
	this->thread->wait();
	delete this->thread;
}
void Home::file_import() {
	//打开选择文件窗口，选择导入路径
	QString fileName = QFileDialog::getOpenFileName(this, "import path", "../", "Files (*.pac)");
	FILE* f;
	QByteArray ba = fileName.toLocal8Bit();
	char* path = ba.data();
	this->thread->import(path);
	this->thread->start();
}
void copy_handler(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	/* 保存数据包到堆文件 */
	pcap_dump(dumpfile, header, pkt_data);
}
void Home::file_export(){

	FILE* f_data = fopen("./data.pac", "r");
	//打开选择文件目录窗口，选择导出路径
	QString dir = QFileDialog::getExistingDirectory(this, "export path", "../");
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyyMMdd_hhmm");
	QByteArray ba = (dir+"/"+current_date+".pac").toLatin1();
	char* path = ba.data();
	FILE* f_out = fopen(path, "w");
	//文件复制
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	char source[PCAP_BUF_SIZE];
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
		return ;
	}
	pcap_dumper_t *dumpfile = pcap_dump_open(fp, path);
	pcap_loop(fp, 0, copy_handler, (unsigned char *)dumpfile);
}
void Home::view_filter(){
	if (this->filter_clicked == 0) {
		ui.lineEdit_search->hide();
		ui.btn_search->hide();
		ui.tableWidget_search->setGeometry(QRect(20, 2, 621, 411));
	}
	else {
		ui.tableWidget_search->setGeometry(QRect(20, 30, 621, 381));
		ui.lineEdit_search->show();
		ui.btn_search->show();
	}
	this->filter_clicked = this->filter_clicked ^ 1;
}
void Home::handleTimeout(PacketInfo* packet) {//更新界面数据包
	
	int rowCount = this->ui.tableWidget_search->rowCount();
	this->count = this->thread->count;
	if (this->ui.action_unshow->isChecked())
		return;
	QString type = " ";
	QString sour_addr = "";
	QString dest_addr = "";
	QString info = "";
	type = " ";
	sour_addr = "";
	dest_addr = "";
	info = "";
	this->ui.tableWidget_search->insertRow(rowCount);
	if (packet->transmission_packet_info->arp_check == 1) {
		type = "ARP";
		ARP_info* arp_info = static_cast<ARP_info*>(packet->transmission_packet_info);
		sour_addr = QString::number(arp_info->arp_senderMAC[0], 16);
		for (int i = 1; i < 6; i++) {
			sour_addr = sour_addr + ":" + QString::number(arp_info->arp_senderMAC[i], 16);
		}
		dest_addr = QString::number(arp_info->arp_targetMAC[0], 10);
		for (int i = 1; i < 6; i++) {
			dest_addr = dest_addr + ":" + QString::number(arp_info->arp_targetMAC[i], 16);
		}
		info = info + "上层协议:";
		switch (arp_info->arp_pro)
		{
		case 0x800:
			info = info + "IPv4  ";
			break;
		case 0x806:
			info = info + "ARP  ";
			break;
		default:
			info = info + "其他  ";
			break;
		}
		switch (arp_info->operation_code)
		{
		case 1:
			info = info + "操作:ARP请求  ";
			break;
		case 2:
			info = info + "操作:ARP应答  ";
			break;
		case 3:
			info = info + "操作:RARP请求  ";
			break;
		case 4:
			info = info + "操作:RARP应答  ";
			break;
		default:
			break;
		}
		info = info + QString::number(arp_info->arp_senderIP[0], 10) + "." + QString::number(arp_info->arp_senderIP[1], 10) + "." + QString::number(arp_info->arp_senderIP[2], 10) + "." + QString::number(arp_info->arp_senderIP[3], 10) + "->";
		info = info + QString::number(arp_info->arp_targetIP[0], 10) + "." + QString::number(arp_info->arp_targetIP[1], 10) + "." + QString::number(arp_info->arp_targetIP[2], 10) + "." + QString::number(arp_info->arp_targetIP[3], 10);
	}
	else if (packet->transmission_packet_info->tcp_check == 1) {
		type = "TCP";
		TCP_info*tcp_info = static_cast<TCP_info*>(packet->transmission_packet_info);
		info = QString::number(tcp_info->tcp_sourport, 10);
		info = info + "->" + QString::number(tcp_info->tcp_destport, 10)+"  ";
		info = info + "Seq:" + QString::number(tcp_info->tcp_seqnu, 10) + "  ";
		info = info + "Ack:" + QString::number(tcp_info->tcp_acknu, 10) + "  ";
		info = info + "[ ";
		if (tcp_info->tcp_reserved & 32)
			info = info + "UGR ";
		if (tcp_info->tcp_reserved & 16)
			info = info + "ACK ";
		if (tcp_info->tcp_reserved & 8)
			info = info + "PSH ";
		if (tcp_info->tcp_reserved & 4)
			info = info + "RST ";
		if (tcp_info->tcp_reserved & 2)
			info = info + "SYN ";
		if (tcp_info->tcp_reserved & 1)
			info = info + "FIN ";
		info = info + "]  ";
		info = info + "Win:" + QString::number(tcp_info->tcp_window, 10);
		if (packet->internet_packet_info->ipv4_check == 1) {
			IPv4_info*ipv4_info = static_cast<IPv4_info*>(packet->internet_packet_info);
			sour_addr = QString::number(ipv4_info->ipv4_sourpa[0], 10);
			for (int i = 1; i < 4; i++) {
				sour_addr = sour_addr + "." + QString::number(ipv4_info->ipv4_sourpa[i], 10);
			}
			dest_addr = QString::number(ipv4_info->ipv4_destpa[0], 10);
			for (int i = 1; i < 4; i++) {
				dest_addr = dest_addr + "." + QString::number(ipv4_info->ipv4_destpa[i], 10);
			}
		}
		else {
			IPv6_info*ipv6_info = static_cast<IPv6_info*>(packet->internet_packet_info);
			sour_addr = QString::number(ipv6_info->ipv6_sourpa[0], 16);
			for (int i = 1; i < 8; i++) {
				sour_addr = sour_addr + ":" + QString::number(ipv6_info->ipv6_sourpa[i], 16);
			}
			dest_addr = QString::number(ipv6_info->ipv6_destpa[0], 16);
			for (int i = 1; i < 8; i++) {
				dest_addr = dest_addr + ":" + QString::number(ipv6_info->ipv6_destpa[i], 16);
			}
		}
	}
	else if (packet->transmission_packet_info->udp_check == 1) {
		type = "UDP";
		UDP_info*udp_info = static_cast<UDP_info*>(packet->transmission_packet_info);
		info = QString::number(udp_info->udp_sourport, 10);
		info = info + "->" + QString::number(udp_info->udp_destport, 10)+"  ";
		u_short udp_destport = udp_info->udp_destport;
		switch (udp_destport)
		{
		case 80:
			info = info + "上层协议:HTTP  ";
			break;
		case 21:
			info = info + "上层协议:FTP  ";
			break;
		case 23:
			info = info + "上层协议:TELNET  ";
			break;
		case 25:
			info = info + "上层协议:SMTP  ";
			break;
		case 110:
			info = info + "上层协议：POP3  ";
			break;
		default:
			break;
		}
		info = info + "UDP总长度:" + QString::number(udp_info->udp_hlen, 10) + "  ";
		info = info + + "校验和:" + QString::number(udp_info->udp_crc, 16) + "  ";

		if (packet->internet_packet_info->ipv4_check == 1) {
			IPv4_info*ipv4_info = static_cast<IPv4_info*>(packet->internet_packet_info);
			sour_addr = QString::number(ipv4_info->ipv4_sourpa[0], 10);
			for (int i = 1; i < 4; i++) {
				sour_addr = sour_addr + "." + QString::number(ipv4_info->ipv4_sourpa[i], 10);
			}
			dest_addr = QString::number(ipv4_info->ipv4_destpa[0], 10);
			for (int i = 1; i < 4; i++) {
				dest_addr = dest_addr + "." + QString::number(ipv4_info->ipv4_destpa[i], 10);
			}
		}
		else {
			IPv6_info*ipv6_info = static_cast<IPv6_info*>(packet->internet_packet_info);
			sour_addr = QString::number(ipv6_info->ipv6_sourpa[0], 16);
			for (int i = 1; i < 8; i++) {
				sour_addr = sour_addr + ":" + QString::number(ipv6_info->ipv6_sourpa[i], 16);
			}
			dest_addr = QString::number(ipv6_info->ipv6_destpa[0], 16);
			for (int i = 1; i < 8; i++) {
				dest_addr = dest_addr + ":" + QString::number(ipv6_info->ipv6_destpa[i], 16);
			}
		}
	}
	this->ui.tableWidget_search->setItem(rowCount, 0, new QTableWidgetItem(sour_addr));
	this->ui.tableWidget_search->setItem(rowCount, 1, new QTableWidgetItem(dest_addr));
	this->ui.tableWidget_search->setItem(rowCount, 2, new QTableWidgetItem(type));
	this->ui.tableWidget_search->setItem(rowCount, 3, new QTableWidgetItem(info));

}
void Home::capture_start(){
	this->ui.action_start->setEnabled(false);
	this->ui.action_stop->setEnabled(true);
	this->ui.action_end->setEnabled(false);
	this->ui.tableWidget_search->clearContents();
	int rowNum = this->ui.tableWidget_search->rowCount();
	for (int i = 0; i < rowNum; i++)
		this->ui.tableWidget_search->removeRow(0);
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	/* 获取本机设备列表 */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
	}
	this->alldevs = alldevs;
	Port* a = new Port;
	a->setData(alldevs);
	if (!a->exec())
		this->inum = a->getPort();
	a->setAttribute(Qt::WA_DeleteOnClose);
	/* 跳转到选中的适配器 */
	for (d = alldevs, i = 0; i < this->inum - 1; d = d->next, i++);
	/* 打开设备 */
	if ((this->adhandle = pcap_open(d->name,          // 设备名
		65536,            // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
		PCAP_OPENFLAG_PROMISCUOUS,    // 混杂模式
		1000,             // 读取超时时间
		NULL,             // 远程机器验证
		errbuf            // 错误缓冲池
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return;
	}
	/* 开始捕获 */
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	int res;
	this->thread->init(this->adhandle);
	this->thread->start();
	return;
}
void Home::capture_stop(){
	this->ui.action_start->setEnabled(false);
	this->ui.action_stop->setEnabled(true);
	if (this->stop_clicked == 0) {//暂停
		this->ui.action_stop->setText("\347\273\247\347\273\255");
		//this->m_pTimer->stop();
		this->thread->close();
		this->ui.action_end->setEnabled(true);
	}
	else {//继续
		this->ui.action_stop->setText("\346\232\202\345\201\234");
		this->thread->tcontinue();
		//this->m_pTimer->start();
		this->ui.action_end->setEnabled(false);
	}
	this->stop_clicked = this->stop_clicked ^ 1;
}
void Home::capture_end(){
	this->ui.action_start->setEnabled(true);
	this->ui.action_stop->setEnabled(false);
	this->ui.action_end->setEnabled(false);
	QThread::sleep(1);
	this->thread->terminate();
	this->thread->wait();
	this->thread = new Thread();
	connect(this->thread, SIGNAL(new_packet(PacketInfo*)), this, SLOT(handleTimeout(PacketInfo*)), Qt::BlockingQueuedConnection);
	this->stop_clicked = 0;
	this->ui.action_stop->setText("\346\232\202\345\201\234");
	printf("end\n");
	this->ui.tableWidget_search->clearContents();
	int rowNum = this->ui.tableWidget_search->rowCount();
	for (int i = 0; i < rowNum; i++)
		this->ui.tableWidget_search->removeRow(0);
	return;
}
void Home::statistics_chart() {
	Chart* a = new Chart;
	a->init(this->count.ipv4, this->count.ipv6, this->count.arp, this->count.tcp, this->count.udp);
	a->show();
	a->setAttribute(Qt::WA_DeleteOnClose);
}
void Home::statistics_IPv4(){

}
void Home::statistics_IPv6(){

}
void Home::statistics_UDP(){

}
void Home::statistics_TCP(){

}
void Home::statistics_ARP(){

}
void Home::about() {
	QMessageBox::about(this, "about", "SCUT\nCS\nInformation Security\nAnnie");
}
void Home::exit() {
	this->close();
}
void Home::packet_detail(int row, int column) {
	Detail* detail_dialog = new Detail;
	QString text = this->ui.lineEdit_search->text();
	char*  rule;
	QByteArray ba = text.toLatin1(); // must
	rule = ba.data();
	detail_dialog->loadData(row, rule);
	detail_dialog->exec();
	detail_dialog->setAttribute(Qt::WA_DeleteOnClose);
}
void Home::packet_search() {
	QString text = this->ui.lineEdit_search->text();
	char*  rule;
	QByteArray ba = text.toLatin1(); // must
	rule = ba.data();
	this->ui.tableWidget_search->clearContents();
	int rowNum = this->ui.tableWidget_search->rowCount();
	for (int i = 0; i < rowNum; i++)
		this->ui.tableWidget_search->removeRow(0);

	this->thread = new Thread();
	connect(this->thread, SIGNAL(new_packet(PacketInfo*)), this, SLOT(handleTimeout(PacketInfo*)), Qt::BlockingQueuedConnection);
	bool flag = this->thread->filerPacket(rule);
	if (flag == true)
		this->thread->start();
}