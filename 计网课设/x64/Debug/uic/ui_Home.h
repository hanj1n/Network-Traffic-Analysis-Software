/********************************************************************************
** Form generated from reading UI file 'Home.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeClass
{
public:
    QAction *action_import;
    QAction *action_export;
    QAction *action_start;
    QAction *action_stop;
    QAction *action_filter;
    QAction *action_restart;
    QAction *action_exit;
    QAction *action_UDP;
    QAction *action_TCP;
    QAction *action_ARP;
    QAction *action_IPv4;
    QAction *action_IPv6;
    QAction *action_HTTP;
    QAction *action_DHCP;
    QAction *action_DNS;
    QAction *action_developer;
    QAction *action_chart;
    QAction *action_IPv4_statistics;
    QAction *action_3;
    QAction *action_IPv6_statistics;
    QWidget *centralWidget;
    QListView *listView_search;
    QLineEdit *lineEdit_search;
    QPushButton *btn_search;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_statistics;
    QMenu *menu_capture;
    QMenu *menu_view;
    QMenu *menu_about;

    void setupUi(QMainWindow *HomeClass)
    {
        if (HomeClass->objectName().isEmpty())
            HomeClass->setObjectName(QStringLiteral("HomeClass"));
        HomeClass->resize(663, 456);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HomeClass->sizePolicy().hasHeightForWidth());
        HomeClass->setSizePolicy(sizePolicy);
        HomeClass->setMinimumSize(QSize(663, 456));
        HomeClass->setMaximumSize(QSize(663, 456));
        HomeClass->setStyleSheet(QStringLiteral(""));
        action_import = new QAction(HomeClass);
        action_import->setObjectName(QStringLiteral("action_import"));
        action_import->setCheckable(false);
        action_export = new QAction(HomeClass);
        action_export->setObjectName(QStringLiteral("action_export"));
        action_start = new QAction(HomeClass);
        action_start->setObjectName(QStringLiteral("action_start"));
        action_stop = new QAction(HomeClass);
        action_stop->setObjectName(QStringLiteral("action_stop"));
        action_filter = new QAction(HomeClass);
        action_filter->setObjectName(QStringLiteral("action_filter"));
        action_filter->setCheckable(true);
        action_filter->setChecked(true);
        action_restart = new QAction(HomeClass);
        action_restart->setObjectName(QStringLiteral("action_restart"));
        action_exit = new QAction(HomeClass);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_UDP = new QAction(HomeClass);
        action_UDP->setObjectName(QStringLiteral("action_UDP"));
        action_TCP = new QAction(HomeClass);
        action_TCP->setObjectName(QStringLiteral("action_TCP"));
        action_ARP = new QAction(HomeClass);
        action_ARP->setObjectName(QStringLiteral("action_ARP"));
        action_IPv4 = new QAction(HomeClass);
        action_IPv4->setObjectName(QStringLiteral("action_IPv4"));
        action_IPv6 = new QAction(HomeClass);
        action_IPv6->setObjectName(QStringLiteral("action_IPv6"));
        action_HTTP = new QAction(HomeClass);
        action_HTTP->setObjectName(QStringLiteral("action_HTTP"));
        action_DHCP = new QAction(HomeClass);
        action_DHCP->setObjectName(QStringLiteral("action_DHCP"));
        action_DNS = new QAction(HomeClass);
        action_DNS->setObjectName(QStringLiteral("action_DNS"));
        action_developer = new QAction(HomeClass);
        action_developer->setObjectName(QStringLiteral("action_developer"));
        action_chart = new QAction(HomeClass);
        action_chart->setObjectName(QStringLiteral("action_chart"));
        action_IPv4_statistics = new QAction(HomeClass);
        action_IPv4_statistics->setObjectName(QStringLiteral("action_IPv4_statistics"));
        action_3 = new QAction(HomeClass);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_IPv6_statistics = new QAction(HomeClass);
        action_IPv6_statistics->setObjectName(QStringLiteral("action_IPv6_statistics"));
        centralWidget = new QWidget(HomeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        listView_search = new QListView(centralWidget);
        listView_search->setObjectName(QStringLiteral("listView_search"));
        listView_search->setGeometry(QRect(20, 30, 621, 381));
        lineEdit_search = new QLineEdit(centralWidget);
        lineEdit_search->setObjectName(QStringLiteral("lineEdit_search"));
        lineEdit_search->setGeometry(QRect(20, 0, 591, 25));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        lineEdit_search->setFont(font);
        btn_search = new QPushButton(centralWidget);
        btn_search->setObjectName(QStringLiteral("btn_search"));
        btn_search->setGeometry(QRect(616, 0, 25, 25));
        btn_search->setStyleSheet(QString::fromUtf8("background-image: url(:/Home/icon/\350\277\233\345\205\245.png);\n"
"background-color: rgb(255, 255, 255);"));
        HomeClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(HomeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HomeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HomeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HomeClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(HomeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 663, 18));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QStringLiteral("menu_file"));
        menu_statistics = new QMenu(menuBar);
        menu_statistics->setObjectName(QStringLiteral("menu_statistics"));
        menu_capture = new QMenu(menuBar);
        menu_capture->setObjectName(QStringLiteral("menu_capture"));
        menu_view = new QMenu(menuBar);
        menu_view->setObjectName(QStringLiteral("menu_view"));
        menu_about = new QMenu(menuBar);
        menu_about->setObjectName(QStringLiteral("menu_about"));
        HomeClass->setMenuBar(menuBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_view->menuAction());
        menuBar->addAction(menu_capture->menuAction());
        menuBar->addAction(menu_statistics->menuAction());
        menuBar->addAction(menu_about->menuAction());
        menu_file->addAction(action_import);
        menu_file->addSeparator();
        menu_file->addAction(action_export);
        menu_file->addSeparator();
        menu_file->addAction(action_exit);
        menu_statistics->addAction(action_chart);
        menu_statistics->addAction(action_IPv4_statistics);
        menu_statistics->addAction(action_IPv6_statistics);
        menu_capture->addAction(action_start);
        menu_capture->addAction(action_stop);
        menu_capture->addAction(action_restart);
        menu_view->addAction(action_filter);
        menu_about->addAction(action_developer);

        retranslateUi(HomeClass);
        QObject::connect(action_import, SIGNAL(triggered()), HomeClass, SLOT(file_import()));
        QObject::connect(action_export, SIGNAL(triggered()), HomeClass, SLOT(file_export()));
        QObject::connect(action_exit, SIGNAL(triggered()), HomeClass, SLOT(close()));
        QObject::connect(action_filter, SIGNAL(triggered()), HomeClass, SLOT(view_filter()));
        QObject::connect(action_start, SIGNAL(triggered()), HomeClass, SLOT(capture_start()));
        QObject::connect(action_stop, SIGNAL(triggered()), HomeClass, SLOT(capture_end()));
        QObject::connect(action_restart, SIGNAL(triggered()), HomeClass, SLOT(capture_restart()));
        QObject::connect(action_developer, SIGNAL(triggered()), HomeClass, SLOT(about()));
        QObject::connect(action_chart, SIGNAL(triggered()), HomeClass, SLOT(statistics_chart()));

        QMetaObject::connectSlotsByName(HomeClass);
    } // setupUi

    void retranslateUi(QMainWindow *HomeClass)
    {
        HomeClass->setWindowTitle(QApplication::translate("HomeClass", "\347\275\221\347\273\234\346\265\201\351\207\217\345\210\206\346\236\220\350\275\257\344\273\266", nullptr));
        action_import->setText(QApplication::translate("HomeClass", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
        action_export->setText(QApplication::translate("HomeClass", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        action_start->setText(QApplication::translate("HomeClass", "\345\274\200\345\247\213", nullptr));
        action_stop->setText(QApplication::translate("HomeClass", "\345\201\234\346\255\242", nullptr));
        action_filter->setText(QApplication::translate("HomeClass", "\350\277\207\346\273\244\345\231\250", nullptr));
        action_restart->setText(QApplication::translate("HomeClass", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        action_exit->setText(QApplication::translate("HomeClass", "\351\200\200\345\207\272", nullptr));
        action_UDP->setText(QApplication::translate("HomeClass", "UDP", nullptr));
        action_TCP->setText(QApplication::translate("HomeClass", "TCP", nullptr));
        action_ARP->setText(QApplication::translate("HomeClass", "ARP", nullptr));
        action_IPv4->setText(QApplication::translate("HomeClass", "IPv4", nullptr));
        action_IPv6->setText(QApplication::translate("HomeClass", "IPv6", nullptr));
        action_HTTP->setText(QApplication::translate("HomeClass", "HTTP", nullptr));
        action_DHCP->setText(QApplication::translate("HomeClass", "DHCP", nullptr));
        action_DNS->setText(QApplication::translate("HomeClass", "DNS", nullptr));
        action_developer->setText(QApplication::translate("HomeClass", "\345\274\200\345\217\221\350\200\205", nullptr));
        action_chart->setText(QApplication::translate("HomeClass", "\345\233\276\350\241\250", nullptr));
        action_IPv4_statistics->setText(QApplication::translate("HomeClass", "IPv4 statistics", nullptr));
        action_3->setText(QApplication::translate("HomeClass", "\350\241\250\346\240\274", nullptr));
        action_IPv6_statistics->setText(QApplication::translate("HomeClass", "IPv6 statistics", nullptr));
        lineEdit_search->setText(QString());
        btn_search->setText(QString());
        menu_file->setTitle(QApplication::translate("HomeClass", "\346\226\207\344\273\266", nullptr));
        menu_statistics->setTitle(QApplication::translate("HomeClass", "\347\273\237\350\256\241", nullptr));
        menu_capture->setTitle(QApplication::translate("HomeClass", "\346\215\225\350\216\267", nullptr));
        menu_view->setTitle(QApplication::translate("HomeClass", "\350\247\206\345\233\276", nullptr));
        menu_about->setTitle(QApplication::translate("HomeClass", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeClass: public Ui_HomeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
