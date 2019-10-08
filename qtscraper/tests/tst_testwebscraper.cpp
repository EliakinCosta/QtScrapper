#include <QtTest>

// add necessary includes here

class TestWebScraper : public QObject
{
    Q_OBJECT

public:
    TestWebScraper();
    ~TestWebScraper();

private slots:
    void test_case1();

};

TestWebScraper::TestWebScraper()
{

}

TestWebScraper::~TestWebScraper()
{

}

void TestWebScraper::test_case1()
{

}

QTEST_APPLESS_MAIN(TestWebScraper)

#include "tst_testwebscraper.moc"
