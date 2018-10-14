#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    CustomWidget *widget = new CustomWidget(this);

    CustomButton *cb = new CustomButton(widget);
    cb->setText("CustomButton");
    CustomButtonEx *cbex = new CustomButtonEx(widget);
    cbex->setText("CustomButtonEx");

    QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
    widgetLayout->addWidget(cb);
    widgetLayout->addWidget(cbex);

    this->setCentralWidget(widget);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "event is passed to MainWindow";
    event->ignore();
}

MainWindow::~MainWindow()
{

}
