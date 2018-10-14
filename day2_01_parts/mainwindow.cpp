#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCompleter>
#include <QStringList>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->myButton->setText("close the window!");
    connect(ui->myButton, &QPushButton::clicked, this, &MainWindow::close);

    //QLineEdit
    QString str = ui->lineEdit->text();
    qDebug() << str;
    ui->lineEdit->setText("12345678");
    ui->lineEdit->setTextMargins(15, 0, 0, 0);
    ui->lineEdit->setEchoMode(QLineEdit::Normal);//就是像密码似的看不见
    //设置提示符
    QStringList list;
    list << "hello" << "How are you" << "hehe";//创建字符串列表
    QCompleter *com = new QCompleter(list, this);//创建模型
    com->setCaseSensitivity(Qt::CaseInsensitive);//忽略大小写
    ui->lineEdit->setCompleter(com);

    //QLabel
    ui->labelText->setText("^_^");
    ui->labelImage->setPixmap(QPixmap(":/Leisure/Luffy.png"));
    ui->labelImage->setScaledContents(true);
    QMovie *myMovie = new QMovie(":/Leisure/mario.gif");//这个路径是从资源(qrc)→open in editor→选中需要文件右键复制路径
    ui->labelGif->setMovie(myMovie);
    myMovie->start();
    ui->labelGif->setScaledContents(true);
    ui->labelUrl->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    ui->labelUrl->setOpenExternalLinks(true);//有这句才能打开链接,即可使用默认浏览器打开链接

    //数码管
    ui->lcdNumber->display(123);

    //进度条
    ui->progressBar->setMinimum(0); //设置最小值
    ui->progressBar->setMaximum(200);//设置最大值
    ui->progressBar->setValue(100); //设置当前值
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_change_clicked()//你看他的命名:on_按钮名_信号  只要change按钮按下这个函数就自动执行
{
    static int i = 0;
    ui->stackedWidget->setCurrentIndex(++i % 4);
}
