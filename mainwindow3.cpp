#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include"mainwindow2.h"
#include<QDebug>
#include<QStandardItemModel>
#include<QSqlQuery>
#include<QSqlResult>
#include<QSqlRecord>
mainwindow3::mainwindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow3)
{
    ui->setupUi(this);
    model=nullptr;
}

mainwindow3::~mainwindow3()
{
    delete ui;
}

bool mainwindow3::setDatabases(QSqlDatabase *db)
{
    this->db=db;
    return true;
}

bool mainwindow3::setTables(QString table)
{
    this->table=table;
    return true;
}

bool mainwindow3::setPreWindow(mainwindow2 *main2)
{
    this->main2=main2;
    return true;
}

bool mainwindow3::ShowDateWindow()
{
    if(model!=nullptr)
    {
        model->clear();
        delete model;
    }
    model = new QStandardItemModel(this);
    QString sql_select=QString("select * from %1").arg(this->table);
  //  qDebug()<<sql_select;
    QSqlQuery query(*this->db);
    query.exec(sql_select);
    int rowNum=0;
    model->setColumnCount(query.record().count());
    model->setRowCount(query.size());
    while(query.next())
    {
        for(int i=0;i<model->columnCount();++i)
        {
            model->setItem(rowNum, i, new  QStandardItem(query.value(i).toString()));
        }
        rowNum++;
    }
    ui->MainView->setModel(model);
    return true;
}

void mainwindow3::on_pushButton_clicked()
{
    this->hide();
    this->main2->show();
    if(model)
    {
        delete model;
    }
}
