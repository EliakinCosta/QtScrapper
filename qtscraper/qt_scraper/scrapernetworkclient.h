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
    void setStatus(QString status);
    QString fromByteArrayToString(QByteArray html);
private:
    QNetworkAccessManager *m_manager;
    QString m_document;
    QString m_status;
};

#endif // SCRAPERNETWORKCLIENT_H
