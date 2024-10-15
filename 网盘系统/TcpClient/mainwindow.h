#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userscoket.h"
#include <QDebug>
#include <QListWidgetItem>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void showLoadFileInfo();

    void loadFile();
    ~MainWindow();

public slots:
    void dealReadyReadSlot();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    userScoket *scoket;

    QString fileName;

    int fileSize;

    bool startDownLoad = false;//标记是否在下载文件

    QFile file;//下载的文件

    int loadSize = 0;//记录已经下载的字节数
};

#endif // MAINWINDOW_H
