#include "widget.h"
#include "ui_widget.h"
#include <QPen>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    p.begin(this);//指定当前窗口为绘图设备,和p.end相配套

    //重新定义画笔，用于绘制轮廓线
    QPen pen;
    pen.setWidth(5); //设置线宽
    pen.setColor(Qt::red); //设置颜色
    pen.setStyle(Qt::DashLine); //设置风格
    //把画笔交给画家
    p.setPen(pen);

    //重新定义画刷，用于绘制填充色
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::Dense1Pattern);
    //把画刷交给画家
    p.setBrush(brush);

    //画背景图
    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/Luffy.png"));
    //Draws a line from (50, 50) to (150, 150).
    p.drawLine(50, 50, 150, 50);
    p.drawLine(50, 50, 50, 150);
    //画矩形 起点坐标(150,150) 宽100高50
    p.drawRect(150, 150, 100, 50);
    //画圆形 圆心(150,150) 水平半径50，竖直半径25
    p.drawEllipse(QPoint(150, 150), 50, 25);
    //画会移动的小船
    p.drawPixmap(x, 180, 80, 80, QPixmap(":/image/sunny.png"));

    p.end();
}

void Widget::on_pushButton_clicked()
{
    x += 20;
    if(x > this->width())
    {
        x = 0;
    }
    //刷新窗口,间接调用paintEvent()事件函数
    update();
}
