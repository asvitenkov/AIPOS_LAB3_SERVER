#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    return a.exec();
}
