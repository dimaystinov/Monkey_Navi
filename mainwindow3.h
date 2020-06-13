#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

#include <QMainWindow>
#include <QSqlDatabase>
namespace Ui {
class mainwindow3;
}
class mainwindow2;
class QStandardItemModel;
class mainwindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow3(QWidget *parent = nullptr);
    bool setDatabases(QSqlDatabase *db);
    bool setTables(QString table);
    bool setPreWindow(mainwindow2*main2);
    bool ShowDateWindow();
    ~mainwindow3();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_id_textEdited(const QString &arg1);

    void on_id_textChanged(const QString &arg1);

private:
    Ui::mainwindow3 *ui;
    mainwindow2 *main2;
    QSqlDatabase *db;
    QString table;
    QStandardItemModel *model;
};

#endif // MAINWINDOW3_H
