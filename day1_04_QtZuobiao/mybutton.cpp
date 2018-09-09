#include "mybutton.h"
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)//QWidget *parent说明了父组件的类型,因为所有的组件继承于QWidget，这里用的是多态
{
}

MyButton::~MyButton()
{
    qDebug() << "MyButton(child) object is deleted!";
}
