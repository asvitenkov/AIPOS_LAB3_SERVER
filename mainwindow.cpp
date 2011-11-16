#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TServer *server = new TServer(this);
    connect(server,SIGNAL(printToDisplay(QByteArray)),this,SLOT(display(QByteArray)));
    server->initialize();
    if(server->listen(QHostAddress::LocalHost,25))
        qDebug()<<"SERVER RUN";
    else qDebug()<<server->errorString();

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::display(QByteArray msg){
    ui->textEdit->append(QTime::currentTime().toString("hh:mm:ss")+" "+QString::fromLocal8Bit(msg));
    //ui->textEdit->textCursor().insertText(QString(msg));
}
