#pragma once
#include <QtCharts/QChartView>
QT_CHARTS_USE_NAMESPACE
#include <QtWidgets/QMainWindow>
#include <QListWidgetItem>
#include <QHeaderView> 
#include <QObject> 
#include <QTimer> 
#include "ui_Home.h"
#include "pcap.h"
#include "Thread.h"
#include "Detail.h"

class Home : public QMainWindow
{
	Q_OBJECT

public:
	Home(QWidget *parent = Q_NULLPTR);
	~Home();
private slots:
	void file_import();
	void file_export();
	void view_filter();
	void capture_start();
	void capture_stop();
	void capture_end();
	void statistics_chart();
	void statistics_IPv4();
	void statistics_IPv6();
	void statistics_UDP();
	void statistics_TCP();
	void statistics_ARP();
	void about();
	void exit();
public slots:
	void handleTimeout(PacketInfo* packet);
	void packet_detail(int row, int column);
	void packet_search();
private:
	Ui::HomeClass ui;
	int filter_clicked;
	int stop_clicked;
	int unshow_clicked;
	int inum;
	pcap_if_t* alldevs;
	pcap_t* adhandle;
	Thread* thread;
	QTimer *m_pTimer;
	COUNT count;
};
