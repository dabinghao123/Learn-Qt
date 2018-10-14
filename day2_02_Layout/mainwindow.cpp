#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image_label->setPixmap(QPixmap(":/image/Sunny.jpg"));
//    ui->image_label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
