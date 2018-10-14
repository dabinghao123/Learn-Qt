#include "mythread.h"
#include <QThread>
#include <QDebug>
#include <QMessageBox>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = false;
    qDebug() << QThread::currentThread();//与主线程号相同
}

void MyThread::myTimeout()
{
    while( !isStop )
    {
        qDebug() << QThread::currentThread();//与主线程号不同，是子线程号
        QThread::sleep(1);
        emit mySignal();//一秒触发一次信号
        if(isStop)
        {
            break;
        }
    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;
}

