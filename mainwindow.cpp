#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TServer *server = new TServer(this);
    server->initialize();
    if(server->listen(QHostAddress::LocalHost,25))
        qDebug()<<"SERVER RUN";
    else qDebug()<<server->errorString();
}

MainWindow::~MainWindow()
{
    delete ui;
}
