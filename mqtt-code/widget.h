#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <iostream>
using namespace std;
#include <QTimer>

#include <inttypes.h>
#include "qmqtt.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void messageReceived(const QMQTT::Message &message);
    void connackedReceived(quint8);
    void pubackedReceived(QMQTT::Message &message);
    void on_toolButtonConnect_clicked();

private:
    Ui::Widget *ui;
    // MQTT protocole
    QMQTT::Client *client;      // le client MQTT
    QString brokerHost;         // adresse IP ou non du broker
    uint16_t msgId;             // nomero du message
    uint8_t qos;                // qualité de service
    bool retain;                // reste sur le serveur

    QStringList topicsSubscribed;       // la liste des topics souscrits

 };

#endif // WIDGET_H
