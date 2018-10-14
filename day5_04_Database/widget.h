#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_buttonDel_clicked();//删除

    void on_buttonSure_clicked();//确认删除

    void on_buttonCancel_clicked();//取消删除

private:
    Ui::Widget *ui;
    QSqlDatabase db;//数据库连接
};

#endif // WIDGET_H
