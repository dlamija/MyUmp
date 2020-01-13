#ifndef MYUMP_H
#define MYUMP_H

#include <QObject>

class MyUmp : public QObject
{
    Q_OBJECT
public:
    explicit MyUmp(QObject *parent = nullptr);

signals:

};

#endif // MYUMP_H
