#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>
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
    void on_buttonAdd_clicked();//增加
    void on_buttonDel_clicked();//删除
    void on_buttonSure_clicked();//确认
    void on_buttonCancel_clicked();//取消   
    void on_buttonFind_clicked();//查找
    void on_homeReturn_clicked();//返回主界面

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
    QSqlDatabase db;
};

#endif // WIDGET_H
