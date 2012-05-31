#include "fvupdatewindow.h"
#include "ui_fvupdatewindow.h"
#include "fvupdateconfig.h"
#include <QTranslator>
#include <QTextCodec>
#include <QApplication>
#include <QLibraryInfo>
#include <QDebug>
#include <QIcon>
#include <QGraphicsScene>


#ifndef FV_APP_NAME
#	error "FV_APP_NAME is undefined (must have been defined by Fervor.pri)"
#endif
#ifndef FV_APP_VERSION
#	error "FV_APP_VERSION is undefined (must have been defined by Fervor.pri)"
#endif


FvUpdateWindow::FvUpdateWindow(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::FvUpdateWindow)
{
	m_ui->setupUi(this);

	// Initialize translation
	installTranslator();

	// Set application name / version is not set yet
	if (QApplication::applicationName().isEmpty()) {
		QString appName = QString::fromUtf8(FV_APP_NAME);
		qWarning() << "QApplication::applicationName is not set, setting it to '" << appName << "'";
		QApplication::setApplicationName(appName);
	}
	if (QApplication::applicationVersion().isEmpty()) {
		QString appVersion = QString::fromUtf8(FV_APP_VERSION);
		qWarning() << "QApplication::applicationVersion is not set, setting it to '" << appVersion << "'";
		QApplication::setApplicationVersion(appVersion);
	}

	// Set application icon
	QIcon appIcon = QApplication::windowIcon();
	QGraphicsScene appIconScene;
	appIconScene.addPixmap(appIcon.pixmap(m_ui->appIconGraphicsView->size()));

	QString newVersString = m_ui->newVersionIsAvailableLabel->text().arg(QApplication::applicationName());
	m_ui->newVersionIsAvailableLabel->setText(newVersString);

	QString downloadString = m_ui->wouldYouLikeToDownloadLabel->text().arg(QApplication::applicationName(), "newvers", QApplication::applicationVersion());
	m_ui->wouldYouLikeToDownloadLabel->setText(downloadString);
}

FvUpdateWindow::~FvUpdateWindow()
{
	delete m_ui;
}

void FvUpdateWindow::installTranslator()
{
	QTranslator translator;
	QString locale = QLocale::system().name();
	translator.load(QString("fervor_") + locale);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	qApp->installTranslator(&translator);
}
