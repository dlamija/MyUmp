#ifndef MYUMP_H
#define MYUMP_H

#include <QWidget>
#include "userprofile.h"
#include "umpsetting.h"


class MyUmp : public QWidget
{
    Q_OBJECT
public:
    explicit MyUmp(QWidget *parent = nullptr);
    void writeSettings();

private:
    UserProfile *user;
    UMPSetting *umpsetting;

    void readSettings();
    void createActions();
    void createTrayIcon();
    void setIcon();

public slots:


signals:

};

#endif // MYUMP_H
