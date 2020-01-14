#include "myump.h"
#include <QSettings>
#include <QDebug>

MyUmp::MyUmp(QWidget *parent) : QWidget(parent)
{
    user = new UserProfile();
    umpsetting = new UMPSetting(user, this);
    this->readSettings();

    qDebug() << user->userName << user->isCheckedIn << endl;
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
