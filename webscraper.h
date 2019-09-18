#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class WebScraper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl)
    Q_PROPERTY(QString httpMethod READ httpMethod WRITE setHttpMethod)
public:
    explicit WebScraper(QObject *parent = nullptr);
    QString url() const;
    void setUrl(const QString &url);
    QString httpMethod() const;
    void setHttpMethod(const QString &url);
    Q_INVOKABLE void doRequest();
public slots:
    void replyFinished (QNetworkReply *reply);
private:
    QString fromByteArrayToString(QByteArray html);
    QString m_url;
    QString m_httpMethod;
    QNetworkAccessManager *manager;
};

#endif // WEBSCRAPER_H
