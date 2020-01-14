#include "myump.h"
#include <QSettings>
#include <QDebug>

MyUmp::MyUmp(QWidget *parent) : QWidget(parent)
{
    user = new UserProfile();
    this->readSettings();
    umpsetting = new UMPSetting(user, this);

    //create systray item
    createActions();
    createTrayIcon();
    setIcon();



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

}

void MyUmp::createTrayIcon()
{

}

void MyUmp::setIcon()
{

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
