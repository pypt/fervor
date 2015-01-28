#ifndef FV_DOWNLOAD_DIALOG_H
#define FV_DOWNLOAD_DIALOG_H

#include <QDir>
#include <QIcon>
#include <QDateTime>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QNetworkAccessManager>

#include <math.h>

namespace Ui
{
class FvDownloadDialog;
}

class FvDownloadDialog : public QWidget
{
        Q_OBJECT

    public:
        explicit FvDownloadDialog (QWidget *parent = 0);
        ~FvDownloadDialog (void);

        void beginDownload ();

    private slots:
        void openDownload (void);
        void installUpdate (void);
        void cancelDownload (void);
        void downloadFinished (void);
        void updateProgress (qint64 received, qint64 total);
        void ignoreSslErrors (QNetworkReply *reply, const QList<QSslError>& error);

    private:
        Ui::FvDownloadDialog *ui;

        QString m_path;
        bool m_download_paused;

        QNetworkReply *m_reply;
        QNetworkAccessManager *m_manager;

        uint m_start_time;

        float roundNumber (const float& input);
};

#endif
