#include "webscraper.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextCodec>

#include "tidy.h"

WebScraper::WebScraper(QObject *parent) : QObject(parent)
{

}

QString WebScraper::url() const
{
    return m_url;
}

void WebScraper::setUrl(const QString &url)
{
    m_url = url;
}

QString WebScraper::httpMethod() const
{
    return m_httpMethod;
}

void  WebScraper::setHttpMethod(const QString &httpMethod)
{
    m_httpMethod = httpMethod;
}

void WebScraper::doRequest()
{
    this->manager = new QNetworkAccessManager(this);

    connect(this->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    if (m_httpMethod == "get")
        manager->get(QNetworkRequest(QUrl("http://testing-ground.scraping.pro/table")));
}

void WebScraper::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        qDebug() << fromByteArrayToString(reply->readAll());
    }

    reply->deleteLater();
}

QString WebScraper::fromByteArrayToString(QByteArray html)
{
   return QTextCodec::codecForName("iso-8859-1")->toUnicode(html);
}
