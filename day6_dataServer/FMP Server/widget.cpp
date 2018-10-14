#include "widget.h"
#include "ui_widget.h"

#include <QPixmap>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //===设置标题及页面===
    setWindowTitle("电熔镁炉数据中继服务器");
    setWindowIcon(QIcon(QPixmap(":/image/服务器.bmp")));

    //===设置界面按钮外观===
    ui->playSelcet->setStyleSheet("QPushButton{border-image: url(:/image/播放.bmp);}\
                                  QPushButton:hover{border-image: url(:/image/播放鼠标悬浮.bmp);}");
    ui->stopSelcet->setStyleSheet("QPushButton{border-image: url(:/image/暂停.bmp);}\
                                  QPushButton:hover{border-image: url(:/image/暂停鼠标悬浮.bmp);}");
    ui->accelerateSelcet->setStyleSheet("QPushButton{border-image: url(:/image/加速.bmp);}\
                                        QPushButton:hover{border-image: url(:/image/加速鼠标悬浮.bmp);}");
    ui->moderateSelcet->setStyleSheet("QPushButton{border-image: url(:/image/减速.bmp);}\
                                      QPushButton:hover{border-image: url(:/image/减速鼠标悬浮.bmp);}");
    ui->stopConnect->setStyleSheet("QPushButton{border-image: url(:/image/断开连接.bmp);}\
                                   QPushButton:hover{border-image: url(:/image/断开连接鼠标悬浮.bmp);}");
    ui->help->setStyleSheet("QPushButton{border-image: url(:/image/帮助.bmp);}\
                            QPushButton:hover{border-image: url(:/image/帮助鼠标悬浮.bmp);}");

    //===MenuBar===
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("编辑");
    QAction *pNew = pFile->addAction("断开数据传输");
    connect(pNew, &QAction::triggered, this, &Widget::dataFinished);
    QMenu *pFile2 = mBar->addMenu("帮助");
    QAction *pNew2 = pFile2->addAction("关于服务器");
    connect(pNew2, &QAction::triggered,
           [=]()
           {
               QMessageBox::about(this,"关于服务器",\
               QString("<center><h4>服务器端功能</h4></center><BODY>\
                        ---在线工况视频播放<BR>---工况数据表显示<BR>\
                        ---需量趋势图绘制<BR>---数据传输控制(调速、启停)<BR>\
                        ---客户端连接信息显示<BR>---当前工况播报</BODY>"));
           }
           );

    //===数据库===
    //添加数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE","a");
    //设置数据库信息
    db.setDatabaseName("../Resource/database.db");

    //打开数据库
    if(!db.open())
    {
        qDebug() << "Failed to open database1";
    }
    else
    {
        qDebug() << "succeed in opening database1";
    }
    //以下执行相关sql语句
    query = QSqlQuery(db);
    //设置模型，替代QSqlQuery
    model = new QSqlTableModel(this,db);
    //指定数据库表
    model->setTable("sheet1");
    //显示model里的数据
    model->select();

    //===SOCKET===
    tcpSocket = NULL;
    //监听套接字
    tcpServer = new QTcpServer(this);
    //QHostAddress::Any绑定我当前网卡所有的iP 正式监听
    tcpServer->listen(QHostAddress::Any, 8888);
    //如果连接成功，服务器会触发newConnection()
    connect(tcpServer, &QTcpServer::newConnection,
            [=]()
            {
                qDebug() << "服务器被客户端连接！";

                //数据初始化
                sleepSpeed = 80;//视频播放线程速度控制,默认25帧/s
                playStopFlag = true;//暂停、继续子线程1处理函数
                for(int m=0;m<1550;m++)
                {
                    demmandTre[m] = 0;//绘图用到的需量值，使用下标1-1449存储数据
                }
                i = 1;//用于绘图的时间累加器，单位s，每11s传递一次绘图信号

                //==显示工况数据表==
                //把model放在QTabelView组件中
                ui->tableView->setModel(model);
                //设置model的编辑策略：不能编辑
                ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                ui->tableView->setAlternatingRowColors(true);//奇偶行区分颜色样式

                //==读取数据库工况数据==
                //启动子线程1
                thread->start();
                //使能子线程1处理函数
                isStop = false;
                //主线程发出信号，用于启动子线程1中处理函数来读取数据
                emit startThread();

                //==绘制需量趋势图==
                //启动绘图子线程2
                thread2->start();

                //==显示客户端连接信息==
                //取出队列中建立好连接的通信套接字
                tcpSocket = tcpServer->nextPendingConnection();
                //获取对方(客户端)的IP和端口
                              QString ip = tcpSocket->peerAddress().toString();
                              qint16 port = tcpSocket->peerPort();
                              QString temp = QString("<BR><BR><BR><center><h3>客户端[%1:%2]\
                                                成功连接</h3></center>").arg(ip).arg(port);
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

    //===子线程1处理===
    myT = new VideoThread;
    thread = new QThread(this);
    myT->moveToThread(thread);
    connect(this, &Widget::startThread, myT, &VideoThread::myVideoPlay);
    connect(myT, &VideoThread::mySignal, this, &Widget::dealSignal);

    //===子线程2处理===
    myT2 = new VoltTreThread;
    thread2 =new QThread(this);
    myT2->moveToThread(thread2);
    connect(myT,&VideoThread::paintSignal,myT2,&VoltTreThread::myVoltPaint);
    connect(myT2,&VoltTreThread::updateImage,this,&Widget::getImage);
}


Widget::~Widget()
{
    delete ui;
}

//接收线程1中的一条组包为data的工况数据并处理
void Widget::dealSignal(QString data)
{
    //在新的连接被建立时，才可以取出队列中建立好连接的通信套接字
    //在此之前，tcpSocket仅是个没有指向的指针，因此执行tcpSocket操作会出错
    if(tcpSocket==NULL)
    {
        return;
    }
    int frame = data.section("b",0,0).toInt();
    //显示奇数帧视频图片
    if(frame%2 != 0)
    {
       ui->videoPlay->setPixmap(QPixmap(QString("../Resource/videoPictureWhole/%1.jpg").arg(frame)));
       ui->videoPlay->setScaledContents(true);
    }
    //传输数据到客户端
    sendSuccess = tcpSocket->write( data.toUtf8() );
    while(sendSuccess==-1)
    {
       QMessageBox::warning(this,"警告","发送失败,请关闭此次连接建立新连接");
    }
    //显示工况状态
    switch (data.section("b",5,5).toInt()) {
    case 1:
       ui->messageScroll->setText(QString("<BR><BR><BR><center><h3>当前数据\
        传送到第 %1 帧<br>状态:火焰形态稳定、颜色明亮</h3></center>").arg(frame));
       break;
    case 2:
       ui->messageScroll->setText(QString("<BR><BR><BR><center><h3>当前数据\
        传送到第 %1 帧<br>状态:火焰面积明显小于正常熔炼及欠烧的火焰面积，\
        火焰颜色发暗</h3></center>").arg(frame));
       break;
    case 3:
       ui->messageScroll->setText(QString("<BR><BR><BR><center><h3>当前数据\
        传送到第 %1 帧<br>状态:亮度持续增加,火焰可视区域覆盖整个炉口</h3></center>").arg(frame));
       break;
    case 4:
       ui->messageScroll->setText(QString("<BR><BR><BR><center><h3>当前数据\
        传送到第 %1 帧<br>状态:炉口有火星溅出</h3></center>").arg(frame));
       break;
    case 5:
       ui->messageScroll->setText(QString("<BR><BR><BR><center><h3>当前数据\
       传送到第 %1 帧<br>状态:亮度相对正常工况偏低</h3></center>").arg(frame));
       break;
    default:
       break;
    }
    //全部数据处理完后的操作
    if (frame == 36233)
    {
       //暂停子线程1处理函数
       playStopFlag = false;

    //       int ret = QMessageBox::question(this,"提示","全部数据已经传输完成，\
       是否要继续重新传送数据？",
    //                             QMessageBox::Ok|QMessageBox::Cancel);
       int ret = QMessageBox::Ok;
       switch (ret) {
       case QMessageBox::Ok:
           //继续子线程1处理函数，再读一遍工况数据
           playStopFlag = true;
           break;
       case QMessageBox::Cancel:
           Widget::dataFinished();
           break;
       default:
           break;
       }
    }
}
//将在线程2中绘制的图片显示到主界面中
void Widget::getImage(QImage temp)
{
    ui->voltageTrend->setPixmap(QPixmap::fromImage(temp));
    ui->voltageTrend->setScaledContents(true);
}

//断开连接
void Widget::dataFinished()
{
    //在新的连接被建立时，才可以取出队列中建立好连接的通信套接字
    //在此之前，tcpSocket仅是个没有指向的指针，因此执行tcpSocket操作会出错
    if(tcpSocket==NULL)
    {
        return;
    }
    //关闭子线程
    isStop = true;//结束子线程1的处理函数
    thread->terminate();//结束子线程1
//    thread->wait();
    thread2->terminate();//结束子线程2
//    thread2->wait();

    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;

    //关闭提示
    ui->videoPlay->setPixmap(QPixmap(":/image/出错了.bmp"));
    ui->voltageTrend->clear();
    ui->textEditRead->setText("<center><h3>连接已经断开</h3></center>");
    ui->messageScroll->setText("<center><h3>连接已经断开</h3></center>");
    ui->tableView->setModel(new QSqlTableModel(this));
    model->select();//不显示数据
}

//暂停
void Widget::on_stopSelcet_clicked()
{
    playStopFlag = false;
}
//继续播放
void Widget::on_playSelcet_clicked()
{
    playStopFlag = true;
}

//数据加速传输
void Widget::on_accelerateSelcet_clicked()
{
    if(sleepSpeed != 80)
    {
        sleepSpeed -= 80;
    }
    else
    {
        QMessageBox::about(this,"警告","速度已经到达最大！！！");

    }
}
//数据减速传输
void Widget::on_moderateSelcet_clicked()
{
    if(sleepSpeed != 480)
    {
        sleepSpeed += 80;
    }
    else
    {
        QMessageBox::about(this,"警告","速度已经是最小！！！");
    }
}
//帮助按钮
void Widget::on_help_clicked()
{
    QMessageBox::about(this,"关于服务器",\
                       QString("<center><h4>服务器端功能</h4></center><BODY>\
                                ---在线工况视频播放<BR>---工况数据表显示<BR>\
                                ---需量趋势图绘制<BR>---数据传输控制(调速、启停)<BR>\
                                ---客户端连接信息显示<BR>---当前工况播报</BODY>"));
}
//停止按钮
void Widget::on_stopConnect_clicked()
{
    dataFinished();
}
