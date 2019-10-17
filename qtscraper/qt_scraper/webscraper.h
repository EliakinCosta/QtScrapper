#ifndef WEBSCRAPER_H
#define WEBSCRAPER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;
class INetworkClient;

class WebScraper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString url READ url WRITE setUrl)
    Q_PROPERTY(QString httpMethod READ httpMethod WRITE setHttpMethod)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
public:
    explicit WebScraper(QObject *parent = nullptr);
    virtual ~WebScraper();
    QString url() const;
    void setUrl(const QString &url);
    QString httpMethod() const;
    void setHttpMethod(const QString &url);
    QString status() const;
    QString html() const;
    Q_INVOKABLE void doRequest();
public slots:
    void setStatus(QString status);
Q_SIGNALS:
    void statusChanged(QString status);
private:      
    QString fromHtmlToXml(QString html);
private:    
    QString m_status;
    QString m_url;
    QString m_httpMethod;
    QString m_html;
    INetworkClient *m_networkClient;
};

#endif // WEBSCRAPER_H
