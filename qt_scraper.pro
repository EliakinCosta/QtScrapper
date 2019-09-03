TEMPLATE = lib
CONFIG += plugin
QT += qml quick

DESTDIR = ../QtScraper
TARGET = $$qtLibraryTarget(qtscraperplugin)

HEADERS += webscraper.h \
          qtscraperplugin.h

SOURCES += webscraper.cpp \
          qtscraperplugin.cpp

DESTPATH= ../QtScraper

target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

CONFIG += install_ok  # Do not cargo-cult this!

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$DESTDIR
COPIES += cpqmldir
