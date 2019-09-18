#include "webscraper.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QString>

#include "tidy.h"
#include "tidybuffio.h"

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

        qDebug() << fromHtmlToXml(fromByteArrayToString(reply->readAll()));
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

    return QString::fromUtf8(reinterpret_cast<const char*>(output.bp));
}
