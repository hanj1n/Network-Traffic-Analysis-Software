/********************************************************************************
** Form generated from reading UI file 'chart.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHART_H
#define UI_CHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_Chart
{
public:
    QChartView *widget_left;
    QChartView *widget_right;

    void setupUi(QWidget *Chart)
    {
        if (Chart->objectName().isEmpty())
            Chart->setObjectName(QStringLiteral("Chart"));
        Chart->resize(484, 381);
        widget_left = new QChartView(Chart);
        widget_left->setObjectName(QStringLiteral("widget_left"));
        widget_left->setGeometry(QRect(-10, 50, 241, 231));
        widget_right = new QChartView(Chart);
        widget_right->setObjectName(QStringLiteral("widget_right"));
        widget_right->setGeometry(QRect(210, 50, 281, 231));

        retranslateUi(Chart);

        QMetaObject::connectSlotsByName(Chart);
    } // setupUi

    void retranslateUi(QWidget *Chart)
    {
        Chart->setWindowTitle(QApplication::translate("Chart", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chart: public Ui_Chart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHART_H
