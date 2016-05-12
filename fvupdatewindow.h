#ifndef FVUPDATEWINDOW_H
#define FVUPDATEWINDOW_H

#include <QWidget>
#include <QTextBrowser>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
class QGraphicsScene;

namespace Ui {
class FvUpdateWindow;
}

class FvUpdateWindow : public QWidget
{
	Q_OBJECT

public:
	explicit FvUpdateWindow(QWidget *parent = 0);
	~FvUpdateWindow();

	// Update the current update proposal from FvUpdater
	bool UpdateWindowWithCurrentProposedUpdate();

	void closeEvent(QCloseEvent* event);

public slots:

    void writeChangelog(QNetworkReply* reply);

private:
	Ui::FvUpdateWindow*	m_ui;
	QGraphicsScene* m_appIconScene;
    QTextBrowser* relNotes;
    QNetworkAccessManager* net;
};

#endif // FVUPDATEWINDOW_H
