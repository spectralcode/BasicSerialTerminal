QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/comportselectwidget.cpp \
    src/main.cpp \
    src/basicserialterminal.cpp \
    src/serialcom.cpp

HEADERS += \
    src/basicserialterminal.h \
    src/comportselectwidget.h \
    src/serialcom.h

FORMS += \
    src/comportselectwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#set application icon
RC_ICONS = images/icon.ico
