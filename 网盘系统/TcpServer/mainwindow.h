#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QHostInfo>
#include <QDir>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void sendFileInfo();

    bool isHasFile(QString filename);

    void sendLoadFileData(QString fileName);

    ~MainWindow();

public slots:
    void dealNewConnectionSlot();

    void dealReadyReadSlot();

    void dealDisconnectSlot();

    void showHostIP();

    void initLoadFileName();

private:
    Ui::MainWindow *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpScoket;

    QFileInfoList fileName;//所有下载的文件信息
};

#endif // MAINWINDOW_H
