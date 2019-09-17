#include "webscraper.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>

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

void WebScraper::doRequest(const QString &httpMethod)
{
    this->manager = new QNetworkAccessManager(this);

    connect(this->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    if (httpMethod == "get")
        manager->get(QNetworkRequest(QUrl("http://testing-ground.scraping.pro/table")));
}

// -------------Slots --------------------

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

        QFile *file = new QFile("C:/Qt/Dummy/downloaded.txt");
        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }

    reply->deleteLater();
}
