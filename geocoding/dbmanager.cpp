#include "dbmanager.h"
#include <QThread>

DbManager::DbManager()
{
}


QSqlQueryModel *DbManager::getModel(QString path, QString query, int &name)
{
    name++;
    name++;
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE",QString::number(name));
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
       // t->appendPlainText( "Error: connection with database failed");
    }
    else
    {
       // t->appendPlainText( "Database: connection ok");
    }

    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery qry(m_db);
    qry.prepare(query);
    qry.exec();
    model->setQuery(qry);
    qDebug() << query;
    m_db.close();
    name++;

    return model;
}

void DbManager::load()
{

//QList<QList<QString>> tmsDB;
// QList<QList<QString>> hrmDB;
//QMap <int, QList<QList<QString>>> db;


// Создание списка по базе TMS
    int check = 500000;
    QSqlQueryModel *start = getModel(pathTMS, "select name from sqlite_master where type='table' ", check);
    int round = start->rowCount();
    check = 500000 + 5;

    for(int i=1;i<round;++i)
    {
        QList<QString> atr;
        QSqlQueryModel *table = getModel(pathTMS, "PRAGMA TABLE_INFO(" +start->data(start->index(i,0)).toString()  + ")", check);

        for(int j=0; j<table->rowCount();++j)
        {
                atr.push_back(table->data(table->index(j,1)).toString());
               // qDebug() << table->data(table->index(j,1)).toString();
        }
        tmsDB.push_back(atr);
    }


// Создание списка по базе HRM
    check = 550000;
    QSqlQueryModel *start1 = getModel(pathHRM, "select name from sqlite_master where type='table' ", check);
    check = 550000 + 5;
    int round1 = start1->rowCount();

    for(int i=1;i<round1;++i)
    {
        QList<QString> atr;
        QSqlQueryModel *table1 = getModel(pathHRM, "PRAGMA TABLE_INFO(" +start1->data(start1->index(i,0)).toString()  + ")", check);
        for(int j=0; j<table1->rowCount();++j)
        {
                atr.push_back(table1->data(table1->index(j,1)).toString());
              // qDebug() << table1->data(table1->index(j,1)).toString();
        }
        hrmDB.push_back(atr);
    }
}

bool DbManager::Command(QString path, QString Query, int &name)
{
    name++;
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE",QString::number(name));
    m_db.setDatabaseName(path);
    bool success = false;

    if (!m_db.open())
      qDebug() << "Error: connection with database failed";

    QSqlQuery qry(m_db);
    qry.prepare(Query);
    success = qry.exec();
    qDebug() << Query;

       if(!success)
        return false;
    m_db.close();
    name++;
}

