#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap *pixmap = new QPixmap(400,300);
    p.begin(pixmap);

    //填充白色背景色,(0,0)是起点坐标，400是宽度，300是高度
    p.fillRect(0, 0, 400, 300, QBrush(Qt::white));
    //(0,0)是起点坐标，80是宽度，80是高度
    p.drawPixmap(0, 0, 80, 80, QPixmap(":/image/Luffy.png"));

    //写图片到本项目文件夹中
    bool flag = pixmap->save("../day3_03_QPixmap/img.jpg");
    qDebug() << flag;//保存成功，返回true

    p.end();
}

Widget::~Widget()
{
    delete ui;
}
