#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class WebScraper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl)
public:
    explicit WebScraper(QObject *parent = nullptr);
    QString url() const;
    void setUrl(const QString &url);
    Q_INVOKABLE void doRequest(const QString &httpMethod);
public slots:
    void replyFinished (QNetworkReply *reply);
private:
    fromByteArrayToXml()
    QString m_url;
    QNetworkAccessManager *manager;
};

#endif // WEBSCRAPER_H
