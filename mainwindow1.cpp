#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include <QMessageBox>
#include"mainwindow2.h"
#include<QDebug>
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    this->setWindowTitle("WelCome NaviMonkey");
    QSettings setting(QCoreApplication::applicationDirPath()+"/Mysql.ini", QSettings::IniFormat);
    setting.beginGroup("set_jojo");
    ui->address->setText( setting.value("address").toString());
    ui->user->setText(setting.value("user").toString());
    ui->passwd->setText(setting.value("passwd").toString());
    ui->database->setText(setting.value("database").toString());
    setting.endGroup();
}

bool MainWindow1::Init()
{
    QString address=ui->address->text();
    QString user=ui->user->text();
    QString pass=ui->passwd->text();
    QString database=ui->database->text();
   // this->db=new QSqlDatabase;
    this->db=new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    db->setHostName(address);
    db->setDatabaseName(database);
    db->setUserName(user);
    db->setPassword(pass);
    bool ok=db->open();
    if(ok)
    {
        QSettings iniFile(QCoreApplication::applicationDirPath()+"/Mysql.ini", QSettings::IniFormat);
        iniFile.beginGroup("set_jojo");
        iniFile.setValue("address",address);
        iniFile.setValue("user",user);
        iniFile.setValue("passwd",pass);
        iniFile.setValue("database",database);
        iniFile.endGroup();
    }
    return ok;
}

MainWindow1::~MainWindow1()
{
    delete ui;
}


void MainWindow1::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Good Bye","再见Have a Good Day");
    exit(0);
}

void MainWindow1::on_pushButton_clicked()
{
    if(Init())
       {
        QMessageBox::information(this,"提示","连接成功，连接到Mysql",0);
        this->hide();
      //  qDebug()<<this->db->databaseName();
        mainwindow2*main2=new mainwindow2;
        main2->setDatabases(&(this->db));
        main2->Init2();
        main2->show();
       }
       else {
            QMessageBox::information(this,"提示","连接失败，检查输入信息，和数据库配置",0);
       }
}

void MainWindow1::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"提示","暂时没制作",0);
}
