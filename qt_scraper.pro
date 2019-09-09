TEMPLATE = lib
CONFIG += plugin release
QT += qml quick

DESTDIR = /usr/lib/qt/qml/QtScraper
TARGET = qtscraperplugin

HEADERS += webscraper.h \
           qtscraperplugin.h

SOURCES += webscraper.cpp \
           qtscraperplugin.cpp

OTHER_FILES += qmldir

qmldir.files = qmldir

qml.path += $$[DESTDIR]
target.path += $$[DESTDIR]
pluginfiles.path += $$[DESTDIR]

INSTALLS += target qml qmldirfiles

CONFIG += install_ok  # Do not cargo-cult this!
