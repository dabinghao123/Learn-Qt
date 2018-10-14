#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QHostAddress>
#include <QDebug>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");

    tcpSocket = new QTcpSocket(this);
    ui->progressBar->setValue(0);
    isStart = true;//接收头部信息

    connect(tcpSocket, &QTcpSocket::readyRead,
    [=]()
    {
        QByteArray buf = tcpSocket->readAll();
        if(isStart == true)//接收头
        {
            isStart = false;

            //拆分字符串，例如QString str = "hello##1024#mike";
            //str.section("##", 0, 0)就是从0段开始，第0段结束，即hello
            fileName = QString(buf).section("##", 0, 0);
            fileSize = QString(buf).section("##", 1, 1).toInt();
            //关联文件
            file.setFileName("../day4_04_TCPFile/"+fileName);
            //接收文件大小
            recvSize = 0;
            //以只写方式打开文件
            bool isOk = file.open(QIODevice::WriteOnly);
            if(false == isOk)
            {
                qDebug() << "WriteOnly error 49";
                tcpSocket->disconnectFromHost(); //断开连接
                tcpSocket->close(); //关闭套接字
                return;
            }
            //设置进度条
            ui->progressBar->setMinimum(0); //最小值
            ui->progressBar->setMaximum(fileSize); //最大值
            ui->progressBar->setValue(0); //当前值
        }
        else //接收文件
        {
            //将接收到的buf写到文件中，返回写入的字节数
            qint64 len = file.write(buf);
            recvSize += len;
            //更新进度条
            ui->progressBar->setValue(recvSize);
            //文件接收完毕
            if(recvSize == fileSize)
            {
                file.close(); //关闭文件
                //断开连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        }
      }
    );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器的ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();
    //主动和服务器连接
    tcpSocket->connectToHost(QHostAddress(ip), port);
    isStart = true;
    ui->progressBar->setValue(0);
}
