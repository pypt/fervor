#ifndef FVUPDATER_H
#define FVUPDATER_H

#include <QObject>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QXmlStreamReader>
class FvUpdateWindow;


class FvUpdater : public QObject
{
	Q_OBJECT

public:

	// Singleton
	static FvUpdater* sharedUpdater();
	static void drop();
	
public slots:

	// Set feed URL
	void SetFeedURL(QString feedURL);
	QString GetFeedURL();

	// Check for updates
	bool CheckForUpdates(bool notifyAboutUpToDateApplication = false);

private:

	// Hide main constructor
	FvUpdater();
	~FvUpdater();

	// Hide copy constructor
	FvUpdater(const FvUpdater&);

	// Hide assign op
	// we leave just the declarations, so the compiler will warn us
	// if we try to use those two functions by accident
	FvUpdater& operator=(const FvUpdater&);

	// Singleton instance
	static FvUpdater* m_Instance;

	// Updater window
	FvUpdateWindow* m_updaterWindow;

	// HTTP fetcher
	QUrl m_feedURL;
	QNetworkAccessManager m_qnam;
	QNetworkReply* m_reply;
	int m_httpGetId;
	bool m_httpRequestAborted;

	void startDownloadFeed(QUrl url);
	void cancelDownloadFeed();

	// XML parser
	QXmlStreamReader m_xml;
	bool parseFeedXML();
	bool searchDownloadedFeedForUpdates(QString xmlTitle,
										QString xmlLink,
										QString xmlReleaseNotesLink,
										QString xmlPubDate,
										QString xmlEnclosureUrl,
										QString xmlEnclosureVersion,
										QString xmlEnclosurePlatform,
										unsigned long xmlEnclosureLength,
										QString xmlEnclosureType);

	// "No updates" dialog was requested
	bool m_showDialogEvenIfNoUpdatesWereFound;

	void destroyUpdaterWindow();

	// Show an error message
	void showErrorDialog(QString message);


private slots:

	void httpFeedReadyRead();
	void httpFeedUpdateDataReadProgress(qint64 bytesRead,
										qint64 totalBytes);
	void httpFeedDownloadFinished();

};

#endif // FVUPDATER_H
