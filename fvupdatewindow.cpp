#include "fvupdatewindow.h"
#include "ui_fvupdatewindow.h"
#include <QTranslator>
#include <QTextCodec>
#include <QApplication>
#include <QLibraryInfo>
#include <QIcon>
#include <QGraphicsScene>


FvUpdateWindow::FvUpdateWindow(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::FvUpdateWindow)
{
	m_ui->setupUi(this);

	// Initialize translation
	installTranslator();

	// Set application icon
	QIcon appIcon = QApplication::windowIcon();
	QGraphicsScene appIconScene;
	appIconScene.addPixmap(appIcon.pixmap(m_ui->appIconGraphicsView->size()));

	QString newVersString = m_ui->newVersionIsAvailableLabel->text().arg(QApplication::applicationName());
	m_ui->newVersionIsAvailableLabel->setText(newVersString);
}

FvUpdateWindow::~FvUpdateWindow()
{
	delete m_ui;
}

void FvUpdateWindow::SetSuggestedApplicationVersion(QString suggestedApplicationVersion)
{
	m_suggestedApplicationVersion = suggestedApplicationVersion;

	QString downloadString = m_ui->wouldYouLikeToDownloadLabel->text().arg(QApplication::applicationName(), suggestedApplicationVersion, QApplication::applicationVersion());
	m_ui->wouldYouLikeToDownloadLabel->setText(downloadString);
}

void FvUpdateWindow::SetReleaseNotesURL(QString releaseNotesUrl)
{
	m_releaseNotesUrl = QUrl(releaseNotesUrl);

	m_ui->releaseNotesWebView->stop();
	m_ui->releaseNotesWebView->load(m_releaseNotesUrl);
}

void FvUpdateWindow::installTranslator()
{
	QTranslator translator;
	QString locale = QLocale::system().name();
	translator.load(QString("fervor_") + locale);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	qApp->installTranslator(&translator);
}
