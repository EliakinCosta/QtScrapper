#ifndef INETWORKCLIENT_H
#define INETWORKCLIENT_H

#include <QObject>

class INetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit INetworkClient(QObject *parent = nullptr);
    virtual void get(QString url) = 0;
    virtual QString document() const = 0;

signals:
    void statusChanged(QString status);
public slots:
};

#endif // INETWORKCLIENT_H
