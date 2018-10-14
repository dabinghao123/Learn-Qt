#include "mythread.h"
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QBrush>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::drawImage()
{
    //定义QImage绘图设备
    QImage image(500, 500, QImage::Format_ARGB32);
    //定义画家，指定绘图设备
    QPainter p;
    p.begin(&image);

    //重新定义画笔，用于绘制轮廓线
    QPen pen;
    pen.setWidth(5);
    //把画笔交给画家
    p.setPen(pen);
    //重新定义画刷，用于绘制填充色
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    //把画刷交给画家
    p.setBrush(brush);

    //定义5个点，画五边形
    QPoint a[] =
    {
       //%2就是0或1,qrand()用于产生随机数
       //%500就是控制在500以内
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500),
       QPoint(qrand()%500, qrand()%500)
    };
    p.drawPolygon(a, 5);

    p.end();

    //通过信号发送图片
    emit updateImage(image);

}

