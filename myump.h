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
    void writeSettings();

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

    void readSettings();
    void createActions();
    void createTrayIcon();
    void setIcon();

public slots:

private slots:
    void loginEcomm();
    void loginKalam();
    void checkInUMP();
    void checkOutUMP();
    void checkMemo();
    void configureSetting();
signals:

};

#endif // MYUMP_H
