#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MenuBar
    QMenuBar *mBar = this->menuBar();
    QMenu *pFile = mBar->addMenu("文件");
    QAction *pNew = pFile->addAction("新建");
    connect(pNew, &QAction::triggered,
            []()
            {
               qDebug() << "新建被按下";
            }
    );
    pFile->addSeparator();
    QAction *pOpen = pFile->addAction("open");
    //ToolBar
    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->addAction("haha");
    QPushButton *b = new QPushButton(this);
    b->setText("^_^");
    toolBar->addWidget(b);
    connect(b,&QPushButton::clicked,
            [=]()
            {
                b->setText("i am clicked!");
            }
            );
    //StatusBar
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("Next text file:");
    sBar->addWidget(label);
    //addwidget 从左往右添加
    sBar->addWidget(new QLabel("test",this));
    //addPermanentWidget从右往左添加,不会被临时消息遮挡
    sBar->addPermanentWidget(new QLabel("permanent",this));

    //add QDockWidget on MainWindow,the QTextEdit on QDockWidget
    QDockWidget *dock =new QDockWidget(this);
    //添加dock到主窗口指定区域
    this->addDockWidget(Qt::NoDockWidgetArea,dock);
    QTextEdit *textEdit = new QTextEdit(this);
    dock->setWidget(textEdit);
}

MainWindow::~MainWindow()
{
}
