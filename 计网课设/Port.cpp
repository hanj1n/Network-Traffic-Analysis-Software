#include "Port.h"
#include <qstringlistmodel.h>
#include <qmessagebox.h>

void Port::setData(pcap_if_t*alldevs) {
	pcap_if_t *d;
	int i = 0;
	QStringList list;
	for (d = alldevs; d; d = d->next)
	{
		if (d->description)
			list << d->description;
	}

	if (i == 0) {
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
	}
	QStringListModel *model = new QStringListModel(list);     //创建对象，并用字符串队列初始化
	ui->listView->setModel(model);
}
Port::Port(QWidget *parent):
	QDialog(parent), ui(new Ui::Port)
{
	this->portid = -1;
	ui->setupUi(this);
	ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void Port::choose_port(QModelIndex index) {
	this->portid=index.row();
}
int Port::getPort() {
	return this->portid;
}
Port::~Port()
{

}

