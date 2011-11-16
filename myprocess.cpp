#include "myprocess.h"
#include <QDebug>
#include <QTextCodec>

/**
* Конструктор процесса
* @param parent родительский объект
*/
myProcess::myProcess(QObject *parent) :
    QObject(parent)
{
    connect(&myProc,SIGNAL(readyReadStandardOutput()),this,SLOT(showOutput()));
    connect(&myProc,SIGNAL(readyReadStandardError()),this,SLOT(showOutput()));
}

/**
* Запускает процесс (cmd.exe)
* в случае успезного запуска посылает сигнал о старте процесса
*/
void myProcess::startProcess()
{
        QString prog="C:\\Windows\\System32\\cmd.exe";
        //QString prog="calc.exe";
        myProc.start(prog);
        if(myProc.waitForStarted())
                emit started();
        else
                qDebug()<<QString("Can't start program <b>%1</b>");
}

/**
* Посылает в процесс параметры для обработки
* @param com команда, которую необходимо выполнить
*/
void myProcess::runCommand(QString com)
{
        QString s=com+"\n";
        if(myProc.write(s.toAscii())!=-1) qDebug()<<"OK";
        int i=0;
        //while(i<100){
        //    qDebug()<<myProc.readAll();
        //    i++;
        //}
}

/**
* Читает ответ процесса и посылает сигнал и пришедшем ответе
*/
void myProcess::showOutput()
{
    QByteArray retStr;
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("CP866"));
    myProc.readLine();
    retStr = myProc.readAllStandardError();
    retStr += myProc.readAll();
    //retStr = myProc.readAllStandardOutput();
    emit output(retStr);
}


QString myProcess::decodeProcessResp(QString str){



    return str;

}
