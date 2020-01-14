#include "myump.h"
#include <QSettings>
#include <QDebug>
#include <QAction>
#include <QCoreApplication>
#include <QMenu>
#include <QSystemTrayIcon>


MyUmp::MyUmp(QWidget *parent) : QWidget(parent)
{
    user = new User();
    this->readSettings();
    umpsetting = new UMPSetting(user, this);

    //create systray item
    this->createActions();
    this->createTrayIcon();




    if (user->SettingSaved){
        umpsetting->show();
    } else {
        umpsetting->show();
    }

}

void MyUmp::readSettings()
{
    QSettings settings;
    user->SettingSaved = settings.contains("Login/username");
    if (user->SettingSaved){
        settings.beginGroup("Login");
            user->userName = QByteArray::fromBase64(settings.value("username").toString().toUtf8());
            user->userPass = QByteArray::fromBase64(settings.value("password").toString().toUtf8());
        settings.endGroup();

        settings.beginGroup("Date");
            user->autoCheckIn = settings.value("day").toBool();
            user->disableCheckOut = settings.value("month").toBool();
            user->disableOutside = settings.value("week").toBool();
        settings.endGroup();
    }
}

void MyUmp::createActions()
{
    loginEcommAction = new QAction(tr("&Log In E-Comm"), this);
    connect(loginEcommAction, &QAction::triggered, this, &MyUmp::loginEcomm);

    loginKalamAction = new QAction(tr("Login &Kalam"),this);
    connect(loginKalamAction, &QAction::triggered, this, &MyUmp::loginKalam);

    checkInAction = new QAction(tr("Check &In"), this);
    connect(checkInAction, &QAction::triggered, this, &MyUmp::checkInUMP);
    checkOutAction = new QAction(tr("Check &Out"), this);
    connect(checkOutAction, &QAction::triggered, this, &MyUmp::checkOutUMP);
    checkMemoAction = new QAction(tr("Check &Memo"), this);
    connect(checkMemoAction, &QAction::triggered, this, &MyUmp::checkMemo);

    configureAction = new QAction(tr("&Configure"),this);
    connect(configureAction, &QAction::triggered, this, &MyUmp::configureSetting);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

}

void MyUmp::createTrayIcon()
{
    trayIconMenu = new QMenu(umpsetting);
    //trayIconMenu->addSeparator();
    trayIconMenu->addAction(loginEcommAction);
    trayIconMenu->addAction(checkMemoAction);
    //trayIconMenu->addAction(loginKalamAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(checkInAction);
    trayIconMenu->addAction(checkOutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(configureAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    this->setIcon();
    trayIcon = new QSystemTrayIcon(umpsetting);
    trayIcon->setContextMenu(trayIconMenu);
}

void MyUmp::setIcon()
{
    QIcon icon = QIcon(":/Resources/logoUMP.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip(tr("UMP"));
}


void MyUmp::configureSetting()
{
    umpsetting->show();
}

void MyUmp::writeSettings()
{
    QSettings settings;

    settings.beginGroup("Login");
        settings.setValue("username",user->userName.toUtf8().toBase64() );
        settings.setValue("password", user->userPass.toUtf8().toBase64());
    settings.endGroup();
    settings.beginGroup("Date");
        settings.setValue("day",user->autoCheckIn );
        settings.setValue("month",user->disableCheckOut );
        settings.setValue("week",user->disableOutside);
     settings.endGroup();
    settings.sync();

}
