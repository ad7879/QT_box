#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scoket = userScoket::getSingle();

    connect(scoket,&userScoket::readyRead,this,&MainWindow::dealReadyReadSlot);
}

void MainWindow::showLoadFileInfo()
{
    QByteArray a = scoket->readAll();
    QString msg = QString::fromLocal8Bit(a);
    qDebug()<<msg;

    //分割收到的文件属性字符串  以;为分隔符
    QStringList list = msg.split(";");

    ui->listWidget->addItems(list);
}

//接收数据
void MainWindow::loadFile()
{
    QByteArray msg = scoket->readAll();

    //收到数据存入同名文件
    QDataStream stream(&file);

    //写入 返回len 实际写入的字节数
    int len = stream.writeRawData(msg.data(),msg.size());

    //统计下载文件的总长度
    loadSize += len;

    //设置界面进度条
    ui->progressBar->setValue(loadSize);

    //判断文件是否下载完毕
    if(loadSize == fileSize)
    {
        //下载状态设置为false
        startDownLoad = false;

        //下载按钮不可用
        ui->pushButton->setEnabled(false);

        loadSize = 0;

        //关闭文件
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealReadyReadSlot()
{
    if(startDownLoad)
    {
        //下载文件
        loadFile();
    }
    else
    {
        //在列表框显示下拉列表
        showLoadFileInfo();
    }
}

//单击选择
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //获取用户点击的想下载的文件名
    QString fileInfo = item->text();

    //分割 提取文件名
    QStringList str = fileInfo.split(',');
    fileName = str[0];
    fileSize = str[1].toInt();//将QString类型转为int

    //下载按钮使能
    ui->pushButton->setEnabled(true);

    //设置进度条
    ui->progressBar->setMaximum(fileSize);
}

//下载按钮
void MainWindow::on_pushButton_clicked()
{
    //准备同名文件(创建 并以可写的方式打开)

    //1.用户可以选择目录 getExistingDirectory
    QString dirPath = QFileDialog::getExistingDirectory(this,"选择要下载的文件夹","C:/");

    //2.
    file.setFileName(dirPath + "/" + fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    //更新当前状态为下载文件状态
    startDownLoad = true;

    //将要下载的文件名发给服务器
    QByteArray a = fileName.toLocal8Bit();
    scoket->write(a.data(),a.size());
}
