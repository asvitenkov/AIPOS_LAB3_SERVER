#ifndef TSERVER_H
#define TSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QTextEdit>
#include "myprocess.h"

/**
 * @brief
 *
 */
class TServer : public QTcpServer
{
    Q_OBJECT
    /**
     * @brief
     *
     */
    enum TTCommadn {IAC=255, DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};
    /**
     * @brief
     *
     */
    enum OptionsState {UNKNOWN=-1,OFF=0, ON=1, TRY_SERVER=2, TRY_CLIENT=3, CONST_ON=4, CONST_OFF=5 };
    static const TTCommadn TCommand; /**< TODO */

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit TServer(QObject *parent = 0);
    /**
     * @brief
     *
     */
    void initialize();

signals:
    /**
     * @brief
     *
     * @param msg
     */
    void printToDisplay(QByteArray msg);
public slots:

private:
    OptionsState optionsState[40]; /**< TODO */
    bool enteringCMD; /**< TODO */
    QByteArray cmd; /**< TODO */
    /**
     * @brief
     *
     * @param handle
     */
    void incomingConnection(int handle);
    /**
     * @brief
     *
     * @param aMessage
     */
    void parseMessage(QByteArray aMessage);
    QTcpSocket *clientSocket; /**< TODO */
    /**
     * @brief
     *
     * @param aData
     */
    void sendToClient(QByteArray aData);
    /**
     * @brief
     *
     */
    void sendFirstMessage();
    /**
     * @brief
     *
     */
    void sendHelloMessage();

    bool echoMode; /**< TODO */
    bool enteringPassword; /**< TODO */
    bool enteringLogin; /**< TODO */
    QByteArray login; /**< TODO */
    QByteArray password; /**< TODO */
    /**
     * @brief
     *
     * @param aOptions
     */
    void parseOptions(QByteArray aOptions);
    /**
     * @brief
     *
     * @param aData
     */
    void parseClientData(QByteArray aData);
    /**
     * @brief
     *
     */
    bool checkAccess();
    myProcess *prc; /**< TODO */
private slots:
    /**
     * @brief
     *
     */
    void readClient();
    /**
     * @brief
     *
     * @param msg
     */
    void commandProcessed(QByteArray msg);
    /**
     * @brief
     *
     */
    void clientDisc();

};

#endif // TSERVER_H
