#include "myump.h"
#include <QSettings>
#include <QDebug>
#include <QAction>
#include <QCoreApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QNetworkReply>
#include <QTextDocument>


MyUmp::MyUmp(QWidget *parent) : QWidget(parent)
{
    user = new User();
    this->readSettings();
    umpsetting = new UMPSetting(user, this);

    //create connection
    connect(umpsetting,&UMPSetting::valueChanged,this, &MyUmp::writeSettings);
    connect(user, &User::checkin, this, &MyUmp::checkInFinished);
    connect(user, &User::checkout, this, &MyUmp::checkOutFinished);

    //create systray item
    this->createActions();
    this->createTrayIcon();
    this->setIcon();
    trayIcon->show();


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
    connect(loginEcommAction, &QAction::triggered, user, &User::loginEcomm);

    loginKalamAction = new QAction(tr("Login &Kalam"),this);
    connect(loginKalamAction, &QAction::triggered, user, &User::loginKalam);

    checkInAction = new QAction(tr("Check &In"), this);
    connect(checkInAction, &QAction::triggered, user, &User::checkInUMP);
    checkOutAction = new QAction(tr("Check &Out"), this);
    connect(checkOutAction, &QAction::triggered, user, &User::checkOutUMP);
    checkMemoAction = new QAction(tr("Check &Memo"), this);
    connect(checkMemoAction, &QAction::triggered, user, &User::checkMemo);

    configureAction = new QAction(tr("&Configure"),this);
    connect(configureAction, &QAction::triggered, this, &MyUmp::configureSetting);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

}

void MyUmp::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
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


    trayIcon = new QSystemTrayIcon(this);
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

void MyUmp::checkInFinished(QNetworkReply *reply)
{
    qDebug() << "In finish "<< endl;
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        QString strdata = reply->readAll();
        QTextDocument doc;
        doc.setHtml(strdata);
        strdata = doc.toPlainText().remove(QRegExp("[\n\t\r]")).trimmed();
        if (strdata.mid(1,1) == ' '){
            strdata = strdata.mid(2,strdata.length());
        }

        QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(1);

        if (strdata == "Check in failed!."){
            qDebug() << strdata;
            trayIcon->showMessage(QCoreApplication::applicationName() + ": Check In",
                                  "Dear " +user->userName +", " +strdata,
                                  msgIcon, 5 * 1000);
        } else if (strdata.contains("Check-in failed.")) {
            int indexN = strdata.indexOf("Check-in failed.",0,Qt::CaseSensitive);
            QString name = strdata.mid(1,indexN-1).trimmed();
            strdata = strdata.mid(indexN, strdata.length());
            qDebug() << "Check-in failed. : " +strdata;

            trayIcon->showMessage(name, strdata, msgIcon, 5 * 1000);
            isCheckedIn = true;
            checkInAction->setEnabled(false);
            checkOutAction->setEnabled(true);
        } else {
            int indexN = strdata.indexOf("Check-in successful",0,Qt::CaseSensitive);
            QString name = strdata.mid(1,indexN-1).trimmed();
            strdata = strdata.mid(indexN, strdata.length());
            qDebug() << "Check-in successful : " +strdata;

            trayIcon->showMessage(name, strdata, msgIcon, 5 * 1000);
            isCheckedIn = true;
            checkInAction->setEnabled(false);
            checkOutAction->setEnabled(true);

        }
        reply->deleteLater();
    }
}

void MyUmp::checkOutFinished(QNetworkReply *reply)
{

}
