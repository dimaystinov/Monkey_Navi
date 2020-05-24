#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QSqlDatabase>
class QModelIndex;
class QStandardItemModel;
namespace Ui {
class mainwindow2;
}
class mainwindow3;
class mainwindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow2(QWidget *parent = nullptr);
    bool setDatabases(QSqlDatabase **db);
    bool Init2();
    bool ShowTable(const QModelIndex &index);
    bool ChangeWindow(const QModelIndex &index);
    ~mainwindow2();

private:
    Ui::mainwindow2 *ui;
    QSqlDatabase *db;
    mainwindow3*main3;
    QStandardItemModel* model;
};

#endif // MAINWINDOW2_H
