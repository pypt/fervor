#ifndef FVUPDATEWINDOW_H
#define FVUPDATEWINDOW_H

#include <QWidget>
#include <QUrl>

namespace Ui {
class FvUpdateWindow;
}

class FvUpdateWindow : public QWidget
{
	Q_OBJECT
	
public:
	explicit FvUpdateWindow(QWidget *parent = 0);
	~FvUpdateWindow();

	// Property setters for the dialog
	void SetSuggestedApplicationVersion(QString suggestedApplicationVersion);
	void SetReleaseNotesURL(QString releaseNotesUrl);

private:
	Ui::FvUpdateWindow*	m_ui;

	// Dialog properties
	QString m_suggestedApplicationVersion;
	QUrl m_releaseNotesUrl;

	// Helpers
	void installTranslator();
};

#endif // FVUPDATEWINDOW_H
