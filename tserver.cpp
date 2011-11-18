#include "tserver.h"
#include "myprocess.h"
#include <QChar>
#include <QTextCodec>





TServer::TServer(QObject *parent) :
    QTcpServer(parent)
{
    qDebug()<<"TServer::TServer";


}


void TServer::initialize(){
    qDebug()<<"TServer::initialize";
    echoMode = true;
    enteringLogin = false;
    enteringPassword = false;
    for(int i=0;i<40;i++) optionsState[i]=CONST_OFF;
    optionsState[1]=CONST_ON;
    //optionsState[31]=CONST_ON;
    optionsState[3]=CONST_ON;
    password.clear();
    login.clear();
    enteringCMD = false;
    cmd.clear();
    clientSocket = NULL;




}


void TServer::incomingConnection(int handle){
    qDebug()<<"TServer::incomingConnection";
    if(clientSocket!=NULL) return;
    clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(handle);
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect((clientSocket),SIGNAL(disconnected()),this,SLOT(clientDisc()));
    emit printToDisplay(QString(QString("incoming connection from ")+clientSocket->peerAddress().toString()).toLocal8Bit());



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

    sendFirstMessage();
    clientSocket->write(str.toLocal8Bit());
    sendHelloMessage();

}


void TServer::readClient(){
    qDebug()<<"readClient";
    parseMessage(clientSocket->readAll());
}


void TServer::parseMessage(QByteArray aMessage){
    qDebug()<<"TServer::parseMessage";
    QByteArray ars; ars+=255;
    if(aMessage.indexOf((char)255)!=-1 && aMessage.size()==2) return;
    //for(int i=0;i<aMessage.size();i++)
    qDebug()<<"int "<<(int)aMessage[0]<<" "<<QString::fromLocal8Bit(aMessage)<<" "<<aMessage.size();
    //int pos=-1;
    QByteArray outputData;
    int pos=aMessage.indexOf((char)IAC);
    while(pos!=-1){
        // всё что до 255 записываем на принтер
        //lastChar = aMessage[pos];
        outputData += aMessage.mid(0,pos);
        aMessage = aMessage.remove(0,pos+1);
        // удалили разбираем дальше
        // за 255 может быть подопция опция или символ 255
        if(aMessage[0]==(char)SB){
            // подопция
            // извлекаем
            QByteArray subOptions;
            int indexSE=aMessage.indexOf(SE);
            subOptions = aMessage.mid(0,indexSE+1);
            aMessage = aMessage.remove(0,indexSE+1);
        }
        else if (aMessage[0]!=(char)255){
            // опция
            QByteArray options;
            options+=aMessage[0];
            options+=aMessage[1];
            if(options[0]>=251)
                parseOptions(options);
            aMessage.remove(0,2);

        }
        else{
            // символ 255
            outputData+=255;
            aMessage.remove(0,1);
        }


        pos = aMessage.indexOf(IAC);
    }
    outputData+=aMessage;
    //emit printMessageSignal(outputData);
    parseClientData(outputData);
    outputData.clear();

}

void TServer::sendToClient(QByteArray aData){
    qDebug()<<"TServer::sendToClient";
    qDebug()<<aData.size();
    if(clientSocket!=NULL){
        int pos = aData.indexOf((char)IAC);
        while(pos!=-1){
            qDebug()<<"######## "<<(int)aData.at(pos+1);
            if ((aData.at(pos+1)!=(char)250) && (aData.at(pos+1)!=(char)251) &&(aData.at(pos+1)!=(char)252) &&(aData.at(pos+1)!=(char)253)&&(aData.at(pos+1)!=(char)254)){
                aData = aData.insert(pos,IAC);
                pos = aData.indexOf(IAC,pos+2);
            }
            else pos = aData.indexOf(IAC,pos+1);
        }
        clientSocket->write(aData);
    }
}


void TServer::sendFirstMessage(){
    qDebug()<<"TServer::sendFirstMessage()";
    QByteArray msg;
    msg+=IAC; msg+=WILL; msg+=1;
    msg+=IAC; msg+=WILL; msg+=3;
    sendToClient(msg);
    qDebug()<<msg;
}

void TServer::sendHelloMessage(){
    qDebug()<<"TServer::sendHelloMessage()";
    enteringLogin = true;
    QByteArray msg("WELCOME\r\nLogin: ");
    sendToClient(msg);

}




void TServer::parseOptions(QByteArray aOptions){
    qDebug()<<"TSession::parseOptions";
    // вообще то может на какие то опции нужно отвечать и подругому - хз
    if(aOptions.size()!=2) return;
    QByteArray answer;
    int option=(int)aOptions[1];
    int param = (int)aOptions[0]+256;
    answer+=255;
    if((param==253 && option == 1)||(param==251 && option==3)) return;
    if((option==31 || option==24) && param == 254){
        answer+=WONT;
        answer+=option;
        sendToClient(answer);
        return;
    }
    switch(param){
    case 251: // WILL
        // клиент хочет включить эту опцию
        // проверяем состояние этой опции
        if(optionsState[option]==CONST_ON){
            // опция может быть вкдючена
            answer+=WILL;
        }
        else if(optionsState[option]==CONST_OFF){
            // опцию нельзя включить
            answer+=WONT;
        }
        else{
            // меняем состояние опции
            optionsState[option]=ON;
            answer+=DO;
        }
        break;
    case 252: //WONT
        if(optionsState[option]==CONST_OFF){
            answer+=DONT;
        }
        else{
            optionsState[option]=OFF;
            answer+=DONT;
        }
        break;
    case 253: // DO
        if(optionsState[option]==CONST_OFF){
            answer+=WONT;
        }
        else if(optionsState[option]==CONST_ON){
            answer+=WILL;
        }
        else{
            optionsState[option]=ON;
            answer+=WILL;
        }
        break;
    case 254: // DONT
        if(optionsState[option]==CONST_OFF){
            answer+=WONT;
        }
        else{
            optionsState[option]=OFF;
            answer+=WONT;
        }
        break;
    }
    answer+=option;
    if(answer.size()==3)sendToClient(answer);
}



void TServer::parseClientData(QByteArray aData){
    qDebug()<<"TServer::parseClientData(QByteArray aData)";
//    emit printToDisplay(aData);
    if(aData.isEmpty()) return;
    while(!aData.isEmpty()){
        if(aData[0]==(char)8){

            if(echoMode){
                if(enteringPassword){
                    if(!password.isEmpty())
                        sendToClient(QString(aData.at(0)).toLocal8Bit());
                    password.remove(password.size()-1,1);
                }
                else if(enteringLogin){
                    if(!login.isEmpty())
                        sendToClient(QString(aData.at(0)).toLocal8Bit());
                    login.remove(login.size()-1,1);
                }
                else if(enteringCMD){
                    if(!cmd.isEmpty())
                        sendToClient(QString(aData.at(0)).toLocal8Bit());
                    cmd.remove(cmd.size()-1,1);
                }
            }

            aData.remove(0,1);
            continue;
        }
        if(echoMode){
            if(enteringPassword){
                if(aData[0]!=13){
                    sendToClient(QString('*').toLocal8Bit());
                    password.push_back(aData);
                }
                else{
                    // это перевод строки ввод пароля закончился
                    emit printToDisplay(password);
                    sendToClient(QString("\r\n").toLocal8Bit());
                    if(checkAccess()){
                        // user entering
                        sendToClient(QString("Login and password accepted\r\n").toLocal8Bit());
                        enteringCMD = true;
                        enteringPassword = false;
                        enteringLogin = false;

                        prc = new myProcess;
                        prc->startProcess();
                        connect(prc,SIGNAL(output(QByteArray)),this,SLOT(commandProcessed(QByteArray)));
                    }
                    else{
                        // don't entering
                        enteringPassword = false;
                        enteringLogin = true;
                        login.clear();
                        password.clear();
                        sendToClient(QString("Login or password password incorrect\r\nLogin: ").toLocal8Bit());
                    }
                    return;
                }
            }
            if(enteringLogin){
                if(aData[0]!=13){
                    login.push_back(aData[0]);
                    sendToClient(QString(aData.at(0)).toLocal8Bit());
                }
                else{
                    // ввод логина закончился
                    emit printToDisplay(login);
                    sendToClient(QString("\r\nPassword: ").toLocal8Bit());
                    enteringLogin = false;
                    enteringPassword = true;

                }
            }
            if(enteringCMD){
                if(aData[0]!=13){
                    cmd.push_back(aData[0]);
                    sendToClient(QString(aData.at(0)).toLocal8Bit());
                }
                else{
                    sendToClient(QString("\r\n").toLocal8Bit());
                    emit printToDisplay(cmd);
                    prc->runCommand(cmd);
                    qDebug()<<prc->myProc.readLine();
                    if(QString(cmd)=="exit"){
                        disconnect(clientSocket,SIGNAL(readyRead()),this,SLOT(readClient()));
                        clientSocket->disconnectFromHost();
                        clientSocket->deleteLater();
                        //clientSocket->waitForBytesWritten();
                        clientSocket = NULL;
                        enteringCMD = false;
                    }

                    cmd.clear();
                }
            }

        }
        aData=aData.remove(0,1);
        if(aData[0]==10) aData=aData.remove(0,1);
    }

}


bool TServer::  checkAccess(){
    qDebug()<<"checkAccess";
    qDebug()<<login<<" "<<password;
    if(QString(login)=="admin" && QString(password)=="pass")
        return true;
    else return false;
}


void TServer::commandProcessed(QByteArray msg){
    qDebug()<<"commandProcessed";
    //res=res.remove(res);
    sendToClient(msg);
    //emit printToDisplay(msg);
    //sendToClient(res.toLocal8Bit());
    qDebug()<<msg;
}



void TServer::clientDisc(){
    disconnect(clientSocket,SIGNAL(readyRead()),this,SLOT(readClient()));
    clientSocket->disconnectFromHost();
    clientSocket->deleteLater();
    clientSocket = NULL;
    enteringCMD = false;
    enteringLogin = true;
    enteringPassword = false;
    login.clear();
    password.clear();
    cmd.clear();
    emit printToDisplay(QString("close connection").toLocal8Bit());
}




