#include <QApplication>
#include <QWidget>//窗口控件基类
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget w;
    w.setWindowTitle("主要看气质");//设置标题

    QPushButton b;
    b.setText("^_^");//给按钮设置内容"^_^"
    b.setParent(&w);//指定父对象
    b.move(100,100);//移动坐标

    QPushButton b1(&w);//通过构造函数传参
    b1.setText("abc");//默认坐标是(0,0)

    w.show();
    app.exec();
    return 0;
}
