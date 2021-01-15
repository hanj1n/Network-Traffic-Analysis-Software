#pragma once
#ifndef DETAIL_H
#define DETAIL_H
#include <QWidget>
#include <QDialog>
#include "ui_Detail.h"

namespace Ui {
	class Detail;
}
class Detail : public QDialog
{
	Q_OBJECT

public:
	Detail(QWidget *parent = Q_NULLPTR);
	~Detail();
	void loadData(int num,char* rule);
private:
	Ui::Detail* ui;
};
#endif
