#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // CUSTOMBUTTON_H
