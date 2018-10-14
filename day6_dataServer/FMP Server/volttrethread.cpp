#include "VoltTreThread.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QThread>

VoltTreThread::VoltTreThread(QObject *parent) : QObject(parent)
{

}
//每隔11s才被触发一次,因此坐标x轴为11个时间单位(s)
void VoltTreThread::myVoltPaint(int sec)
{
    //定义QImage绘图设备
    QImage image(1100, 300, QImage::Format_ARGB32);//QImage::Format_ARGB32背景是透明
    //填充背景为黑色
    image.fill(Qt::black);
    //定义画家，指定绘图设备
    QPainter p(&image);
    //设置字体
    p.setFont(QFont("Times New Roman",14,50));//字体类型、大小、粗细
    //相对画布为1200×300的画布确定图像位置
    int pointx=100,pointy=250;//确定坐标轴起点坐标
    int width=960,height=230;//确定坐标轴宽度跟高度

    //绘制坐标框架
    QPen pen;
    pen.setColor(Qt::white);
    p.setPen(pen);
    p.drawRect(10,5,1080,290);//外围的矩形
    p.drawLine(pointx,pointy,width+pointx,pointy);
    p.drawLine(pointx,pointy-height,pointx,pointy);

    //绘制需量曲线 ，需量最大值为3.7722e+03 最小值为2.7234e+03
    double kx=(double)width/(10); //x轴的比例系数 9.6
    double ky=(double)height/(10);//y方向的比例系数 2.3
    pen.setColor(Qt::green);//画曲线的笔
    pen.setWidth(2);
    QPen penPoint;//描点的笔
    penPoint.setColor(Qt::white);
    penPoint.setWidth(5);
    p.setRenderHint(QPainter::Antialiasing);
    for(int k=sec-10;k<sec;k++)//1→10 12→21 23→32
    {
        //由于y轴是倒着的，所以y轴坐标要pointy-demmandTre[i]*ky 其中ky为比例系数
        //曲线绘制
        p.setPen(pen);
        p.drawLine(pointx+kx*(k-(sec-10)),pointy-(demmandTre[k]-2500)/150*ky,pointx+kx*(1+k-(sec-10)),pointy-(demmandTre[k+1]-2500)/150*ky);
        //描点显示
        p.setPen(penPoint);
        p.drawPoint(pointx+kx*(k-(sec-10)),pointy-(demmandTre[k]-2500)/150*ky);
    }
    p.drawPoint(pointx+kx*(sec-(sec-10)),pointy-(demmandTre[sec]-2500)/150*ky);//绘制最后一个点

    //绘制刻度线
    QPen penDegree,penDegree2;
    penDegree.setWidth(1);
    penDegree.setColor(Qt::green);
    penDegree.setStyle(Qt::DotLine);//绘制内部的绿点网格
    penDegree2.setWidth(2);
    penDegree2.setColor(Qt::white);
    penDegree2.setStyle(Qt::SolidLine);//最上、右边的线是白实线
    p.setPen(penDegree);
    //x轴刻度线
    double xInterval = (double)10/10;//x轴刻度间隔为1
    for(int i=-1;i<9;i++)//画10条（不算原点），最后一条在for外边
    {
        //选取合适的坐标，绘制一段长度为width的直线，用于表示刻度
        p.drawLine(pointx+(i+1)*width/10,pointy,pointx+(i+1)*width/10,pointy-height);
        p.setPen(penDegree2);
        p.drawText(pointx+(i+1)*width/10,
                         pointy+15,QString::number((int)(xInterval*(sec-9+i))));
        p.setPen(penDegree);
    }
    p.setPen(penDegree2);
    p.drawLine(pointx+(9+1)*width/10,pointy,pointx+(9+1)*width/10,pointy-height);
    p.drawText(pointx+(9+1)*width/10,
                     pointy+15,QString::number((int)(xInterval*(sec))));
    //y轴刻度线
    p.setPen(penDegree);
    double yInterval = (double)1500/10;//y轴刻度间隔150
    for(int j=0;j<9;j++)
    {
        //代码较长，但是掌握基本原理即可。
        //主要就是确定一个位置，然后画一条短短的直线表示刻度。
        p.drawLine(pointx,pointy-(j+1)*height/10,
                         pointx+width,pointy-(j+1)*height/10);
        p.setPen(penDegree2);
        p.drawText(pointx-40,pointy-(j+1)*height/10,
                         QString::number((int)(yInterval*(j+1)+2500)));
        p.setPen(penDegree);
    }
    p.setPen(penDegree2);
    p.drawLine(pointx,pointy-(9+1)*height/10,
                     pointx+width,pointy-(9+1)*height/10);
    p.drawText(pointx-40,pointy-(9+1)*height/10,
                     QString::number((int)(yInterval*(9+1)+2500)));
    //坐标名称：(横轴：Times;纵轴：Demand(KW))
    p.setFont(QFont("Times New Roman",14,75));
    p.drawText(pointx+(4+1)*width/10-15,
                     pointy+30,QString("Time(s)"));
    p.drawText(pointx-70,pointy-(7+1)*height/10,
                     QString("D"));
    p.drawText(pointx-70,pointy-(6+1)*height/10,
                     QString("e"));
    p.drawText(pointx-70,pointy-(5+1)*height/10,
                     QString("m"));
    p.drawText(pointx-70,pointy-(4+1)*height/10,
                     QString("a"));
    p.drawText(pointx-70,pointy-(3+1)*height/10,
                     QString("n"));
    p.drawText(pointx-70,pointy-(2+1)*height/10,
                     QString("d"));
    p.drawText(pointx-86,pointy-(1+1)*height/10,
                     QString("(KW)"));

    emit updateImage(image);

}
