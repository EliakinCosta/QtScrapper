#include "webscraper.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QString>

#include "tidy.h"
#include "tidybuffio.h"

WebScraper::WebScraper(QObject *parent) : QObject(parent)
{
    m_status = "WAITING";
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

QString WebScraper::html() const
{
    return m_html;
}

void  WebScraper::setHttpMethod(const QString &httpMethod)
{
    m_httpMethod = httpMethod;
}

QString WebScraper::status() const
{
    return m_status;
}

void WebScraper::setStatus(QString status)
{
    if (m_status != status) {
        m_status = status;
        emit statusChanged(m_status);
    }
}

void WebScraper::doRequest()
{
    setStatus("RUNNING");
    this->manager = new QNetworkAccessManager(this);

    connect(this->manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    if (m_httpMethod == "get")
        manager->get(QNetworkRequest(QUrl(m_url)));
}

void WebScraper::replyFinished (QNetworkReply *reply)
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

        qDebug() << fromByteArrayToString(reply->readAll());
        m_html = fromByteArrayToString(reply->readAll());        
        setStatus("READY");
        qDebug() << this->status();
    }

    reply->deleteLater();
}

QString WebScraper::fromByteArrayToString(QByteArray html)
{
   return QTextCodec::codecForName("iso-8859-1")->toUnicode(html);
}

QString WebScraper::fromHtmlToXml(QString html)
{
    TidyDoc tdoc = tidyCreate();
    tidyOptSetBool(tdoc, TidyXmlOut, yes);
    tidyOptSetBool(tdoc, TidyQuiet, yes);
    tidyOptSetBool(tdoc, TidyNumEntities, yes);
    tidyOptSetBool(tdoc, TidyShowWarnings, no);

    tidyParseString(tdoc, html.toUtf8());
    tidyCleanAndRepair(tdoc);
    TidyBuffer output = {nullptr, nullptr, 0, 0, 0};
    tidySaveBuffer(tdoc, &output);

    return reinterpret_cast<const char*>(output.bp);
}
