#include "widget.h"
#include "ui_widget.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE","a");
    //设置数据库信息
    db.setDatabaseName("../day5_05_ModelView/database2");//数据库名称
    //打开数据库
    if(!db.open())
    {
        qDebug() << "Failed to open database2";
    }
    else
    {
        qDebug() << "succeed in opening database2";
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

    //设置模型，替代QSqlQuery
    model = new QSqlTableModel(this,db);

    //下面两句等价于 select * from student
    model->setTable("student");//指定数据库表
    model->select();//显示model里的数据

    //把model放在QTabelView组件中
    ui->tableView->setModel(model);

    //设置model的编辑策略，手动提交修改
    model->setEditStrategy(QSqlTableModel::QSqlTableModel::OnRowChange);
}

Widget::~Widget()
{
    delete ui;
}

//添加操作
void Widget::on_buttonAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();
    //获取表总行数
    int row = model->rowCount();
    //在row+1位置插入空记录，进行修改
    model->insertRecord(row, record);
}
//删除操作
void Widget::on_buttonDel_clicked()
{
    //获取选中的行
    int cur_row = ui->tableView->currentIndex().row();
    //删除该行
    model->removeRow(cur_row);
}

//提交动作
void Widget::on_buttonSure_clicked()
{
    model->submitAll();
}

//撤销修改
void Widget::on_buttonCancel_clicked()
{
    model->revertAll();
}

//查询操作
void Widget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);

    //指定查询时的条件
    model->setFilter(str);
    //显示结果
    model->select();

}

//返回主界面，即"显示全表"
void Widget::on_homeReturn_clicked()
{
    model->setTable("student");//重新关联表
    model->select();//这样才能再次显示整个表的内容
}
