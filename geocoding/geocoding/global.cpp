#include "global.h"
#include "ui_global.h"
#include <QTimer>
#include <QTime>
#include <QThread>

global::global(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::global)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("color: rgb(200, 0, 0)");
    ui->label_3->setStyleSheet("color: rgb(200, 0, 0)");
    tmr = new QTimer();
    pp = new popwindow();
    tmr->setInterval(100);
    connect(tmr, SIGNAL(timeout()), this, SLOT(UpdateFrame()));
    tmr->start();
    db = new DbManager();
    db->load();
    tms[0] = db->tmsDB;
    hrm[0] = db->hrmDB;


    tms[1] = {
/*depot*/        {"Код отделения","Код товара отделения", "Адрес отделения", "Количество авто у отделения", "Количество товаров у отделения","Код авто у отделения"},
/*driver*/        {"Код водителя" , "Опыт вождения водителя","ФИО водителя","Здоровье водителя","Конец смены водителя","Начало смены водителя","Суммарный километраж водителя","Номер прав водителя"},
/*vehicle*/      {"Код авто","Номер авто","Расход топлива авто","Тип топлива авто","Статус авто","Вместимость авто","Пробег авто","Название авто"},
/*route*/         {"Код маршрута","Номер маршрута","Название маршрута","Начало маршрута","Конец маршрута","Время пути у маршрута","Код водителя маршрута","Код клиента маршрута","Код авто маршрута"},
/*good*/         {"Код товара","Название товара","Количество товара","Тип товара"},
/*client*/         {"Код клиента","ФИО клиента","Телефон клиента","Точка выдача у клиента","Адрес клиента"}
    };

    hrm[1] = {
       {"Код заказа","Номер заказа","Дата заказа"},
       {"Код образования","Тип образования","Название образования"},
       {"Код сотрудника","ФИО сотрудника","Пол сотрудника","ИНН_СНИЛС сотрудника","Код и серия паспорта сотрудника","Телефон сотрудника","Дата рождения сотрудника",
        "Адрес сотрудника","Код образования сотрудника"},
        {"Код компании","Название компании", "Описание компании"},
        {"Код сотрудника по бухгалтерии","Статус сотрудника по бухгалтерии","Дата выдача з/п сотрудника по бухгалтерии","Дата начала работы сотрудника по бухгалтерии",
         "Зарплата сотрудника по бухгалтерии","Премия сотрудника по бухгалтерии"},
        {"Код должности","Код сотрудника на должности","Опыт работы сотрудника на должности","Код компании сотрудника на должности","Название должности"}
    };
}

global::~global()
{
    delete ui;
}

void global::on_searchButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    QStringList tmsTablesNames, hrmTablesNames;
    QStringList tmsAttributeNames, hrmAttributeNames;
    QStringList tmsColumns, hrmColumns;
    QStringList headersTms, headersHrm, headersForeignTms,headersForeignHrm;
    QStringList tmp;

    for(int i=0;i<atribInfo.count();++i)
    {
        atribInfo[i]->setTableName();
        if(atribInfo[i]->getDbNumber()==1)
        {
            tmp.clear();
           // forTms.push_back(atribInfo[i]);
            tmsTablesNames << atribInfo[i]->getTableName();
            for(int f=0;f<atribInfo[i]->selectedColumns.count();++f)
            {
                QString str = atribInfo[i]->selectedColumns[f];
                tmp << str.split(".")[1];
            }

            tmsColumns << atribInfo[i]->selectedColumns;
            tmsAttributeNames << atribInfo[i]->getTableName()+"."+getNameForDb(atribInfo[i]->atrib,"tms") + " = '" + atribInfo[i]->info + "'";
            for(int g=0;g<tmp.count();++g)
                for(int k=0;k<tms[0].count();++k)
                    if(tms[0][k].contains(tmp[g]))
                    {
                            int p = tms[0][k].indexOf(tmp[g]);
                            headersTms << tms[1][k][p];
                        break;
                    }
        }
        else
        {
            tmp.clear();
           // forHrm.push_back(atribInfo[i]);
            hrmTablesNames << atribInfo[i]->getTableName();
            for(int f=0;f<atribInfo[i]->selectedColumns.count();++f)
            {
                QString str = atribInfo[i]->selectedColumns[f];
                tmp << str.split(".")[1];
            }
            hrmColumns << atribInfo[i]->selectedColumns;
            hrmAttributeNames << atribInfo[i]->getTableName()+"."+getNameForDb(atribInfo[i]->atrib,"hrm") + " = '" + atribInfo[i]->info + "'";
            for(int g=0;g<tmp.count();++g)
                for(int k=0;k<hrm[0].count();++k)
                    if(hrm[0][k].contains(tmp[g]))
                    {
                            int p = hrm[0][k].indexOf(tmp[g]);
                            headersHrm << hrm[1][k][p];
                        break;
                    }
        }
    }

// формирование строки для TMS
     QString tmsrequest = "SELECT * FROM ";

     QString toSelect = "";
     for(int i=0;i<tmsColumns.count();++i)
     {
         if(i!=tmsColumns.count()-1)
             toSelect += tmsColumns[i] + ",";
         else toSelect += tmsColumns[i];
     }

     tmsrequest.replace("*", toSelect);
     qDebug() << toSelect;
     tmsTablesNames.removeDuplicates();
     for(int i=0;i<tmsTablesNames.count();++i)
     {
             if(i!=tmsTablesNames.count()-1)
               tmsrequest += tmsTablesNames[i] + ",";
             else tmsrequest += tmsTablesNames[i] + " WHERE ";
     }

     for(int i=0;i<tmsAttributeNames.count();++i)
     {
             if(i!=tmsAttributeNames.count()-1)
               tmsrequest += tmsAttributeNames[i] + " AND ";
             else tmsrequest += tmsAttributeNames[i];
     }

// внешние ключи и поля для tms
       if(tmsrequest.contains("Client"))
       {
           tmsrequest.replace(tmsrequest.indexOf("Client"), 6, "Client, Depot");
           tmsrequest += "AND Client.id_delivery_point = Depot.id ";
       }

       if(tmsrequest.contains("Depot"))
       {
           tmsrequest.replace(tmsrequest.indexOf("Depot"),5, "Depot,Vehicle,Goods");
           tmsrequest += "AND Depot.id_vehicle = Vehicle.id AND Depot.id_goods = Goods.id ";
       }

       if(tmsrequest.contains("Route"))
       {
           tmsrequest.replace(tmsrequest.indexOf("Route"),5, "Route,Driver,Client,Vehicle");
           tmsrequest += "AND Route.id_driver = Driver.id AND Route.id_client = Client.id AND Route.id_vehicle = Vehicle.id ";
       }

       if(!tmsrequest.contains(";") && !tmsTablesNames.isEmpty())
           tmsrequest += ";";






// формирование строки для HRM
         QString hrmrequest = "SELECT * FROM ";
         toSelect = "";
         for(int i=0;i<hrmColumns.count();++i)
         {
             if(i!=hrmColumns.count()-1)
                 toSelect += hrmColumns[i] + ",";
             else toSelect += hrmColumns[i];
         }

         hrmrequest.replace("*", toSelect);
         qDebug() << toSelect;

         hrmTablesNames.removeDuplicates();
         for(int i=0;i<hrmTablesNames.count();++i)
         {
                 if(i!=hrmTablesNames.count()-1)
                   hrmrequest += hrmTablesNames[i] + ",";
                 else hrmrequest += hrmTablesNames[i] + " WHERE ";
         }

         for(int i=0;i<hrmAttributeNames.count();++i)
         {
                 if(i!=hrmAttributeNames.count()-1)
                   hrmrequest += hrmAttributeNames[i] + " AND ";
                 else hrmrequest += hrmAttributeNames[i];
         }

// внешние ключи и поля для hrm
         if(!hrmrequest.contains("Employee"))
             hrmrequest.replace(" FROM", " FROM Employee,");

        if(hrmrequest.contains("Education"))
             hrmrequest += "AND Employee.id_education=Education.id ";

         if(hrmrequest.contains("Time_schedule"))
             hrmrequest += "AND Employee.id = Time_schedule.id_employee ";

         if(hrmrequest.contains("Work_history"))
             hrmrequest += "AND Work_history.id_employee = Employee.id ";

         if(hrmrequest.contains("Company") && !hrmrequest.contains("Work_history"))
         {
             hrmrequest.replace(", Company" , ",Company,Work_history");
             hrmrequest += " AND Work_history.id_company = Company.id AND Work_history.id_employee=Employee.id ";
         }

         if(!hrmrequest.contains(";") && !hrmTablesNames.isEmpty())
             hrmrequest += ";";
            if(hrmTablesNames.isEmpty()) hrmrequest.replace("FROM Employee,", "Employee.name FROM Employee");
            else hrmrequest.replace("FROM Employee", ",Employee.name FROM Employee");






QTableWidget *tb2 = db->transformModel(db->getModel(pathHRM,hrmrequest,count));

    QStringList name;
    for(int i=0;i<tb2->rowCount();++i)
        for(int j=0;j<tb2->columnCount();++j)
        {
            if(tb2->item(i,j)->text().split(" ").count()==3)
                name << tb2->item(i,j)->text();
        }

    for(int i=0;i<name.count();++i)
        qDebug() << name[i];

    if(!tmsrequest.contains("Driver") && (!tmsrequest.contains("Depot") && !tmsrequest.contains("Client") && !tmsrequest.contains("Vehicle")) && !tmsrequest.contains("Goods"))
            tmsrequest.replace(" FROM ", " FROM Driver,");

    if(!tmsrequest.contains("WHERE") && name.count() > 0)
                tmsrequest.replace("Driver,;", "Driver WHERE ");
     else tmsrequest.replace(";", "AND (");
    for(int i=0;i<name.count();++i)
    {
        if(i!=name.count()-1)
            tmsrequest += "Driver.name = '" + name[i] + "' OR ";
        else tmsrequest +="Driver.name ='" + name[i] + "');";
    }





    QTableWidget *tb1 = db->transformModel(db->getModel(pathTMS,tmsrequest,count));

    QTableWidget *t = db->concatTables(tb1,tb2);

    ui->tableWidget->setRowCount(t->rowCount());
    ui->tableWidget->setColumnCount(t->columnCount());

    for(int i=0;i<ui->tableWidget->columnCount();++i)
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    for(int i=0;i<ui->tableWidget->rowCount();++i)
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

    QStringList headers;
    for(int i=0;i<headersForeignTms.count();++i)
        headers << headersForeignTms[i];

    for(int i=0;i<headersTms.count();++i)
        headers << headersTms[i];

    for(int i=0;i<headersForeignHrm.count();++i)
        headers << headersForeignHrm[i];

    for(int j=0;j<headersHrm.count();++j)
        headers << headersHrm[j];
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i=0;i<t->rowCount();++i)
        for(int j=0;j<t->columnCount();++j)
            ui->tableWidget->setItem(i,j, new QTableWidgetItem (t->item(i,j)->text()));

}

void global::paintEvent(QPaintEvent *)
{
        QImage img("/home/unfort/workspace/geocoding/4.jpeg"); // загружаем картинку


        QPainter painter(this); // определяем объект painter, который обеспечивает рисование


        painter.drawImage(0,0, img.scaled(this->size()));
}

void global::on_pushButton_clicked()
{
    pp->Rating();
}

void global::on_addAttButton_clicked()
{
    attribute *s = new attribute();
    s->Update(tms[1],hrm[1]);
    s->LoadList(tms,hrm);
    atribInfo.push_back(s);
}

void global::UpdateFrame()
{
    for(int i=0;i<atribInfo.count();++i)
        if(!atribInfo[i]->toDel)
    {
            atribInfo[i]->hide();
            delete atribInfo[i];
            atribInfo.removeAt(i);
    }
    else
            ui->widgetLayout->addWidget(atribInfo[i]);
}

QString global::getNameForDb(QString &id, QString db)
{
    int p=0, k=0;
    QString result;
    if(db == "tms")
    {
        for(int i=0; i<tms[1].count();++i)
        {
            if(tms[1][i].contains(id))
            {
                p = i;
                k = tms[1][i].indexOf(id);
                break;
            }
        }
        result = tms[0][p][k];
    }
    else
    {
        for(int i=0; i<hrm[1].count();++i)
        {
            if(hrm[1][i].contains(id))
            {
                p = i;
                k = hrm[1][i].indexOf(id);
                break;
            }
        }
        result = hrm[0][p][k];
    }
    return result;
}
