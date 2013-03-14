#if QT_VERSION <= 0x050000
    #include <QApplication>
#else
    #include <QtGui/QApplication>
#endif

#include "mainwindow.h"
#include "fvupdater.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	// Prerequisite for the Fervor updater
	QApplication::setOrganizationName("pypt");
	QApplication::setOrganizationDomain("pypt.lt");
	QApplication::setApplicationName("Sample");
    QApplication::setApplicationVersion("1.0");

	// Set feed URL before doing anything else
	FvUpdater::sharedUpdater()->SetFeedURL("https://www.dannhauer.de/swupdates/appcast_fervor.xml");
    FvUpdater::sharedUpdater()->setRequiredSslFingerPrint("d7e0f2fc899f5ec4456300c7061ff1da");	// Optional
	FvUpdater::sharedUpdater()->setHtAuthCredentials("swupdates", "updatepw");	// Optional
    FvUpdater::sharedUpdater()->setSkipVersionAllowed(false);	// Optional
    FvUpdater::sharedUpdater()->setRemindLaterAllowed(false);	// Optional
	// Finish Up old Updates
	FvUpdater::sharedUpdater()->finishUpdate();

	// Check for updates automatically
	FvUpdater::sharedUpdater()->CheckForUpdatesSilent();

	// Show main window
	MainWindow w;
	w.show();
	
	return a.exec();
}
