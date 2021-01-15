#pragma once
#ifndef CHART_H
#define CHART_H
#include <QtWidgets/QWidget>
#include <qlabel.h>

namespace Ui {
	class Chart;
}

class Chart : public QWidget
{
	Q_OBJECT

public:
	Chart(QWidget *parent = 0);
	void init(int ipv4_num, int ipv6_num, int arp_num, int tcp_num, int udp_num);
private:
	Ui::Chart* ui;
};
#endif
