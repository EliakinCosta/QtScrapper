#include "scrapernetworkclient.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>

ScraperNetworkClient::ScraperNetworkClient(QObject *parent) : INetworkClient(parent)
{

}

void ScraperNetworkClient::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
        setStatus("ERROR");
        return;
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        m_document = fromByteArrayToString(reply->readAll());
        setStatus("READY");
    }

    reply->deleteLater();
}

void ScraperNetworkClient::get(QString url)
{
    m_manager = new QNetworkAccessManager(this);

    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    m_manager->get(QNetworkRequest(QUrl(url)));
    setStatus("RUNNING");
}

QString ScraperNetworkClient::document() const
{
    return m_document;
}

QString ScraperNetworkClient::fromByteArrayToString(QByteArray html)
{
   return QTextCodec::codecForName("iso-8859-1")->toUnicode(html);
}

void ScraperNetworkClient::setStatus(QString status)
{
    if (status != m_status)
    {
        m_status = status;
        emit statusChanged(status);
    }
}
