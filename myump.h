#ifndef MYUMP_H
#define MYUMP_H

#include <QWidget>
#include "user.h"
#include "umpsetting.h"

class QSystemTrayIcon;
class QMenu;

class MyUmp : public QWidget
{
    Q_OBJECT
public:
    explicit MyUmp(QWidget *parent = nullptr);


private:
    User *user;
    UMPSetting *umpsetting;

    QAction *loginEcommAction;
    QAction *loginKalamAction;
    QAction *checkInAction;
    QAction *checkOutAction;
    QAction *checkMemoAction;
    QAction *configureAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    bool isCheckedIn;

    void readSettings();
    void createActions();
    void createTrayIcon();
    void setIcon();

public slots:
    void writeSettings();
    void checkInFinished(QNetworkReply *reply);
    void checkOutFinished(QNetworkReply *reply);


private slots:
    void configureSetting();
signals:

};

#endif // MYUMP_H
