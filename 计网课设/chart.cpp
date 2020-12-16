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
	//统计IPv4与IPv6占比

	// 构造饼状图，IPv4数据显示绿色，IPv6数据显示蓝色
	QPieSlice *slice_1 = new QPieSlice(QStringLiteral("IPv4"), 0.6, this);
	slice_1->setLabelVisible(true); // 显示饼状区对应的数据label
	slice_1->setBrush(Qt::green);
	QPieSlice *slice_2 = new QPieSlice(QStringLiteral("IPv6"), 0.4, this);
	slice_2->setLabelVisible(true);
	slice_2->setBrush(Qt::blue);
	QPieSeries *pseries = new QPieSeries();
	pseries->append(slice_1);
	pseries->append(slice_2);
	QChart *chart = new QChart();
	chart->addSeries(pseries);
	chart->setTitle("统计IPv4 IPv6报文情况");
	chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
	ui->widget_left->setChart(chart);
	ui->widget_left->setRenderHint(QPainter::Antialiasing);
	//统计TCP UDP ARP
	//构造柱状图
	QBarSet *set_data = new QBarSet("");
	*set_data << 1 << 2 << 3;
	set_data->setBrush(QColor(52, 152, 219));
	QBarSeries *bseries = new QBarSeries();
	bseries->append(set_data);
	chart = new QChart();
	chart->addSeries(bseries);
	chart->setTitle("统计TCP UDP ARP报文情况");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	QStringList categories;
	categories << "TCP" << "UDP" << "ARP";
	QBarCategoryAxis *axis = new QBarCategoryAxis();
	axis->append(categories);
	chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
	chart->setAxisX(axis, bseries);//设置坐标轴
	chart->legend()->setVisible(false); //设置图例为显示状态
	chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部
	chart->addSeries(bseries);
	chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
	ui->widget_right->setChart(chart);
	ui->widget_right->setRenderHint(QPainter::Antialiasing);
}