#include "Home.h"
#include "chart.h"
#include<stdio.h>
#include<qfiledialog.h>
#include<qdebug.h>
#include<qdatetime.h>
#include<qmessagebox.h>
#include<string.h>

Home::Home(QWidget *parent)
	: QMainWindow(parent)
{
	this->filter_clicked = 0;
	ui.setupUi(this);
}
void Home::file_import() {
	//打开选择文件窗口，选择导入路径
	QString fileName = QFileDialog::getOpenFileName(this, "import path", "../", "Files (*.pac)");
	FILE* f;
	QByteArray ba = fileName.toLatin1();
	char* path = ba.data();
	f = fopen(path, "r");
	//导入数据
}
void Home::file_export(){
	//打开选择文件目录窗口，选择导出路径
	QString dir = QFileDialog::getExistingDirectory(this, "export path", "../");
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyyMMdd_hhmm");
	FILE* f;
	QByteArray ba = (dir+"/"+current_date+".pac").toLatin1();
	char* path = ba.data();
	f = fopen(path, "w");
	//导出数据
}
void Home::view_filter(){
	if (this->filter_clicked == 0) {
		ui.lineEdit_search->hide();
		ui.btn_search->hide();
		ui.listView_search->setGeometry(QRect(20, 0, 621, 411));
	}
	else {
		ui.listView_search->setGeometry(QRect(20, 30, 621, 381));
		ui.lineEdit_search->show();
		ui.btn_search->show();
	}
	this->filter_clicked = this->filter_clicked ^ 1;
}
void Home::capture_start(){
	//开始抓包
}
void Home::capture_end(){
	//暂停抓包
}
void Home::capture_restart(){
	//重新开始抓包
}
void Home::statistics_chart() {
	Chart* a = new Chart;
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
void Home::statistics_HTTP(){

}
void Home::statistics_DHCP(){

}
void Home::statistics_DNS(){

}
void Home::about() {
	QMessageBox::about(this, "about", "SCUT\nCS\nInformation Security\nAnnie");
}