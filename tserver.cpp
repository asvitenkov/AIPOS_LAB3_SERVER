#include "tserver.h"
#include <QChar>
#include <QTextCodec>

TServer::TServer(QObject *parent) :
    QTcpServer(parent)
{
    qDebug()<<"TServer::TServer";


}


void TServer::initialize(){
    qDebug()<<"TServer::initialize";
    echoMode = false;
}


void TServer::incomingConnection(int handle){
    qDebug()<<"TServer::incomingConnection";
    clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(handle);
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(readClient()));

    QString str;
    str+="^^^^^^^^^^^^^^^##########^^^^^^^^^^^^^^^\r\n";
    str+="^^^^^^^^^^^########^^########^^^^^^^^^^^\r\n";
    str+="^^^^^^^^#####^^^^^^^^^^^^^^#####^^^^^^^^\r\n";
    str+="^^^^^^####^^^^^^^^^^^^^^^^^^^^####^^^^^^\r\n";
    str+="^^^^^###^^^^####^^^^^^^^####^^^^###^^^^^\r\n";
    str+="^^^^###^^^^######^^^^^^######^^^^###^^^^\r\n";
    str+="^^^###^^^^^######^^^^^^######^^^^^###^^^\r\n";
    str+="^^^###^^^^^######^^^^^^######^^^^^###^^^\r\n";
    str+="^^###^^^^^^^####^^^^^^^^####^^^^^^^###^^\r\n";
    str+="^^###^^^##^^^^^^^^^^^^^^^^^^^^##^^^###^^\r\n";
    str+="^^###^^^##^^^^^^^^^^^^^^^^^^^^##^^^###^^\r\n";
    str+="^^^###^^###^^^^^^^^^^^^^^^^^^###^^###^^^\r\n";
    str+="^^^###^^^####^^^^^^^^^^^^^^####^^^###^^^\r\n";
    str+="^^^^###^^^######^^^^^^^^######^^^###^^^^\r\n";
    str+="^^^^^###^^^^^##############^^^^^###^^^^^\r\n";
    str+="^^^^^^####^^^^^^########^^^^^^####^^^^^^\r\n";
    str+="^^^^^^^^#####^^^^^^^^^^^^^^#####^^^^^^^^\r\n";
    str+="^^^^^^^^^^^########^^########^^^^^^^^^^^\r\n";
    str+="^^^^^^^^^^^^^^^##########^^^^^^^^^^^^^^^\r\n";
    str+="^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n";
    //clientSocket->write(str.toLocal8Bit());

//    QByteArray a;
//    a+=27;
//    a+=91;
//    a+=50;
//    a+=74;
//    a+=27;
//    a+=91;
//    a+=49;
//    a+=59;
//    a+=49;
//    a+=72;
//    a+=27;
//    a+=91;
//    a+=48;
//    a+=59;
//    a+=51;
//    a+=55;
//    a+=59;
//    a+=52;
//    a+=48;
//    clientSocket->write(a);


    sendFirstMessage();
    sendHelloMessage();

}


void TServer::readClient(){
    parseMessage(clientSocket->readAll());
}


void TServer::parseMessage(QByteArray aMessage){
    qDebug()<<"TServer::parseMessage";
    qDebug()<<"int"<<(int)aMessage[0]<<" "<<QString::fromLocal8Bit(aMessage);

}

void TServer::sendToClient(QByteArray aData){
    qDebug()<<"TServer::sendToClient";
    clientSocket->write(aData);
}


void TServer::sendFirstMessage(){
    qDebug()<<"TServer::sendFirstMessage()";
    QByteArray msg;
    msg+=IAC; msg+=DO; msg+=31;
    msg+=IAC; msg+=DO; msg+=24;
    msg+=IAC; msg+=WILL; msg+=1;
    msg+=IAC; msg+=WILL; msg+=3;
    sendToClient(msg);
    qDebug()<<msg;
}

void TServer::sendHelloMessage(){
    qDebug()<<"TServer::sendHelloMessage()";
    QByteArray msg("WELCOME\r\n");
    sendToClient(msg);

}
