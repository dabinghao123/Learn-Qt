#include "custombutton.h"
#include <QDebug>

CustomButton::CustomButton(QWidget *parent) : QPushButton(parent)
{
    this->setText("leisure button!");
    this->resize(150,150);
}


void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "left";
        QPushButton::mousePressEvent(event);//调用 QPushButton的事件函数
        qDebug() << event->isAccepted();
    }
}
