#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    cb.setParent(this);
    connect(&cb,&CustomButton::clicked,this,&Widget::buttonClicked);
}

Widget::~Widget()
{

}

void Widget::buttonClicked()
{
    qDebug() << "leisure button is clicked!";
}
