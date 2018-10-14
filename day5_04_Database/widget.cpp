#include "widget.h"
#include "ui_widget.h"
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印可使用数据库驱动
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();
    //0:QSQLITE   1:QMYSQL
    int flag = 0;

    if (flag == 0)
    {
        //使用 数据库驱动类型 添加数据库连接,给数据库连接起名为"a"
        //用于区分不同的数据库连接(用"a"而不是"QSQLITE"、"QMYSQL"区分)
        db = QSqlDatabase::addDatabase("QSQLITE","a");
        //设置数据库信息
        db.setDatabaseName("../day5_04_Database/database1");//数据库名称
    }
    else
    {
        //添加数据库连接
        db = QSqlDatabase::addDatabase("QMYSQL","a");
        //设置数据库信息
        db.setHostName("localhost"); //数据库服务器IP
        db.setUserName("root"); //数据库用户名
        db.setPassword("123456"); //密码
        db.setDatabaseName("database1"); //数据库名称
    }
    //打开数据库
    if(!db.open())
    {
        qDebug() << "Failed to open database1";
    }
    else
    {
        qDebug() << "succeed in opening database1";
    }

    //以下执行相关sql语句
    QSqlQuery query(db);

    //新建student表，id设置为主键
    query.exec("create table student(id int primary key, name varchar(255), age int, score int);");

    //向表中插入4条记录
    query.exec("insert into student(id,name,age,score) values(1,'xiaogang',15,91)");
    query.exec("insert into student values(2,'xiaoming',14,93)");
    query.exec("insert into student values(3,'xiaohong',15,87)");
    query.exec("insert into student values(6,'liuliu',16,95)");

    //查找表中id >=2 的记录的id项和name项的值
    query.exec("select id,name from student where id >= 2");

    //query.next()指向查找到的第一条记录，然后每次后移一条记录
    while(query.next())
    {
        //query.value(0)是id的值，将其转换为int型
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();
        //输出两个值
        qDebug() << value0 << value1 ;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonDel_clicked()
{
    QString name = ui->lineEdit->text();
    QString sql = QString("delete from student where name = '%1'").arg(name);
    //开启一个事务
    QSqlDatabase::database("a").transaction();
    QSqlQuery query(db);//静态对象
    query.exec(sql);
}

void Widget::on_buttonSure_clicked()
{
    //确定删除，且结束事务
    QSqlDatabase::database("a").commit();
}

void Widget::on_buttonCancel_clicked()
{
    //撤销删除，且结束事务
     QSqlDatabase::database("a").rollback();
}
