#include "Mydatabase.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
//#include <QStandardItemModel>

MyDataBase::MyDataBase(QWidget *parent) : QMainWindow(parent)
{

}

void MyDataBase::open_database()
{
    QString tab = "q";
    QSqlDatabase database;
    int count = 0;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("admin");
        database.setPassword("123");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
        qDebug() << "database connect is  very nice!";
        //判断表格是否存在
        if(IsTabExists(tab))
        {
            qDebug() << "存在表格q ！";
            //取出数据显示
            count = IDCount(tab);
            GetAllData(tab,count);

        }
        else
        {
            creat_table();
            if(IsTabExists(tab))
            {
                qDebug() << "存在表格q2 ！";
                //取出数据显示
                count = IDCount(tab);
                GetAllData(tab,count);

            }
        }

    }
}

void MyDataBase::creat_table()
{
    QSqlQuery sql_query;
    //QString create_sql = "create table bill (id int primary key, MonthlyIncome varchar(30), AlipayExpenditure varchar(30), WechatExpenditure varchar(30), AlipayIncome varchar(30), WechatIncom varchar(30), MoneySaved varchar(30))";
    QString create_sql = "create table q (id int primary key, income varchar(10),AliEx varchar(10),WeEx varchar(10),AliIn varchar(10),WeIn varchar(10),saved varchar(10))";

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }

    //int max_id = 0;
    QString insert_sql = "insert into q values (?, ?, ?, ?, ?, ?, ?)";
    for(int i=0; i<12; i++)
    {
        insert_sql = "insert into q values (?, ?, ?, ?, ?, ?, ?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(i+1);
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted success!";
        }
    }

}

bool MyDataBase::IsTabExists(QString& Tabname)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.tables().contains(Tabname))
    {
        return true;
    }
    return false;
}

void MyDataBase::GetAllData(QString& Tabname,int count)
{
    QStringList list;
    QString select_all_sql = "select * from "+Tabname;
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString id = sql_query.value(0).toString();
            QString income = sql_query.value(1).toString();
            QString aliex = sql_query.value(2).toString();
            QString weex = sql_query.value(3).toString();
            QString aliin = sql_query.value(4).toString();
            QString wein = sql_query.value(5).toString();
            QString saved = sql_query.value(6).toString();

            //qDebug()<<QString("id:%1 income:%2 AliEx:%3 WeEx:%4 AliIn:%5 Wein:%6 saved:%7").arg(id).arg(income).arg(aliex).arg(weex).arg(aliin).arg(wein).arg(saved);
            list<<id<<income<<aliex<<weex<<aliin<<wein<<saved;
        }
        //qDebug()<<list;
        DataDisplay(list,count);
    }

}

void MyDataBase::DataDisplay(QStringList& list,int count)
{
    QStandardItemModel *model = new QStandardItemModel();
    /*设置列字段名*/
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,"当月收入");
    model->setHeaderData(1,Qt::Horizontal,"支付宝支出");
    model->setHeaderData(2,Qt::Horizontal,"微信支出");
    model->setHeaderData(3,Qt::Horizontal,"支付宝收入");
    model->setHeaderData(4,Qt::Horizontal,"微信收入");
    model->setHeaderData(5,Qt::Horizontal,"结余");

    /*设置行字段名*/
    model->setRowCount(12);
    QString str_month;
    for (int i=0; i<12; i++)
    {
        str_month = QString::number(i+1,10);
        model->setHeaderData(i,Qt::Vertical,str_month+"月");
    }

    /*设置数据*/
    QList<QStandardItem*> l;
    for(int month_index = 0; month_index<count; month_index++)
    {
        if(month_index!=0)
        {
            //清除list前7个元素
            for(int x=0; x<7; x++)
            {
                list.removeAt(0);
            }

            //qDebug()<<list;
        }

        for(int temp = 0; temp<6; temp++)
        {
            l<< new QStandardItem(list.at(temp+1));
            model->setItem(month_index, temp, l.at(temp));

        }
        //清空l
        l.clear();
    }
    emit database_slot(model);
}

int MyDataBase::IDCount(QString& Tabname)
{
    QSqlQuery sql_query;
    int count = 0;
    QString select_sql = "select id from "+Tabname;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
           // qDebug()<<QString("id:%1").arg(id);
            count = id;
        }
    }
    return count;
}

void MyDataBase::Update(QStringList& updatelist,int curRow)
{
    qDebug() << updatelist;
    QString update_sql = "update q set income = :income, AliEx = :AliEx, WeEx = :WeEx, AliIn = :AliIn, WeIn = :WeIn, saved = :saved where id = :id";
    //update_sql = "update q set income = "+ updatelist.at(0)+", AliEx = "+ updatelist.at(1)+" where id = :id";
    QSqlQuery  sql_query;
    sql_query.prepare(update_sql);
    sql_query.bindValue(":income",updatelist.at(0));
    sql_query.bindValue(":AliEx",updatelist.at(1));
    sql_query.bindValue(":WeEx",updatelist.at(2));
    sql_query.bindValue(":AliIn",updatelist.at(3));
    sql_query.bindValue(":WeIn",updatelist.at(4));
    sql_query.bindValue(":saved",updatelist.at(5));
    sql_query.bindValue(":id",curRow+1);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
        qDebug() << "updated!";
}
