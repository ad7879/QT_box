#include "connectmainwindow.h"
#include "ui_connectmainwindow.h"

connectMainWindow::connectMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connectMainWindow)
{
    ui->setupUi(this);

    mw = new MainWindow(this);

    //获取单例模式下的用户套接字
    tcpScoket = userScoket::getSingle();

    connect(tcpScoket,&userScoket::connected,this,&connectMainWindow::dealConnectSlot);
}

connectMainWindow::~connectMainWindow()
{
    delete ui;
}

void connectMainWindow::on_pushButton_clicked()
{
    QString ip = ui->iplineEdit->text();
    QString add = ui->addresslineEdit->text();
    tcpScoket->connectToHost(QHostAddress(ip),add.toInt());
}

void connectMainWindow::dealConnectSlot()
{
    this->close();

    mw->show();
}
