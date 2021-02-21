#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>


//#include "Mydatabase.h"
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //LoginDlg login;
    //login.ui->setupUi();
    ui->setupUi(this);

    m_db = new MyDataBase();
    connect(m_db,SIGNAL(database_slot(QStandardItemModel*)),this,SLOT(setdatabase_ui(QStandardItemModel*)));
    m_db->open_database();

    m_chart = new mychart();
    connect(m_chart,SIGNAL(chartslot(QChart*)),this,SLOT(setchart_ui(QChart*)));
    m_chart->chartdisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString expendStr = ui->textEdit->toPlainText();
    QString incomeStr = ui->textEdit_2->toPlainText();
    QString resultStr;
    double expendNum,incomeNum,resultNum;
    expendNum = expendStr.toDouble();
    incomeNum = incomeStr.toDouble();
    resultNum = expendNum + incomeNum;
    resultStr =  QString::number(resultNum,10,2);   //QString::number(resultNum,基底，精度)
    ui->textEdit_3->setText(resultStr);
}

void MainWindow::on_pushButton_add_clicked(bool checked)
{
    qDebug("Test:%d",checked);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);//点击单元格两次可编辑
}
void MainWindow::setchart_ui(QChart * ch)
{
    ui->widget->setChart(ch);
    qDebug() << "chart slot!";
}

void MainWindow::setdatabase_ui(QStandardItemModel* model)
{
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableView->setModel(model);
    qDebug() << "database slot!";
}


void MainWindow::on_pushButton_save_clicked()
{
    QAbstractItemModel *mod = ui->tableView->model();
    QTableView* tableview = ui->tableView;
    QStringList updateList;
    //获取tableview选中的行
    int curRow = tableview->currentIndex().row();//从0开始
    //获取选中行所有列的数据
    QModelIndex indextemp = mod->index(curRow,1);
    for(int i =0; i<6; i++)
    {
        indextemp = mod->index(curRow,i);
        updateList << mod->data(indextemp).toString();
    }
    //qDebug() << updateList;

    //更新数据库
    m_db->Update(updateList,curRow);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
