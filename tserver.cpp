#include "tserver.h"

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
    sendFirstMessage();
    sendHelloMessage();
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


}


void TServer::readClient(){
    parseMessage(clientSocket->readAll());
}


void TServer::parseMessage(QByteArray aMessage){
    qDebug()<<"TServer::parseMessage";

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
    QByteArray msg("WELCOME");
    sendToClient(msg);

}
