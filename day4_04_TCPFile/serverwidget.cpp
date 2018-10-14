#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器端口为：8888");

    tcpServer = new QTcpServer(this);
    //QHostAddress::Any绑定我当前网卡所有的iP 正式监听
    tcpServer->listen(QHostAddress::Any, 8888);

    //使两个按钮无效，经过设置，选项变灰(本是黑色)
    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(false);

    connect(tcpServer, &QTcpServer::newConnection,
    [=]()
    {
        tcpSocket = tcpServer->nextPendingConnection();

        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        ui->textEdit->setText(str);
        //成功连接后，才能按选择文件按钮
        ui->buttonFile->setEnabled(true);
    }
    );

    connect(&timer, &QTimer::timeout,
            [=]()
            {
                timer.stop();
                //发送真正的文件信息
                sendData();
            }
            );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//选择文件的按钮
void ServerWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    if(filePath.isEmpty() == false)
    {
        //选择文件之前清空文件名、文件大小
        fileName.clear();
        fileSize = 0;
        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        //发送文件的大小
        sendSize = 0;
        //为文件对象关联路径
        file.setFileName(filePath);
        //只读方式打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if(isOk == false)
        {
            qDebug() << "只读方式打开文件失败 106";
        }
        //提示打开文件的路径
        ui->textEdit->append(filePath);
        //选择好文件后使选择文件按钮失效，使发送按钮使能
        ui->buttonFile->setEnabled(false);
        ui->buttonSend->setEnabled(true);
    }
    else
    {
        qDebug() << "选择文件路径出错 118";
    }

}
//发送文件按钮
void ServerWidget::on_buttonSend_clicked()
{
    ui->buttonSend->setEnabled(false);
    //先发送文件头信息：让对方知道你传送的文件是哪一个
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8());
    if(len > 0)//len是写入的字节数，大于0表明头部信息发送成功
    {
        //发送真正的文件信息
        //通过定时器将头部信息和文件数据发送分开
        timer.start(20);
    }
    else
    {
        qDebug() << "头部信息发送失败 142";
        file.close();
        ui->buttonFile->setEnabled(true);//继续选择文件
        ui->buttonSend->setEnabled(false);
    }
}
//发送真正的文件信息
void ServerWidget::sendData()
{
     ui->textEdit->append("正在发送文件……");
     qint64 len = 0;
     do
     {
        //每次发送数据的大小(4kb)
        char buf[4*1024] = {};
        len = 0;
        //最多往buf中读sizeof(buf)大小数据，返回读入的字节数
        len = file.read(buf, sizeof(buf));
        //最多传输len大小的buf数据到客户端，返回传输的字节数
        len = tcpSocket->write(buf, len);
        //发送的数据累积量
        sendSize += len;
     }while(sendSize!=fileSize);

     //是否发送文件完毕
     if(sendSize == fileSize)
     {
         ui->textEdit->append("文件发送完毕");
         file.close();
         //断开客户端
         tcpSocket->disconnectFromHost();
         tcpSocket->close();
     }
}
