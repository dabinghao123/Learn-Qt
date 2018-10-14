#include "videothread.h"
#include <QVariant>
#include <QThread>
#include <QDebug>

VideoThread::VideoThread(QObject *parent) : QObject(parent)
{

}

void VideoThread::myVideoPlay()
{
    while(!isStop)
    {
        query.exec("select * from sheet1");
        //query.next()指向查找到的第一条记录，然后每次后移一条记录
        while (query.next())
        {
            //读取数据库每一行的工况数据
            frame = query.value(0).toInt();
            current1 = query.value(1).toDouble();
            current2 = query.value(2).toDouble();
            current3 = query.value(3).toDouble();
            voltage = query.value(4).toInt();
            label = query.value(5).toInt();
            demand = query.value(6).toDouble();
            //b:每个特征的间隔 break；bw:每帧的间隔 break widely
            QString data = QString("%1b%2b%3b%4b%5b%6b%7bw")\
                    .arg(frame).arg(current1).arg(current2)\
                    .arg(current3).arg(voltage).arg(label).arg(demand);

            emit mySignal(data);
            //如果工况数据发送失败，停止子线程1处理函数来停止读取数据
            while (sendSuccess == -1)
            {
                isStop = true;
            }

            //获取需量数据到demmandTre数组中，每隔11s发送一次绘图信号
            if(frame>24)
            {
                //总共36233帧,当读取到1449×25=36225时
                //demmandTre的[1~1449]被赋值
                if(frame%25==0 && frame<=36225)
                {
                    demmandTre[i] = demand;
                    if (i==1449)
                    {
                        i = 1;
                    }
                    //每隔11s发送一次绘图信号，最后一次是i=1441
                    if (i%11 == 0)
                    {
                        emit paintSignal(i);
                    }
                    i++;
                }
            }
            //由于帧数太多，80ms显示奇数帧
            QThread::msleep(sleepSpeed);
            //暂停、继续子线程1处理函数
            while(!playStopFlag)
            {
                ;
            }
        }
    }
}
