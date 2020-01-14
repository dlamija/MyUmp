#include "user.h"
#include <QTemporaryDir>
#include <QTextStream>
#include <QDesktopServices>
#include <QThread>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>


User::User(QObject *parent) : QObject(parent)
{

}

//void User::onSslError(QNetworkReply *r, QList<QSslError> l)
//{
//    l.size();
//    r->ignoreSslErrors();
//}

void User::checkInFinished(QNetworkReply *reply)
{
    this->checkin(reply);
}

void User::checkOutFinished(QNetworkReply *reply)
{
    this->checkout(reply);
}

void User::loginEcomm()
{
    QTemporaryDir dir;
    QString path = dir.path() +"/";
    QFile file("out.html");
    if (dir.isValid()) {
        if(QDir::setCurrent(dir.path())){
            file.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream out(&file);
                out << "<html>" << endl;
                out << "<body >" << endl;
                out << "    <form id=\"auto\" method=\"post\" ";
                out << "        action=\"https://community.ump.edu.my/ecommstaff/Login\">" << endl;
                out << "        <input name=\"userName\" type=\"hidden\" value=\"" << this->userName <<"\"/>" << endl;
                out << "        <input name=\"password\" type=\"hidden\" value=\"" << this->userPass <<"\"/>" << endl;
                out << "        <input name=\"level\" type=\"hidden\" value=\"Staff\"/>" << endl;
                out << "    </form>" << endl;
                out << "    <script type=\"text/javascript\">" << endl;
                out << "        function myfunc(){" << endl;
                out << "            var frm=document.getElementById(\"auto\");" << endl;
                out << "            frm.submit();" << endl;
                out << "        }" << endl;
                out << "        window.onload=myfunc;" << endl;
                out << "    </script>" << endl;
                out << "</body>" << endl;
                out << "</html>" << endl;

                file.close();
                QString link = "file://" + path + "out.html";
                QDesktopServices::openUrl(link);
                QThread::sleep(1);
        }
    }
}

void User::loginKalam()
{

}

void User::checkInUMP()
{
    QString link = "https://community.ump.edu.my/ecommstaff/cms/StaffAttendance/checkatt2.jsp";
    QUrlQuery urlQuery;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    urlQuery.addQueryItem("action", "checkin");
    urlQuery.addQueryItem("username", userName);
    urlQuery.addQueryItem("password", userPass.toLatin1().toPercentEncoding());
    //qDebug() << userName << userPass.toLatin1().toPercentEncoding() << endl;
    QUrl url = QUrl(link);
    QNetworkRequest networkRequest(url);

    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));

    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(checkInFinished(QNetworkReply*)));

    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(networkRequest, urlQuery.toString(QUrl::FullyEncoded).toUtf8());

}

void User::checkOutUMP()
{
    QString link = "https://community.ump.edu.my/ecommstaff/cms/StaffAttendance/checkatt2.jsp";

    QUrlQuery urlQuery;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    urlQuery.addQueryItem("action", "checkout");
    urlQuery.addQueryItem("username", userName);
    //QUrl::toPercentEncoding(userPass));
    urlQuery.addQueryItem("password", userPass.toLatin1().toPercentEncoding());
    QUrl url = QUrl(link);
    QNetworkRequest networkRequest(url);

    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));
    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(checkOutFinished(QNetworkReply*)));

    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(networkRequest, urlQuery.toString(QUrl::FullyEncoded).toUtf8());

}

void User::checkMemo()
{     QString linkMemo = "https://community.ump.edu.my/ecommstaff/memo.jsp?action=folders&type=Y&folderID=1";
      QDesktopServices::openUrl(QUrl(linkMemo));

}
