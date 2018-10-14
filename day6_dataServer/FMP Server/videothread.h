#ifndef VideoThread_H
#define VideoThread_H
#include <QObject>
#include <QSqlQuery>

extern QSqlQuery query;

extern bool isStop;//结束和开启子线程1的处理函数
extern int sendSuccess;//每条工况数据传输成功标志
extern bool playStopFlag;//暂停、继续子线程1处理函数标志
extern int demmandTre[1550];//绘图的时候按秒计时
extern int sleepSpeed;//视频播放线程速度控制,默认25帧/s
extern int i;//用于绘图的时间累加器，单位s，每11s传递一次绘图信号

class VideoThread : public QObject
{
    Q_OBJECT
public:
    explicit VideoThread(QObject *parent = 0);

    //线程处理函数
    void myVideoPlay();
    //工况数据
    int frame;//36233帧
    double current1;
    double current2;
    double current3;
    int voltage;
    int label;
    int demand;

signals:
    void mySignal(QString data);//播放视频信号
    void paintSignal(int sec);//画图信号 每秒画一次图

private:

public slots:
};

#endif // VideoThread_H
