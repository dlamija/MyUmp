#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QObject>

class UserProfile : public QObject
{
    Q_OBJECT
public:
    explicit UserProfile(QObject *parent = nullptr);
    QString userName;
    QString userPass;

    bool isInUMP = false;
    bool isCheckedIn = false;
    bool isCheckedOut = false;
    bool SettingSaved = false;
    bool autoCheckIn = false;
    bool disableCheckOut = false;
    bool disableOutside = true;
signals:

};

#endif // USERPROFILE_H
