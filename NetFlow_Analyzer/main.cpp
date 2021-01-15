#include "Home.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Home w;
	w.show();
	return a.exec();
}
