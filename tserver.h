#ifndef TSERVER_H
#define TSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextEdit>

class TServer : public QTcpServer
{
    Q_OBJECT
    enum TTCommadn {IAC=255, DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};
    enum TOptionsState {OFF=0, TRY=1, ON=2};
    static const TTCommadn TCommand;

public:
    explicit TServer(QObject *parent = 0);
    void initialize();

signals:

public slots:

private:
    void incomingConnection(int handle);
    void parseMessage(QByteArray aMessage);
    QTcpSocket *clientSocket;
    void sendToClient(QByteArray aData);
    void sendFirstMessage();
    void sendHelloMessage();
    QTextEdit *te;

    bool echoMode;


private slots:
    void readClient();

};

#endif // TSERVER_H
