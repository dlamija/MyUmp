#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QObject>
#include <QSslError>

class QNetworkReply;


class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString userName;
    QString userPass;

    bool isInUMP = false;
    bool isCheckedIn = false;
    bool isCheckedOut = false;
    bool SettingSaved = false;
    bool autoCheckIn = false;
    bool disableCheckOut = false;
    bool disableOutside = true;

private slots:

    //void kalamLogined(QNetworkReply *reply);
    //void checkIPChanged();

public slots:
    void loginEcomm();
    void studentIMS();
    void loginKalam();
    void checkInUMP();
    void checkOutUMP();
    void checkMemo();

signals:
    void checkin(QNetworkReply *reply);
    void checkout(QNetworkReply *reply);
    void onSslError(QNetworkReply *r, QList<QSslError> l);

};

#endif // USERPROFILE_H
