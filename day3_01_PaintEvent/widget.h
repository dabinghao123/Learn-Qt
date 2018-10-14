#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();
private:
    Ui::Widget *ui;
    QPainter p;
    int x;//小船横坐标
};

#endif // WIDGET_H
