#include "fvupdater.h"
#include "fvupdatewindow.h"
#include "fvplatform.h"
#include "fvignoredversions.h"
#include <QApplication>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>

#ifndef FV_APP_NAME
#	error "FV_APP_NAME is undefined (must have been defined by Fervor.pri)"
#endif
#ifndef FV_APP_VERSION
#	error "FV_APP_VERSION is undefined (must have been defined by Fervor.pri)"
#endif


#ifdef FV_DEBUG
// Unit tests
#include "fvversioncomparatortest.h"
#endif


FvUpdater* FvUpdater::m_Instance = 0;


FvUpdater* FvUpdater::sharedUpdater()
{
	static QMutex mutex;
	if (! m_Instance) {
		mutex.lock();

		if (! m_Instance) {
			m_Instance = new FvUpdater;
		}

		mutex.unlock();
	}

	return m_Instance;
}

void FvUpdater::drop()
{
	static QMutex mutex;
	mutex.lock();
	delete m_Instance;
	m_Instance = 0;
	mutex.unlock();
}

FvUpdater::FvUpdater() : QObject(0)
{
	m_updaterWindow = 0;

#ifdef FV_DEBUG
	// Unit tests
	FvVersionComparatorTest* test = new FvVersionComparatorTest();
	test->runAll();
	delete test;
#endif

}

FvUpdater::~FvUpdater()
{
	destroyUpdaterWindow();
}

void FvUpdater::destroyUpdaterWindow()
{
	if (m_updaterWindow) {
		m_updaterWindow->hide();
		delete m_updaterWindow;
		m_updaterWindow = 0;
	}
}


void FvUpdater::SetFeedURL(QString feedURL)
{
	m_feedURL = QUrl(feedURL);
}

QString FvUpdater::GetFeedURL()
{
	return m_feedURL.toString();
}


bool FvUpdater::CheckForUpdates(bool notifyAboutUpToDateApplication)
{
	if (m_feedURL.isEmpty()) {
		qCritical() << "Please set feed URL via setFeedURL() before calling CheckForUpdates().";
		return false;
	}

	m_showDialogEvenIfNoUpdatesWereFound = notifyAboutUpToDateApplication;

	// Check if application's organization name and domain are set, fail otherwise
	// (nowhere to store QSettings to)
	if (QApplication::organizationName().isEmpty()) {
		qCritical() << "QApplication::organizationName is not set. Please do that.";
		return false;
	}
	if (QApplication::organizationDomain().isEmpty()) {
		qCritical() << "QApplication::organizationDomain is not set. Please do that.";
		return false;
	}

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

	m_httpRequestAborted = false;
	startDownloadFeed(m_feedURL);

	return true;
}

void FvUpdater::startDownloadFeed(QUrl url)
{
	m_xml.clear();

	m_reply = m_qnam.get(QNetworkRequest(url));

	connect(m_reply, SIGNAL(readyRead()), this, SLOT(httpFeedReadyRead()));
	connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(httpFeedUpdateDataReadProgress(qint64, qint64)));
	connect(m_reply, SIGNAL(finished()), this, SLOT(httpFeedDownloadFinished()));
}

void FvUpdater::cancelDownloadFeed()
{
	m_httpRequestAborted = true;
	m_reply->abort();
}

void FvUpdater::httpFeedReadyRead()
{
	// this slot gets called every time the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	m_xml.addData(m_reply->readAll());
}

void FvUpdater::httpFeedUpdateDataReadProgress(qint64 bytesRead,
											   qint64 totalBytes)
{
	if (m_httpRequestAborted) {
		return;
	}

	Q_UNUSED(bytesRead);
	Q_UNUSED(totalBytes);
}

void FvUpdater::httpFeedDownloadFinished()
{
	if (m_httpRequestAborted) {
		m_reply->deleteLater();
		return;
	}

	QVariant redirectionTarget = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	if (m_reply->error()) {

		// Error.
		showErrorDialog(tr("Feed download failed: %1.").arg(m_reply->errorString()));

	} else if (! redirectionTarget.isNull()) {
		QUrl newUrl = m_feedURL.resolved(redirectionTarget.toUrl());

		m_feedURL = newUrl;
		m_reply->deleteLater();

		startDownloadFeed(m_feedURL);
		return;

	} else {

		// Done.
		parseFeedXML();

	}

	m_reply->deleteLater();
	m_reply = 0;
}

bool FvUpdater::parseFeedXML()
{
	QString currentTag, currentQualifiedTag;

	QString xmlTitle, xmlLink, xmlReleaseNotesLink, xmlPubDate, xmlEnclosureUrl,
			xmlEnclosureVersion, xmlEnclosurePlatform, xmlEnclosureType;
	unsigned long xmlEnclosureLength;

	// Parse
	while (! m_xml.atEnd()) {

		m_xml.readNext();

		if (m_xml.isStartElement()) {

			currentTag = m_xml.name().toString();
			currentQualifiedTag = m_xml.qualifiedName().toString();

			if (m_xml.name() == "item") {

				xmlTitle.clear();
				xmlLink.clear();
				xmlReleaseNotesLink.clear();
				xmlPubDate.clear();
				xmlEnclosureUrl.clear();
				xmlEnclosureVersion.clear();
				xmlEnclosurePlatform.clear();
				xmlEnclosureLength = 0;
				xmlEnclosureType.clear();

			} else if (m_xml.name() == "enclosure") {

				QXmlStreamAttributes attribs = m_xml.attributes();

				if (attribs.hasAttribute("fervor:platform")) {
					xmlEnclosurePlatform = attribs.value("fervor:platform").toString();

					if (FvPlatform::CurrentlyRunningOnPlatform(xmlEnclosurePlatform)) {

						if (attribs.hasAttribute("url")) {
							xmlEnclosureUrl = attribs.value("url").toString();
						} else {
							xmlEnclosureUrl = "";
						}
						if (attribs.hasAttribute("fervor:version")) {
							xmlEnclosureVersion = attribs.value("fervor:version").toString();
						} else {
							xmlEnclosureVersion = "";
						}
						if (attribs.hasAttribute("sparkle:version")) {
							xmlEnclosureVersion = attribs.value("sparkle:version").toString();
						} else {
							xmlEnclosureVersion = "";
						}
						if (attribs.hasAttribute("length")) {
							xmlEnclosureLength = attribs.value("length").toString().toLong();
						} else {
							xmlEnclosureLength = 0;
						}
						if (attribs.hasAttribute("type")) {
							xmlEnclosureType = attribs.value("type").toString();
						} else {
							xmlEnclosureType = "";
						}

					}

				}

			}

		} else if (m_xml.isEndElement()) {

			if (m_xml.name() == "item") {

				// That's it - we have analyzed a single <item> and we'll stop
				// here (because the topmost is the most recent one, and thus
				// the newest version.


				return searchDownloadedFeedForUpdates(xmlTitle,
													  xmlLink,
													  xmlReleaseNotesLink,
													  xmlPubDate,
													  xmlEnclosureUrl,
													  xmlEnclosureVersion,
													  xmlEnclosurePlatform,
													  xmlEnclosureLength,
													  xmlEnclosureType);

			}

		} else if (m_xml.isCharacters() && ! m_xml.isWhitespace()) {

			if (currentTag == "title") {
				xmlTitle += m_xml.text().toString();

			} else if (currentTag == "link") {
				xmlLink += m_xml.text().toString();

			} else if (currentQualifiedTag == "sparkle:releaseNotesLink") {
				xmlReleaseNotesLink += m_xml.text().toString();

			} else if (currentTag == "pubDate") {
				xmlPubDate += m_xml.text().toString();

			}

		}

		if (m_xml.error() && m_xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {

			showErrorDialog(tr("Feed parsing failed: %1 %2.").arg(QString::number(m_xml.lineNumber()), m_xml.errorString()));
			return false;

		}
	}

	return false;
}


bool FvUpdater::searchDownloadedFeedForUpdates(QString xmlTitle,
											   QString xmlLink,
											   QString xmlReleaseNotesLink,
											   QString xmlPubDate,
											   QString xmlEnclosureUrl,
											   QString xmlEnclosureVersion,
											   QString xmlEnclosurePlatform,
											   unsigned long xmlEnclosureLength,
											   QString xmlEnclosureType)
{
	// Validate
	if (xmlReleaseNotesLink.isEmpty()) {
		if (xmlLink.isEmpty()) {
			showErrorDialog("Feed error: \"release notes\" link is empty");
			return false;
		} else {
			xmlReleaseNotesLink = xmlLink;
		}
	} else {
		xmlLink = xmlReleaseNotesLink;
	}
	if (! (xmlLink.startsWith("http://") || xmlLink.startsWith("https://"))) {
		showErrorDialog("Feed error: invalid \"release notes\" link");
		return false;
	}
	if (xmlEnclosureUrl.isEmpty() || xmlEnclosureVersion.isEmpty() || xmlEnclosurePlatform.isEmpty()) {
		showErrorDialog("Feed error: invalid \"enclosure\" with the download link");
		return false;
	}

	// Relevant version?
	if (FVIgnoredVersions::VersionIsIgnored(xmlEnclosureVersion)) {
		qDebug() << "Version '" << xmlEnclosureVersion << "' is ignored, too old or something like that.";

		if (m_showDialogEvenIfNoUpdatesWereFound) {
			QMessageBox msgBox;
			msgBox.setText(tr("No updates were found."));
			msgBox.exec();
		}

		return true;	// Things have succeeded when you think of it.
	}

	// Success!

	// Destroy window if already exists
	destroyUpdaterWindow();

	m_updaterWindow = new FvUpdateWindow();
	m_updaterWindow->SetSuggestedApplicationVersion(xmlEnclosureVersion);
	m_updaterWindow->SetReleaseNotesURL(xmlLink);
	m_updaterWindow->show();

	/*
	showErrorDialog(QString("Done!\n\n"
							"xmlTitle = %1\n"
							"xmlLink = %2\n"
							"xmlReleaseNotesLink = %3\n"
							"xmlPubDate = %4\n"
							"xmlEnclosureUrl = %5\n"
							"xmlEnclosureVersion = %6\n"
							"xmlEnclosurePlatform = %7\n"
							"xmlEnclosureLength = %8\n"
							"xmlEnclosureType = %9")
					.arg(xmlTitle,
						 xmlLink,
						 xmlReleaseNotesLink,
						 xmlPubDate,
						 xmlEnclosureUrl,
						 xmlEnclosureVersion,
						 xmlEnclosurePlatform,
						 QString::number(xmlEnclosureLength),
						 xmlEnclosureType));
	*/

	return true;
}


void FvUpdater::showErrorDialog(QString message)
{
	QMessageBox dlFailedMsgBox;
	dlFailedMsgBox.setIcon(QMessageBox::Critical);
	dlFailedMsgBox.setText(tr("Error"));
	dlFailedMsgBox.setInformativeText(message);
	dlFailedMsgBox.exec();
}
