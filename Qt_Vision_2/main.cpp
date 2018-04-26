#include "Qt_Vision_2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qt_Vision_2 w;

	w.show();
	return a.exec();
}
