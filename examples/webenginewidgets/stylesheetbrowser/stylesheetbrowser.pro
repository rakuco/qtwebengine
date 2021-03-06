TEMPLATE = app
TARGET = stylesheetbrowser
QT += webenginewidgets
CONFIG += c++11

HEADERS += \
    mainwindow.h \
    stylesheetdialog.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    stylesheetdialog.cpp

FORMS += \
    mainwindow.ui \
    stylesheetdialog.ui

RESOURCES += stylesheetbrowser.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webenginewidgets/stylesheetbrowser
INSTALLS += target
