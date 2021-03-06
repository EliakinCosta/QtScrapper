#include "webscraper.h"

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QString>
#include <QObject>
#include <inetworkclient.h>

#include "tidy.h"
#include "tidybuffio.h"

WebScraper::WebScraper(QObject *parent) : QObject(parent)
{
    QObject::connect(
        m_networkClient, SIGNAL(statusChanged(QString)),
        this,  SLOT(setStatus(QString))
    );
}

WebScraper::~WebScraper()
{
    delete &m_networkClient;
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
    if (m_httpMethod == "get")
        m_networkClient->get(m_url);
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
