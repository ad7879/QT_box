#ifndef CONNECTMAINWINDOW_H
#define CONNECTMAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include "mainwindow.h"
#include "userscoket.h"

namespace Ui {
class connectMainWindow;
}

class connectMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit connectMainWindow(QWidget *parent = 0);
    ~connectMainWindow();

private slots:
    void on_pushButton_clicked();

    void dealConnectSlot();

private:
    Ui::connectMainWindow *ui;
    userScoket *tcpScoket;
    MainWindow *mw;
};

#endif // CONNECTMAINWINDOW_H
