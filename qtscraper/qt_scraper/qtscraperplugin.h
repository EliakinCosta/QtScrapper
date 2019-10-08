#ifndef QTSCRAPERPLUGIN_H
#define QTSCRAPERPLUGIN_H

#include <QQmlExtensionPlugin>

class QtScraperPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};

#endif // QTSCRAPERPLUGIN_H
