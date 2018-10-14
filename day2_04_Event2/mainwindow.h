#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event);

};

class CustomWidget:public QWidget
{
    Q_OBJECT
public:
    CustomWidget(QWidget * parent):QWidget(parent)
    {
        ;
    }
protected:
    void mousePressEvent(QMouseEvent *event)
    {
        qDebug() << "event is passed to CustomWidget";
        QWidget::mousePressEvent(event);//函数中的第一句就是event->ignore()
    }
};

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    CustomButton(QWidget * parent):QPushButton(parent)
    {

    }
protected:
    void mousePressEvent(QMouseEvent *event)
    {
        qDebug() << "event is passed to CustomButton";
    }

};

class CustomButtonEx:public CustomButton
{
    Q_OBJECT
public:
    CustomButtonEx(QWidget * parent):CustomButton(parent)
    {}
protected:
    void mousePressEvent(QMouseEvent *event)
    {
        event->ignore();
        qDebug() << "event is passed to CustomButtonEx";
    }
};

#endif // MAINWINDOW_H
