#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTcpServer>
#include <QTcpSocket>

#include "videothread.h"
#include "volttrethread.h"
#include <QThread>


namespace Ui {
class Widget;
}

extern QSqlDatabase db;
extern QSqlQuery query;
extern QSqlTableModel *model;

extern bool isStop;//结束和开启子线程1的处理函数
extern int sendSuccess;//每条工况数据传输成功标志
extern bool playStopFlag;//暂停、继续子线程1处理函数
extern int demmandTre[1550];//绘图用到的需量值，使用下标1-1449存储数据
extern int sleepSpeed;//视频播放线程速度控制,默认25帧/s
extern int i;//用于绘图的时间累加器，单位s，每11s传递一次绘图信号

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void dealSignal(QString data);//自定义播放视频线程信号处理槽函数
    void getImage(QImage); //自定义绘图线程信号处理槽函数
    void dataFinished();//数据传送完成 or 断开连接

signals:
    void startThread(); //触发视频播放线程处理函数的信号

private slots:
    void on_stopSelcet_clicked();//暂停
    void on_playSelcet_clicked();//继续播放
    void on_accelerateSelcet_clicked();//加速数据传输
    void on_moderateSelcet_clicked();//减速数据传输
    void on_help_clicked();//帮助按钮
    void on_stopConnect_clicked();//停止连接按钮

private:
    Ui::Widget *ui;
    VideoThread *myT;
    QThread *thread;//视频播放子线程

    VoltTreThread *myT2;
    QThread *thread2;//绘图子线程
    QImage image;//保存子线程绘制的图

    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

};

#endif // WIDGET_H
