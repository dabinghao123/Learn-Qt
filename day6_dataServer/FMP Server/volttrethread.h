#ifndef VoltTreThread_H
#define VoltTreThread_H

#include <QObject>
#include <QImage>

extern int demmandTre[1550];//绘图用到的需量值，使用下标1-1449存储数据

class VoltTreThread : public QObject
{
    Q_OBJECT
public:
    explicit VoltTreThread(QObject *parent = 0);
    //子线程2处理函数
    void myVoltPaint(int sec);

signals:
    void updateImage(QImage temp);

public slots:
};

#endif // VoltTreThread_H
