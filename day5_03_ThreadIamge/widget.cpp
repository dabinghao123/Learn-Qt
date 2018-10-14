#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建需要在子线程中处理的函数所在类的对象
    myT = new MyThread;
    //创建子线程
    thread = new QThread(this);
    //移交myT对象到子线程
    myT->moveToThread(thread);
    //启动子线程
    thread->start();
    //使用signal-slot方式启动子线程处理函数
    connect(ui->pushButton, &QPushButton::pressed, myT, &MyThread::drawImage);
    connect(myT, &MyThread::updateImage, this, &Widget::getImage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getImage(QImage temp)
{
    image = temp;
    update(); //更新窗口，间接调用paintEvent()
}

void Widget::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备为窗口
    QPainter p(this); //同begin+end
    //在(50,50)处开始绘图
    p.drawImage(50, 50, image);
}
