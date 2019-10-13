#include <QtTest>
#include <QDebug>

// add necessary includes here
#include "webscraper.h"

class TestWebScraper : public QObject
{
    Q_OBJECT

public:
    TestWebScraper();
    virtual ~TestWebScraper();

private slots:
    void test_simple_scraping();

};

TestWebScraper::TestWebScraper()
{

}

TestWebScraper::~TestWebScraper()
{

}

void TestWebScraper::test_simple_scraping()
{
    WebScraper scraper;
    scraper.setUrl("http://testing-ground.scraping.pro/table");
    scraper.setHttpMethod("get");
    scraper.doRequest();

    while (scraper.status() != "READY") {
        qDebug() << scraper.status();
        QTest::qSleep(2);
    }
     QString regex = "<.*?id=\"pStyle\".*?>(.*?)</.*?>";
     QRegExp re(regex);
     re.indexIn(scraper.html(), 0);
     qDebug() << re.cap(1);
}

QTEST_MAIN(TestWebScraper)

#include "tst_testwebscraper.moc"
