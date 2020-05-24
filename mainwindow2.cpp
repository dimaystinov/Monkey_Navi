#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include"mainwindow3.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlQuery>
#include<QSqlRecord>
#include <QString>
#include <QDebug>
mainwindow2::mainwindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow2)
{
    ui->setupUi(this);

    this->setWindowTitle("请选择你的数据库和表格");
    this->model=nullptr;
    this->main3=nullptr;
}

bool mainwindow2::setDatabases(QSqlDatabase **db)
{
    this->db=*db;
    return true;
}

bool mainwindow2::Init2()
{
    QSqlQuery query(*(this->db));
    query.exec("show databases;");
    QStandardItemModel* model = new QStandardItemModel(this);
    QSqlRecord rec = query.record();
    int rowNum=0;
    model->setColumnCount(1);
    model->setRowCount(query.size());
    while(query.next())
    {
        model->setItem(rowNum++, 0, new  QStandardItem(query.value(0).toString()));
    }
    ui->DatabaseView->setModel(model);
    connect(ui->DatabaseView,static_cast<void (QTableView::*)(const QModelIndex &index)>(&QTableView::clicked)\
            ,this,&mainwindow2::ShowTable);
    connect(ui->TableView,static_cast<void (QTableView::*)(const QModelIndex &index)>(&QTableView::clicked)\
            ,this,&mainwindow2::ChangeWindow);
    return true;
}

bool mainwindow2::ShowTable(const QModelIndex &index)
{
    if(model!=nullptr)
    {
        model->clear();//释放内存
        delete model;
    }
    model = new QStandardItemModel(this);
    QString sql_changedatabase;
    sql_changedatabase=QString("use %1").arg(index.data().toString());
    db->exec(sql_changedatabase);
    db->setDatabaseName(index.data().toString());
    QSqlQuery query(*this->db);
    query.exec("show tables;");
    int rowNum=0;
    model->setColumnCount(1);
    model->setRowCount(query.size());
    while(query.next())
    {
        model->setItem(rowNum++, 0, new  QStandardItem(query.value(0).toString()));
    }
    ui->TableView->setModel(model);

    return true;
}

bool mainwindow2::ChangeWindow(const QModelIndex &index)
{
    if(main3!=nullptr)
    {
        delete main3;
    }
    main3=new mainwindow3;
    main3->setDatabases(this->db);
    main3->setTables(index.data().toString());
    main3->setPreWindow(this);
    this->hide();
    main3->show();
    main3->ShowDateWindow();
    return true;
}

mainwindow2::~mainwindow2()
{
    delete ui;
}
