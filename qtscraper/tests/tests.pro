QT += testlib network qml quick
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testwebscraper.cpp

INCLUDEPATH += ../qt_scraper
LIBS += -L../qt_scraper -lqtwebscraper-plugin

DISTFILES += \
    html
