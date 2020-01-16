#ifndef MYUMP_H
#define MYUMP_H

#include <QWidget>
#include "user.h"
#include "umpsetting.h"

class QSystemTrayIcon;
class QMenu;
class QSslError;
class QTimer;

class MyUmp : public QWidget
{
    Q_OBJECT
public:
    explicit MyUmp(QWidget *parent = nullptr);
    QTimer *timer;

private:
    User *user;
    UMPSetting *umpsetting;

    QAction *login_action;
    QAction *loginkalam_action;
    QAction *checkin_action;
    QAction *checkout_action;
    QAction *checkmemo_action;
    QAction *configureAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    static const QString logUMPNETUrl;
    static const QString umpHostUrl;
    static const QString umpHostIpAddress;

    bool isCheckedIn;
    bool isInUMP;

    void readSettings();
    void createActions();
    void createTrayIcon();
    void setIcon();
    bool lookupUMPDNS();

public slots:
    void writeSettings();
    void onSslError(QNetworkReply *r, QList<QSslError> l);
    void checkInFinished(QNetworkReply *reply);
    void checkOutFinished(QNetworkReply *reply);


private slots:
    void configureSetting();
    void checkIPChanged();

signals:

};

#endif // MYUMP_H
