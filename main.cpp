#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    LoginDlg login;
    //w.setCentralWidget(w);
    if(login.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
   // w.show();
    else
        return 0;
   // return a.exec();
}
