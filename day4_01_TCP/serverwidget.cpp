#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器: 8888");
    tcpSocket = NULL;

    tcpServer = new QTcpServer(this);
    //QHostAddress::Any绑定我当前网卡所有的iP 正式监听
    tcpServer->listen(QHostAddress::Any, 8888);

    //如果连接成功，服务器会触发newConnection()
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                //取出队列中建立好连接的通信套接字
                tcpSocket = tcpServer->nextPendingConnection();

                //获取对方(客户端)的IP和端口
                QString ip = tcpSocket->peerAddress().toString();
                qint16 port = tcpSocket->peerPort();
                //格式化显示[::ffff:127.0.0.1:10077]:成功连接
                QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
                ui->textEditRead->setText(temp);

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=]()
                        {
                            QByteArray array = tcpSocket->readAll();
                            ui->textEditRead->append(array);
                        }
                        );

            }
            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonSend_clicked()
{
   //在新的连接被建立时，才可以取出队列中建立好连接的通信套接字
   //在此之前，tcpSocket仅是个没有指向的指针，因此直接点击send按钮会出现错误
    if(tcpSocket == NULL)
    {
        return;
    }
    QString str = ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8());
}

void ServerWidget::on_buttonClose_clicked()
{
    if(tcpSocket == NULL)
    {
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}
