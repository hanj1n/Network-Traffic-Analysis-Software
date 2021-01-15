#pragma execution_character_set("utf-8")
#include"chart.h"
#include<stdio.h>
#include<qfiledialog.h>
#include<qdebug.h>
#include<qdatetime.h>
#include<qmessagebox.h>
#include<string.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
QT_CHARTS_USE_NAMESPACE
#include"ui_chart.h"

Chart::Chart(QWidget *parent):
	QWidget(parent),ui(new Ui::Chart)
{
	ui->setupUi(this);
}
void Chart::init(int ipv4_num, int ipv6_num, int arp_num, int tcp_num, int udp_num) 
{
	//ͳ��IPv4��IPv6ռ��
	double pipv4 = ipv4_num*1.0 / (ipv4_num + ipv6_num);
	// �����״ͼ��IPv4������ʾ��ɫ��IPv6������ʾ��ɫ
	QPieSlice *slice_1 = new QPieSlice(QStringLiteral("IPv4"), pipv4, this);
	//slice_1->setLabelVisible(true); // ��ʾ��״����Ӧ������label
	slice_1->setBrush(Qt::green);
	QPieSlice *slice_2 = new QPieSlice(QStringLiteral("IPv6"), 1-pipv4, this);
	//slice_2->setLabelVisible(true);
	slice_2->setBrush(Qt::blue);
	QPieSeries *pseries = new QPieSeries();
	pseries->append(slice_1);
	pseries->append(slice_2);
	QChart *chart = new QChart();
	chart->addSeries(pseries);
	chart->setTitle("ͳ��IPv4 IPv6�������");
	chart->setAnimationOptions(QChart::AllAnimations); // ������ʾʱ�Ķ���Ч��
	ui->widget_left->setChart(chart);
	ui->widget_left->setRenderHint(QPainter::Antialiasing);
	//ͳ��TCP UDP ARP
	//������״ͼ
	QBarSet *set_data = new QBarSet("");
	*set_data << tcp_num << udp_num << arp_num;
	set_data->setBrush(QColor(52, 152, 219));
	QBarSeries *bseries = new QBarSeries();
	bseries->append(set_data);
	chart = new QChart();
	chart->addSeries(bseries);
	chart->setTitle("ͳ��TCP UDP ARP�������");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	QStringList categories;
	categories << "TCP" << "UDP" << "ARP";
	QBarCategoryAxis *axis = new QBarCategoryAxis();
	axis->append(categories);
	chart->createDefaultAxes();//����Ĭ�ϵ����������ᣨ���� QBarSet ���õ�ֵ��
	chart->setAxisX(axis, bseries);//����������
	chart->legend()->setVisible(false); //����ͼ��Ϊ��ʾ״̬
	chart->legend()->setAlignment(Qt::AlignBottom);//����ͼ������ʾλ���ڵײ�
	chart->addSeries(bseries);
	chart->setAnimationOptions(QChart::AllAnimations); // ������ʾʱ�Ķ���Ч��
	ui->widget_right->setChart(chart);
	ui->widget_right->setRenderHint(QPainter::Antialiasing);
	QString text = "IPv4: " + QString::number(ipv4_num, 10) + "  IPv6: " + QString::number(ipv6_num, 10) + "  TCP: " + QString::number(tcp_num, 10) + "  UDP: " + QString::number(udp_num, 10) + "  ARP: " + QString::number(arp_num, 10);
	ui->label->setText(text);
	
}