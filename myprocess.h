#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QObject>

#include <QProcess>

class myProcess : public QObject
{
    Q_OBJECT
public:
    explicit myProcess(QObject *parent = 0);

public slots:
        void startProcess();
        void showOutput();
        void runCommand(QString);
private:
        QProcess myProc;
        QString decodeProcessResp(QString);
signals:
        void started();
        void output(QString);


};

#endif // MYPROCESS_H
