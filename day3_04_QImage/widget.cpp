#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QImage *image = new QImage(400, 300, QImage::Format_RGB32);
    p.begin(image);

    //在(80,80)开始绘图，宽和高都是150
    p.drawPixmap(80,80,150,150,QPixmap(":/image/LuffyQ.png"));

    //对绘图设备250个像素点进行操作
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            image->setPixel(QPoint(i, j), qRgb(0, 255, 0));//绿色
        }
    }

    int flag = image->save("../day3_04_QImage/img.jpg");
    qDebug() << flag;

    p.end();


}

Widget::~Widget()
{
    delete ui;
}
