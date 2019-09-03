#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <QObject>

class WebScraper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl)
public:
    explicit WebScraper(QObject *parent = nullptr);
    QString url() const;
    void setUrl(const QString &url);
private:
    QString m_url;
};

#endif // WEBSCRAPER_H
