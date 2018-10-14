#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar = menuBar();
    QMenu *menu = mBar->addMenu("对话框");
    QAction *p1 = menu->addAction("模态对话框");// modal dialog
    connect(p1, &QAction::triggered,
            [=]()
            {
                QDialog dlg;
                dlg.exec();//一直等待用户处理,当你关闭后堵塞解除
                qDebug() << "modal dialog is closed";
            }
            );

    QAction *p2 = menu->addAction("非模态对话框");
    connect(p2, &QAction::triggered,
            [=]()
            {
                dlg.show();//void QWidget::show()
                qDebug() << "i am not modal dialog";
            }
            );

    QAction *p3 = menu->addAction("关于对话框");
    connect(p3, &QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"about","关于qt");//静态函数成员 父窗口 标题 内容
            }
            );

    QAction *p4 = menu->addAction("问题对话框");
    connect(p4, &QAction::triggered,
            [=]()
            {
                int ret = QMessageBox::question(this,"question","Are you ok？",
                    QMessageBox::Ok | QMessageBox::Cancel);//默认是Yes和No
                switch(ret)
                {
                    case QMessageBox::Ok:
                        qDebug() << "i am ok";
                        break;
                    case QMessageBox::Cancel:
                        qDebug() << "i am bad";
                        break;
                    default:
                        break;
                }
            }
            );

    QAction *p5 = menu->addAction("文件对话框");
    connect(p5, &QAction::triggered,
            [=]()
            {
                QString path = QFileDialog::getOpenFileName(//参数依次是父窗口、对话框标题、对话框打开时的默认目录、过滤器
                    this,"open","../","source(*.cpp *.h);;Text(*.txt);;all(*.*)"
                    );
                qDebug() << path;
            }
            );
}

MainWindow::~MainWindow()
{
}
