#include "popwindow.h"
#include "ui_popwindow.h"
#include <QTableWidget>

popwindow::popwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popwindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
    QString tabStyle =
                       "QTabBar::tab:!selected {height: 50px; width: 160px;font-size:10pt;}"
                       "QTabBar::tab:selected {height: 50px; width: 160px;font-size:12pt;}";
    ui->tabWidget->setStyleSheet(tabStyle);
}

popwindow::~popwindow()
{
    delete ui;
}

void popwindow::Show(QString *mode)
{
    ui->tabWidget->clear();
    if(mode->contains("tms"))
    {
        count++;
        QTableWidget *final = db->transformModel(db->getModel(pathHRM,
                    "SELECT order_number, order_date FROM Internal_info;"
                    ,count));
        QTableWidget *new_data = db->transformModel((db->getModel(pathTMS,
                                                            "SELECT name, address, phone, name_good, quantity, address_depot FROM Client, Depot, Goods WHERE Client.id_delivery_point = Depot.id AND Client.id = Goods.id"
                                                            ,count)));

        QTableWidget *result = db->concatTables(final,new_data);

        result->setHorizontalHeaderLabels(QStringList() << "Номер заказа" << "Дата заказа" << "Имя клиента" << "Адрес" << "Телефон" << "Груз" << "Количество груза" << "Адрес выдачи");
        result->setFont(QFont("Calibre",12));
        for(int i=0;i<result->columnCount();++i)
            result->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->tabWidget->addTab(result,"Заказы");



        QTableWidget *t1 = db->transformModel(db->getModel(pathTMS,
                                                           "SELECT name, driving_experience, health,start_of_shift,end_of_shift, Mileage,license_number FROM Driver"
                                                           ,count));
        //QTableWidget *t2 = db->transformModel(db->getModel(pathHRM,
                                                     //      "SELECT sex,INN,SNILS,passport,phone,date_of_birth,address FROM Employee"
                                                       //    ,count));
      //  QTableWidget *t3 = db->transformModel(db->getModel(pathHRM,
                                            //               "SELECT Description FROM Education"
                                              //             ,count));

       // QTableWidget *tb = db->concatTables(t1,t2);
        QTableWidget *tb2 =t1; //db->concatTables(tb,t3);

         tb2->setHorizontalHeaderLabels(QStringList() << "Имя" << "Опыт вождения" << "Здоровье" << "Начало смены" << "Конец смены" << "Километраж" <<
                                           "Номер лицензии");// << "Пол" << "ИНН" << "СНИЛС" << "Серия и номер паспорта" << "Телефон" << "Дата рождения" << "Адрес" << "Образование");
        tb2->setFont(QFont("Calibre",12));
        for(int i=0;i<tb2->columnCount();++i)
            tb2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->tabWidget->addTab(tb2,"Водители");



        QTableWidget *tb3 = db->transformModel(db->getModel(pathTMS,
                                                           "SELECT route_number, route_name, start_point, finish_point, delivery_time, Driver.name, Client.name, Vehicle.car_name FROM Route, Driver,"
                                                           "Client, Vehicle WHERE Route.id_driver=Driver.id AND Route.id_client=Client.id AND Route.id_vehicle = Vehicle.id;"
                                                           ,count));

        tb3->setHorizontalHeaderLabels(QStringList() << "Имя маршрута" << "Номер маршрута" << "Начальная точка" << "Конечная точка" <<
                                       "Время доставки" << "Водитель" << "Клиент" << "Транспорт");

        tb3->setFont(QFont("Calibre",12));
        for(int i=0;i<tb3->columnCount();++i)
            tb3->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->tabWidget->addTab(tb3,"Маршруты");
    }

    else
    {
        count++;
        QTableWidget *tb1 = db->transformModel(db->getModel(pathHRM,
                                                          "SELECT Employee.name, name_position, Company.name, experience, salary, bonus, Education.Description,sex, passport, phone, address"
                                                          " FROM Employee, Company, Education, Work_history, Time_schedule "
                                                          "WHERE Education.id = Employee.id_education AND Time_schedule.id_employee=Employee.id AND"
                                                          " Employee.id=Work_history.id_employee AND Company.id = Work_history.id_company;",count));

        tb1->setHorizontalHeaderLabels(QStringList() << "Имя сотрудника" << "Должность" << "Компания" << "Опыт работы (лет)" <<
                                       "Зарплата" << "Премия" << "Образование" << "Пол" << "Серия/номер паспорта" << "Телефон" << "Адрес проживания");

        for(int i=0;i<tb1->columnCount();++i)
            tb1->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        tb1->setFont(QFont("Calibre",12));
        ui->tabWidget->addTab(tb1,"Сотрудники");

        QTableWidget *tb2 = db->transformModel(db->getModel(pathHRM,
                                                          "SELECT Employee.name, name_position, salary, bonus, payday_date, start_date, status_of_day, Company.name"
                                                          " FROM Employee, Company, Work_history, Time_schedule "
                                                          "WHERE Time_schedule.id_employee=Employee.id AND"
                                                          " Employee.id=Work_history.id_employee AND Company.id = Work_history.id_company;",count));

        tb2->setHorizontalHeaderLabels(QStringList() << "Имя сотрудника" << "Должность" << "Зарплата" << "Премия" <<
                                       "Дата выплаты" << "Начало работы" << "Статус" << "Компания");

        for(int i=0;i<tb2->columnCount();++i)
            tb2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        tb2->setFont(QFont("Calibre",12));
        ui->tabWidget->addTab(tb2,"Расписание");
    }
    show();
}

void popwindow::Rating()
{


    QTableWidget *name = db->transformModel(db->getModel(pathTMS,"SELECT name FROM Driver", count));
    QTableWidget *tb1 = new QTableWidget(name->rowCount(), 10);
    for(int i=0;i<name->rowCount();++i)
        for(int k=0;k<10;++k)
            tb1->setItem(i,k, new QTableWidgetItem(""));

    for(int i=0;i<name->rowCount();++i)
    {
        QTableWidget *t1 = db->transformModel(db->getModel(pathTMS,
                                                             "SELECT name, Mileage, health, start_of_shift, end_of_shift, license_number FROM Driver WHERE name = '" +
                                                           name->item(i,0)->text() + "'",count));
        QTableWidget *t2 = db->transformModel(db->getModel(pathHRM,
                                                              "SELECT sex, passport, phone, Education.Description FROM Employee, Education WHERE Education.id=Employee.id_education AND "
                                                           "Employee.name = '" + name->item(i,0)->text() + "'",count));
        QTableWidget *t = db->concatTables(t1,t2);

        for(int j=0;j<t->columnCount();++j)
           tb1->setItem(i,j, new QTableWidgetItem(t->item(0,j)->text()));
    }



 /*  QTableWidget *t1 = db->transformModel(db->getModel(pathTMS,
                                                    "SELECT name, Mileage, health, start_of_shift, end_of_shift, license_number FROM Driver" ,count));
    QTableWidget *t2 = db->transformModel(db->getModel(pathHRM,
                                                    "SELECT sex, passport, phone, Education.Description FROM Employee, Education WHERE Education.id=Employee.id_education" ,count));

    QTableWidget *tb1 = db->concatTables(t1,t2);*/

    tb1->sortItems(1,Qt::SortOrder(Qt::DescendingOrder));


    QTableWidget *final = new QTableWidget(tb1->rowCount(),tb1->columnCount()+1);
            for(int i=0;i<tb1->rowCount();++i)
            {
             for(int j=0;j<tb1->columnCount();++j)
                final->setItem(i,j, new QTableWidgetItem(tb1->item(i,j)->text()));

             QPushButton * btn = new QPushButton("+Премия");
             btn->setProperty("row", tb1->item(i,0)->text());
             QPalette pal = btn->palette();
             pal.setColor(QPalette::Button, QColor(Qt::blue));
             btn->setAutoFillBackground(true);
             btn->setPalette(pal);
             connect(btn, SIGNAL(clicked()), this, SLOT(MySlot()));
             final->setCellWidget(i,tb1->columnCount(),btn);
            }


    for(int i=0;i<tb1->columnCount();++i)
        final->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    final->setHorizontalHeaderLabels(QStringList() << "Имя" << "Километраж за месяц" << "Здоровье" << "Начало смены" << "Конец смены" << "Номер лицензии" <<
                                   "Пол" << "Паспорт" << "Телефон" << "Образование" << "Премия");
   // for(int i=0;i<tb1->rowCount();++i)
     //   tb1->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    final->setFont(QFont("Calibre",10));
    ui->tabWidget->addTab(final,"Рейтинг\nсотрудников");
    show();
}

void popwindow::on_pushButton_clicked()
{
    this->close();
}

void popwindow::MySlot()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
         if (!button) return;
         QVariant var = button->property("row");
         if (!var.isValid()) return;
       //  qDebug() << "row is " << var.toString();

    count++;
    db->Command(pathHRM,"UPDATE Time_schedule SET bonus ='" + QString::number(5000) + "' WHERE id_employee = (SELECT Employee.id FROM Employee WHERE Employee.name = '"
                + var.toString() + "');"
                , count);
    button->setEnabled(false);
}




















