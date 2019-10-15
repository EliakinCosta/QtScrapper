#ifndef SCRAPERNETWORKCLIENT_H
#define SCRAPERNETWORKCLIENT_H

#include "inetworkclient.h"

class QNetworkAccessManager;
class QNetworkReply;

class ScraperNetworkClient : public INetworkClient
{
public:
    ScraperNetworkClient(QObject *parent = nullptr);
    virtual void get(QString url);
    virtual QString document() const;
public slots:
    void replyFinished (QNetworkReply *reply);
private:
    QString fromByteArrayToString(QByteArray html);
private:
    QNetworkAccessManager *m_manager;
    QString m_document;
};

#endif // SCRAPERNETWORKCLIENT_H
