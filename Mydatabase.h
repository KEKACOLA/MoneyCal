#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMetaType>
#include <QStandardItemModel>


namespace Ui
{
    class MyDataBase;
}

class CustomDataType
{
public:
    //CustomDataType(int n=100):m_nValue(n){}
    //~CustomDataType(){}
private:
    //int m_nValue;
};

class MyDataBase : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyDataBase(QWidget *parent = nullptr);
    //~MyDataBase();
   // MyDataBase m;
    void open_database();
    void creat_table();
    void Update(QStringList& updatelist,int curRow);

signals:
    void database_slot(QStandardItemModel*);

private:
    //Ui::MyDataBase *m_db;
    bool IsTabExists(QString& Tabname);
    void GetAllData(QString& Tabname,int count);
    void DataDisplay(QStringList& list,int count);
    int IDCount(QString& Tabname);


};

//Q_DECLARE_METATYPE(CustomDataType)

#endif // MyDATABASE_H
