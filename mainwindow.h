#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts>
#include "Mydatabase.h"
#include "mychart.h"
#include "logindlg.h"
#include "ui_logindlg.h"
using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;


signals:
    void mySignal();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_add_clicked(bool checked);
    void setchart_ui(QChart*);
    void setdatabase_ui(QStandardItemModel*);


private slots:
    void on_pushButton_save_clicked();

private:
    MyDataBase *m_db;
    mychart *m_chart;

};
#endif // MAINWINDOW_H
