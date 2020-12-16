#pragma once
#ifndef CHART_H
#define CHART_H
#include <QtWidgets/QWidget>

namespace Ui {
	class Chart;
}

class Chart : public QWidget
{
	Q_OBJECT

public:
	Chart(QWidget *parent = 0);

private:
	Ui::Chart* ui;
};
#endif
