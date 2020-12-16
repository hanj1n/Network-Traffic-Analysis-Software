#pragma once
#include <QtCharts/QChartView>
QT_CHARTS_USE_NAMESPACE
#include <QtWidgets/QMainWindow>
#include "ui_Home.h"

class Home : public QMainWindow
{
	Q_OBJECT

public:
	Home(QWidget *parent = Q_NULLPTR);

private slots:
	void file_import();
	void file_export();
	void view_filter();
	void capture_start();
	void capture_end();
	void capture_restart();
	void statistics_chart();
	void statistics_IPv4();
	void statistics_IPv6();
	void statistics_UDP();
	void statistics_TCP();
	void statistics_ARP();
	void statistics_HTTP();
	void statistics_DHCP();
	void statistics_DNS();
	void about();
private:
	Ui::HomeClass ui;
	int filter_clicked;

};
