#include "widget.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

QSqlDatabase db;
QSqlQuery query;
QSqlTableModel *model;

bool isStop = false;//结束和开启子线程1的处理函数
int sendSuccess;//每条工况数据发送成功标志
bool playStopFlag = true;//暂停、继续子线程1处理函数
int demmandTre[1550];//绘图用到的需量值，使用下标1-1449存储数据
int sleepSpeed = 80;//视频播放线程速度控制,默认25帧/s
int i = 1;//用于绘图的时间累加器，单位s，每11s传递一次绘图信号

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
