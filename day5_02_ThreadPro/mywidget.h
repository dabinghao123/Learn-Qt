#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealSignal();//在主线程控制数码管

signals:
    void startThread();//主线程信号

private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

private:
    Ui::MyWidget *ui;
    MyThread *myT;
    QThread *thread;

};

#endif // MYWIDGET_H
