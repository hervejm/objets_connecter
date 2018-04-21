#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:04:56
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client-mqtt
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    qmqtt_client_p.cpp \
    qmqtt_client.cpp \
    qmqtt_frame.cpp \
    qmqtt_message.cpp \
    qmqtt_network.cpp \
    qmqtt_will.cpp

HEADERS  += widget.h \
    qmqtt_client_p.h \
    qmqtt_client.h \
    qmqtt_frame.h \
    qmqtt_global.h \
    qmqtt_message.h \
    qmqtt_network.h \
    qmqtt_will.h \
    qmqtt.h

FORMS    += widget.ui

#   QWT library
#INCLUDEPATH += /usr/local/qwt-6.1.2/include
#LIBS += -L/usr/local/qwt-6.1.2/lib  -lqwt

RESOURCES += \
    img_for_app/img_thermo.qrc \
    img_for_app.qrc

OTHER_FILES +=

