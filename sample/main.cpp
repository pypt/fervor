#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Prerequisite for the Fervor updater
	QApplication::setOrganizationName("pypt");
	QApplication::setOrganizationDomain("pypt.lt");

	MainWindow w;
	w.show();
	
	return a.exec();
}
