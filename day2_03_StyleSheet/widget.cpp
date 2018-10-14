#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //所有的label的前景色为蓝色、背景色为黄色
    this->setStyleSheet("QLabel{color:blue;background-color:yellow;}");
    //给这个label单独设置为前景色为黑色、背景色为红色
    ui->label_1->setStyleSheet("QLabel{color:black;\
                             background-color:red;\
                             border-image:url(:/new/prefix1/image/butterfly.png);\
                             }");
    //给按钮设置伪状态
    ui->pushButton_1->setStyleSheet("QPushButton{\
                                  border-image:url(:/new/prefix1/image/Sunny.jpg);}\
                                  QPushButton:hover{\
                                  border-image:url(:/new/prefix1/image/OnePiece.png);}\
                                  QPushButton:pressed{\
                                  border-image:url(:/new/prefix1/image/Luffy.png);}"
                                  );
}

Widget::~Widget()
{
    delete ui;
}
