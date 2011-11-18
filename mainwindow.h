#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tserver.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; /**< TODO */

private slots:
    /**
     * @brief
     *
     * @param msg
     */
    void display(QByteArray msg);
};

#endif // MAINWINDOW_H
