#pragma once
#ifndef PORT_H
#define PORT_H
#include "ui_Port.h"
#include <QWidget>
#include "pcap.h"

namespace Ui {
	class Port;
}
class Port : public QDialog
{
	Q_OBJECT

public:
	Port(QWidget *parent = Q_NULLPTR);
	~Port();
	void setData(pcap_if_t*);
	int getPort();
public slots:
	void choose_port(QModelIndex index);

private:
	Ui::Port*ui;
	int portid;
	
};
#endif