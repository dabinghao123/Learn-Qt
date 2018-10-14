#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "custombutton.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    void buttonClicked();
    ~Widget();

     CustomButton cb;
};

#endif // WIDGET_H
