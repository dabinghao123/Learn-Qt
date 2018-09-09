#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"//子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    int i = 3;
public slots:
    void mySlot();
    void changeWin();
    void dealSub();
    void dealSlot(int a, QString str);

private:
    QPushButton b1;//关闭窗口
    QPushButton *b2;//自定义槽
    QPushButton b3;//显示子窗口

    SubWidget w;//子窗口对象
};

#endif // MAINWIDGET_H
