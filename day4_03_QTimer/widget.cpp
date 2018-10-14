#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);
    i = 0;

    connect(myTimer, &QTimer::timeout,
            [=]()
            {
                i++;
                ui->lcdNumber->display(i);
            }
            );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonStart_clicked()
{
    if(myTimer->isActive() == false)
    {
         myTimer->start(100);
    }

}

void Widget::on_buttonStop_clicked()
{
    //如果定时器激活，才关闭
    if(myTimer->isActive() == true)
    {
        myTimer->stop();
        i = 0;
    }
}
