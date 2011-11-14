#ifndef TSERVER_H
#define TSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextEdit>
#include "myprocess.h"

class TServer : public QTcpServer
{
    Q_OBJECT
    enum TTCommadn {IAC=255, DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};
    enum OptionsState {UNKNOWN=-1,OFF=0, ON=1, TRY_SERVER=2, TRY_CLIENT=3, CONST_ON=4, CONST_OFF=5 };
    static const TTCommadn TCommand;

public:
    explicit TServer(QObject *parent = 0);
    void initialize();

signals:

public slots:

private:
    OptionsState optionsState[40];
    bool enteringCMD;
    QByteArray cmd;
    void incomingConnection(int handle);
    void parseMessage(QByteArray aMessage);
    QTcpSocket *clientSocket;
    void sendToClient(QByteArray aData);
    void sendFirstMessage();
    void sendHelloMessage();
    QTextEdit *te;

    bool echoMode;
    bool enteringPassword;
    bool enteringLogin;
    QByteArray login;
    QByteArray password;
    void parseOptions(QByteArray aOptions);
    void parseClientData(QByteArray aData);
    bool checkAccess();
    myProcess *prc;
private slots:
    void readClient();
    void commandProcessed(QString);
    void clientDisc();

};

#endif // TSERVER_H
