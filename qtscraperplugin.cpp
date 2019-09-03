#include "qtscraperplugin.h"
#include "webscraper.h"
#include <qqml.h>

void QtScraperPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<WebScraper>(uri, 1, 0, "WebScraper");
}
