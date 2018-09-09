#include <QPushButton>
#include <QDebug>
#include "mybutton.h"
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    move(0,0);
    QPushButton *b1 = new QPushButton(this);
    b1->move(100,100);
    b1->setText("^_^");
    b1->resize(100,100);

    QPushButton *b2 = new QPushButton(b1);
    b2->move(10,10);
    b2->setText("@_@");

    MyButton *b3 = new MyButton(this);
    b3->setText("123");
}

Widget::~Widget()
{
    qDebug() << "Widget(parent) is deleted!";
}
