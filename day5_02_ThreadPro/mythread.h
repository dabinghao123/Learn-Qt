#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    void myTimeout();//线程处理函数
    bool isStop;//是否要停止线程处理函数
    void setFlag(bool flag);//设置isstop

signals:
    void mySignal();

public slots:


};

#endif // MYTHREAD_H
