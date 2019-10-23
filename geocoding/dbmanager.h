#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QMap>
#include <QList>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTableView>
#include <QDebug>
#include <QMap>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QSqlError>

class DbManager
{
public:
    DbManager();
    void load();
    bool Command(QString path, QString Query, int &name);
    QTableWidget *transformModel(QSqlQueryModel *view)
    {
            int row = view->rowCount(); int column = view->columnCount();
            QTableWidget *table = new QTableWidget(row,column);
            for(int i=0;i<row;++i)
                for(int j=0;j<column;++j)
                    table->setItem(i,j, new QTableWidgetItem(view->data(view->index(i,j)).toString()));

        return table;

    }
    QTableWidget *concatTables(QTableWidget* final, QTableWidget* new_data)
    {
        int min_row;
        if(final->rowCount()>0 && new_data->rowCount()>0)
        {
            if(final->rowCount() < new_data->rowCount())
                min_row = final->rowCount();
            else min_row=new_data->rowCount();
        }
        else
        {
            if(final->rowCount()>0) min_row=final->rowCount();
            else min_row=new_data->rowCount();
        }


        QTableWidget *result = new QTableWidget(min_row, final->columnCount()+new_data->columnCount()-1);

        for(int i=0;i<final->rowCount();++i)
            for(int j=0;j<final->columnCount();++j)
                result->setItem(i,j,new QTableWidgetItem(final->item(i,j)->text()));

        for(int i=0;i<new_data->rowCount();++i)
            for(int j=0;j<new_data->columnCount()-1;++j)
                result->setItem(i,final->columnCount()+j, new QTableWidgetItem(new_data->item(i,j)->text()));

        return result;
    }

    //QStringList getHeaders(QString &tms, QString &hrm, QList<QList<QString> > tmsNames[], QList<QList<QString> > hrmNames[]);
    QSqlQueryModel* getModel(QString path, QString query, int &name);
    QTableWidget *getQuery(QString query);
    QList<QList<QString>> tmsDB;
    QList<QList<QString>> hrmDB;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
private:
    int count = 100;

};

#endif // DBMANAGER_H
