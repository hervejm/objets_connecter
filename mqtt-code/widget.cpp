#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <string.h>
#include <QThread>
#include <iostream>
using namespace  std;

#include "qmqtt.h"

#define TITLE "client MQTT - 1.00\t\t"

// __________________________ constructeur
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    // default values
    brokerHost = "192.168.0.35"; //Default PC for E206....

    // topics to subscribe
    topicsSubscribed<<"sensors/tbrd/01";
    topicsSubscribed<<"sensors/hygs/01";


    // MQTT cleint
    client = new QMQTT::Client(brokerHost);
    connect(client, SIGNAL(received(const QMQTT::Message&)), this, SLOT(messageReceived(const QMQTT::Message&)));
    connect(client, SIGNAL(connacked(quint8)), this, SLOT(connackedReceived(quint8)));
    connect(client, SIGNAL(published(QMQTT::Message&)), this, SLOT(pubackedReceived(QMQTT::Message&)));
    msgId = 1;          // message number
    qos = 0;            // quality of service
    retain = false;     // no retain on broker

    // le titre de la fenetre
    this->setWindowTitle(TITLE);
}

//_____________________________________________Destructeur
Widget::~Widget()
{
    delete ui;
    if (client) delete client;
}

//      slot : MQTT message Received
void Widget::messageReceived(const QMQTT::Message &message){
    // écriture sur l'interface tout simplement
    if(message.topic()=="sensors/tbrd/01"){
        ui->textEditMessage->append("Core temps is received");
        ui->coreTempNumber->setMode(QLCDNumber::Dec);
        ui->coreTempNumber->display((QString)message.payload());
    }
    else{
        ui->textEditMessage->append("Humidity is received");
    }
    ui->textEditMessage->append(message.topic()+"="+message.payload());

}

//      slot : Connect acknoledge Received
void Widget::connackedReceived(quint8 code){
    // modifie le titre de la fenêtre
    this->setWindowTitle(TITLE+brokerHost);
    // affiche les topics souscrits
    for (int i=0 ; i<topicsSubscribed.size() ; i++){
            client->subscribe(topicsSubscribed[i], qos);                // souscription
        }
}

//      slot :  publish Acknoledge
void Widget::pubackedReceived(QMQTT::Message& message){
}

//      bouton connecter/déconnecter
void Widget::on_toolButtonConnect_clicked()
{
    if (client->isConnected()){
                                client->disconnect();
                                this->setWindowTitle(TITLE);
                                ui->toolButtonConnect->setText("connect");
                                }
                        else     {
                                client->setHost(brokerHost);
                                client->connect();
                                ui->toolButtonConnect->setText("disconnect");
                                ui->textEditMessage->clear();       // effacement de la fenetre des messages
                                }
}


