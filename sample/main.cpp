#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setApplicationVersion(APP_VERSION);

	MainWindow w;
	w.show();
	
	return a.exec();
}
