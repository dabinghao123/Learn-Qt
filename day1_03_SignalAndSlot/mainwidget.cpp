#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>//和c++中cout一样,但是不需要加endl就可以自动换行

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
//    QPushButton stack; //分配在栈里，函数一运行完成就释放掉了，所以不行
//    stack.setParent(this);
//    stack.setText("This button does not appear");
    b1.setParent(this);
    b1.setText("close");
    b1.move(100,100);
    b2 = new QPushButton(this);//通过构造函数指定父类
    b2->move(20,20);
    b2->setText("send to two slot functions");//输.的时候自动变成->
    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);//&(QPushButton::)pressed(括号中的就是作用域)
    connect(b2, &QPushButton::released, this, &MainWidget::mySlot);
    connect(b2, &QPushButton::released, &b1, &QPushButton::hide);

    this->setWindowTitle("老大");
    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50,50);

    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

    //处理子窗口的信号
//    connect(&w, &SubWidget::mySignal, this, &MainWidget::dealSub);
//    connect(&w, &SubWidget::mySignal, this, &MainWidget::dealSlot);
    //如果按照上面那样写，则w发出的信号不知道是带参数的还是不带参数的
    //可以利用函数指针来解决这个问题
    void (SubWidget::*funSignal)() = &SubWidget::mySignal;
    connect(&w, funSignal, this, &MainWidget::dealSub);

    void (SubWidget::*testSignal)(int, QString) = &SubWidget::mySignal;
    connect(&w, testSignal, this, &MainWidget::dealSlot);

    //Lambda表达式,用于定义并创建匿名的函数对象
    //C++11增加的新特性，项目文件： CONFIG += C++11
    QPushButton  *b4 = new QPushButton(this);
    b4->setText("Lambda表达式");
    b4->move(150,150);

    int a=10,b=100;

    connect(b4, &QPushButton::released,
            [&]()
            {
                qDebug() << "I am the anonymous function";
                a = 11;
                qDebug() << "a = " << a;
            }
           );
    connect(b4, &QPushButton::clicked,//按F1可以查看 void QAbstractButton::clicked(bool checked = false)
            [=](bool isCheck)//因为信号有参数
            {
               qDebug() << "isCheck = " << isCheck;//false
            }
           );

    this->resize(400, 300);//设置老大窗口为固定大小

}


void MainWidget::mySlot()
{
    b2->setText("文本被修改");
}


void MainWidget::changeWin()
{
    //子窗口显示
    w.show();
    //本窗口隐藏
    this->hide();
}

void MainWidget::dealSub()
{
    //子窗口隐藏
    w.hide();
    //本窗口显示
    this->show();
}

void MainWidget::dealSlot(int a, QString str)
{
    qDebug() << a << str.toUtf8().data();//250 I am a child window
}
MainWidget::~MainWidget()
{
}
