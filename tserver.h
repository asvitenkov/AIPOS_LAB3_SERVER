#ifndef TSERVER_H
#define TSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class TServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TServer(QObject *parent = 0);

signals:

public slots:

private:
    void incomingConnection(int handle);

    QTcpSocket *socket;


private slots:
    void readClient();

};

#endif // TSERVER_H
