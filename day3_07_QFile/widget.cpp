#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonRead_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                "open", "../", "TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        //创建文件对象，文件名和文件关联
        QFile file(path);
        QByteArray array;

        //打开文件，只读方式
        bool isOk = file.open(QIODevice::ReadOnly);
        if (isOk == true)
        {
            if (0)
            {
                //一次全部读完
                array = file.readAll();
            }
            else
            {
                //一行一行读
                while( file.atEnd() == false)//到结尾了吗
                {
                    array += file.readLine();
                }
            }
            //显示到编辑区
            ui->textEdit->setText(array);
        }
        //关闭文件
        file.close();

        //获取文件信息
        QFileInfo info(path);
        qDebug() << "文件路径：" << path;
        qDebug() << "文件名字：" << info.fileName();
        qDebug() << "文件后缀：" << info.suffix();
        qDebug() << "文件大小：" << info.size();
    }
}

void Widget::on_buttonWrite_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "save", "../", "TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        QFile file; //创建文件对象
        //关联文件名字
        file.setFileName(path);
        //打开文件，只写方式
        bool isOk = file.open(QIODevice::WriteOnly);
        if(isOk == true)
        {
            //获取编辑区内容
            QString str = ui->textEdit->toPlainText();//获取编辑区内容(纯文本)
            //写文件
            file.write(str.toUtf8());
        }
        file.close();
    }
}
