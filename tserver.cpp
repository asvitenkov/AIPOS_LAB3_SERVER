#include "tserver.h"

TServer::TServer(QObject *parent) :
    QTcpServer(parent)
{
    if(listen(QHostAddress::Any,25)) qDebug()<<"RUN";
}



void TServer::incomingConnection(int handle){
    qDebug()<<"IC";
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readClient()));
    QByteArray array;
    array+=255;
    array+=253;
    array+=24;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
//    array+=;
    socket->write(array);
    socket->write("IA SERVER\r\n");



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
    //socket->write(str.toLocal8Bit());


}


void TServer::readClient(){
    QByteArray array;
    array = socket->readAll();
    //if(array.size()==3){
    QByteArray ar;
    //QDataStream stream(&ar,QIODevice::ReadWrite);
    if(array[0]==255 && array[1]==251 && array[2]==24){ //qDebug()<<QString::fromLocal8Bit("tip terminala");
        ar+=255;
        ar+=253;
        ar+=24;
        socket->write(ar);
        ar.clear();
        // <IAC, SB, 24, 1, IAC, SE>
        ar+=255;
        ar+=250;
        ar+=24;
        ar+=1;
        ar+=255;
        ar+=240;
        socket->write(ar);
        ar.clear();
        array=array.remove(0,3);
    }
    if(array[0]==255 && array[1]==251 && array[2]==31){
        // запрос на размер окна
        ar+=255;
        ar+=253;
        ar+=31;
        array=array.remove(0,3);
    }
    //stream.
    qDebug()<<ar;
    socket->write(ar);
    return;
    //}
    qDebug()<<array;
    //socket->write(array);
}
