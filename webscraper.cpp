#include "webscraper.h"

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
