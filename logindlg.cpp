#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMovie>
#include <QLabel>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie("E:/0.work/MoneyCal/MoneyCal/basketball.gif");
    ui->label->setMovie(movie);
    movie->start();
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_pushButton_clicked()
{

}
