#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QObject>

#include <QProcess>

/**
 * @brief
 *
 */
class myProcess : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit myProcess(QObject *parent = 0);
    QProcess myProc; /**< TODO */

public slots:
        /**
         * @brief
         *
         */
        void startProcess();
        /**
         * @brief
         *
         */
        void showOutput();
        /**
         * @brief
         *
         * @param QString
         */
        void runCommand(QString);
private:

        /**
         * @brief
         *
         * @param QString
         */
        QString decodeProcessResp(QString);
signals:
        /**
         * @brief
         *
         */
        void started();
        /**
         * @brief
         *
         * @param msg
         */
        void output(QByteArray msg);


};

#endif // MYPROCESS_H
