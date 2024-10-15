#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ROOTPATH "C:/Users/Lenovo/Desktop/C++笔记"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,2024);

    connect(tcpServer,&QTcpServer::newConnection,this,&MainWindow::dealNewConnectionSlot);

    //显示主机所有IP
    showHostIP();

    //初始化所有文件名
    initLoadFileName();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLoadFileName()
{
    //关联目录
    QDir dir(QString(ROOTPATH));
    fileName = dir.entryInfoList(QDir::Files);//过滤 . .. 文件

#if 0
    QFileInfo info;

    for(QFileInfoList::iterator it=fileName.begin();it!=fileName.end();it++)
    {
        info = *it;
        qDebug()<<info.fileName();

        QByteArray a = info.fileName().toLocal8Bit();
        tcpScoket->write(a.data(),a.size());
    }
#endif
}

void MainWindow::dealNewConnectionSlot()
{
    //取得连接
    tcpScoket = tcpServer->nextPendingConnection();

    //发送文件信息(文件名 + 文件大小)给客户端
    sendFileInfo();
    //信号槽连接
    connect(tcpScoket,&QTcpSocket::readyRead,this,&MainWindow::dealReadyReadSlot);

    //如果断开连接 自动发送信号disconnected
    connect(tcpScoket,&QTcpSocket::disconnected,this,&MainWindow::dealDisconnectSlot);
}

void MainWindow::sendFileInfo()
{
    //循环获取文件信息
    QFileInfo info;

    QString file;

    for(QFileInfoList::iterator it=fileName.begin();it!=fileName.end();it++)
    {
        info = *it;
        file = file.append(QString("%1,%2;").arg(info.fileName()).arg(info.size()));
    }

    qDebug()<<file;
    //发送给客户端
    QByteArray a = file.toLocal8Bit();
    tcpScoket->write(a.data(),a.size());
}

//判断文件是否存在
bool MainWindow::isHasFile(QString filename)
{
    initLoadFileName();//更新文件信息

    QFileInfo info;
    //在文件的属性列表里匹配
    for(QFileInfoList::iterator it=fileName.begin();it!=fileName.end();it++)
    {
        info = *it;
        if(info.fileName() == filename)
        {
            return true;
        }
    }
    return false;
}

//处理发送的文件数据
void MainWindow::sendLoadFileData(QString fileName)
{
    //创建文件对象
    QFile file(QString(ROOTPATH)+'/'+fileName);

    //以只读的方式打开文件
    if(!file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->append(fileName+" 打开失败");
        return;
    }
    ui->textEdit->append(fileName+" 打开成功");

    //发送数据
    //关联文件
    QDataStream stream(&file);

    int len;//实际读到的字节数
    char buf[1024*5] = "/0";

    //从文件循环读取数据并发送给客户端
    do
    {
        //从文件读取数据
        len = stream.readRawData(buf,1024*5);
        //发送数据
        tcpScoket->write(buf,len);

        tcpScoket->waitForBytesWritten(500);

        QThread::sleep(1);
    }while(len>0);

    ui->textEdit->append(fileName+" 发送成功");

    //关闭文件
    file.close();
}

void MainWindow::dealReadyReadSlot()
{
    //接收客户端要下载的文件名
    QString fileName = QString::fromLocal8Bit(tcpScoket->readAll());

    //判断该文件是否存在
    if(!isHasFile(fileName))
    {
        //说明文件不存在
        ui->textEdit->append(fileName+" 文件不存在");
        return;
    }
    ui->textEdit->append(fileName+" 开始下载");

    //发送要下载的内容
    sendLoadFileData(fileName);
}

//客户端断开连接执行
void MainWindow::dealDisconnectSlot()
{
    if(tcpScoket == NULL)
    {
        return;
    }
    tcpScoket->close();
    tcpScoket = NULL;
}

void MainWindow::showHostIP()
{
    //获取主机名
    QString localhostname = QHostInfo::localHostName();

    //根据主机名获取主机IP
    QHostInfo info = QHostInfo::fromName(localhostname);

    //获取所有地址
    QList<QHostAddress> list = info.addresses();

    //将list转为QString类型 过滤IPV4地址 并存入容器
    QStringList ips;//容器
    for(int i=0;i<list.size();i++)
    {
        //判断地址是否是IPV4
        if(list[i].protocol()==QAbstractSocket::IPv4Protocol)
        {
            ips.append(list[i].toString());//将QHostAddress转为QString类型
        }
    }

    //将匹配到的ip 设置到下拉列表
    ui->ipcomboBox->insertItems(0,ips);//0 表示索引
}
