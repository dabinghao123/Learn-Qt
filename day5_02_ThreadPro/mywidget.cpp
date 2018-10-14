#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QMessageBox>


MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //创建需要在子线程中处理的函数所在类的对象
    myT = new MyThread;
    //创建子线程
    thread = new QThread(this);
    //移交myT对象到子线程
    myT->moveToThread(thread);
    qDebug() << "主线程号：" << QThread::currentThread();

    //如果使用Qt::DirectConnection，因为子线程的无限循环会卡死程序
    connect(this, &MyWidget::startThread, myT, &MyThread::myTimeout,Qt::QueuedConnection);

    connect(myT, &MyThread::mySignal, this, &MyWidget::dealSignal);
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::dealSignal()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void MyWidget::on_buttonStart_clicked()
{
    if(thread->isRunning() == true)
    {
        return;
    }
    //启动子线程
    thread->start();
    //使能子线程处理函数
    myT->setFlag(false);

    //直接调用后，子线程处理函数和主线程是在同一个线程
    //导致程序卡死，因为自定义线程里有个无限循环
    //myT->myTimeout();

    //主线程发出信号，用于启动子线程处理函数
    emit startThread();
}

void MyWidget::on_buttonStop_clicked()
{
    if(thread->isRunning() == false)
    {
        return;
    }
    //关闭子线程处理函数
    myT->setFlag(true);
    //关闭子线程
    thread->terminate();
}
