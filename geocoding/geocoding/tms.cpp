#include "tms.h"
#include "ui_tms.h"
#include <cstdlib>
#include <mainwindow.h>

tms::tms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tms)
{
    ui->setupUi(this);

    ui->label_11->setStyleSheet("color: rgb(200, 0, 0)");
    pp = new popwindow();
    int check = 200;
    QTableWidget*tb =db->transformModel(db->getModel(pathTMS,"SELECT address_depot FROM Depot",check));
    QStringList str;
    pp = new popwindow();
    for(int i=0;i<tb->rowCount();++i)
        str << tb->item(i,0)->text();

    ui->comboBox_2->addItems(str);
    ui->comboBox_5->addItems(str);
    ui->comboBox_6->addItems(str);

    check = 205;
    QTableWidget*tb1 =db->transformModel(db->getModel(pathTMS,"SELECT car_name FROM Vehicle",check));
    QStringList str1;
    for(int i=0;i<tb1->rowCount();++i)
        str1 << tb1->item(i,0)->text();
    ui->comboBox->addItems(str1);
    UpdateFrame();

}

tms::~tms()
{
    delete ui;
}

void tms::on_addOrderButton_clicked()
{
     srand (time(NULL));
    if(!ui->lineEdit_43->text().isEmpty() && !ui->lineEdit_44->text().isEmpty() && !ui->lineEdit_45->text().isEmpty() && !ui->lineEdit_46->text().isEmpty()
             && !ui->lineEdit_48->text().isEmpty() && !ui->lineEdit_49->text().isEmpty()


   && db->Command(pathTMS,
                 "INSERT INTO Client (name, address, phone, id_delivery_point) VALUES ('"
                + ui->lineEdit_43->text() +
                "','"
                + ui->lineEdit_44->text() +
                "','"
                + ui->lineEdit_45->text() +
                "',( SELECT Depot.id FROM Depot where Depot.address_depot = '"
                + ui->comboBox_2->currentText()
                +"'));", count)

  &&  db->Command(pathHRM,
                "INSERT INTO Internal_Info (order_number, order_date) VALUES ('"+QString::number(rand()%100 + rand()%30 + rand()%10) +"','" + ui->lineEdit_49->text() + "');", count)



  &&  db->Command(pathTMS,
                "INSERT INTO Goods (id,name_good, quantity) VALUES ((SELECT Client.id FROM Client where Client.name ='"+ui->lineEdit_43->text()+"'),'"
                + ui->lineEdit_46->text() +
                " ',' " + ui->lineEdit_48->text() +
                "');",  count) )

{
        // основная информация о заказе из данных.
        QString startHtml = "<font color=\"Green\">";
        QString line = "Заказ №" + QString::number(count+1) + " был успешно добавлен.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit->appendHtml(line);
    }
    else
    {
        QString startHtml = "<font color=\"Red\">";
        QString line = "Заказ №" + QString::number(count+1) + " не был добавлен. Проверьте все данные выше.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit->appendHtml(line);
    }
    UpdateFrame();
}

void tms::on_addDriverButton_clicked()
{
    if(!ui->lineEdit_61->text().isEmpty() && /*!ui->lineEdit_62->text().isEmpty() && !ui->lineEdit_63->text().isEmpty() &&*/ !ui->lineEdit_64->text().isEmpty()
            &&/* !ui->lineEdit_65->text().isEmpty() &&*/ !ui->lineEdit_66->text().isEmpty() && /*!ui->lineEdit_67->text().isEmpty() &&*/ !ui->lineEdit_68->text().isEmpty() &&
            !ui->lineEdit_69->text().isEmpty() && !ui->lineEdit_70->text().isEmpty() &&/* !ui->lineEdit_72->text().isEmpty() && !ui->lineEdit_73->text().isEmpty() && */
            !ui->lineEdit_74->text().isEmpty() && /*!ui->lineEdit_75->text().isEmpty() &&*/

            db->Command(pathTMS,
                        "INSERT INTO Driver (name, driving_experience,health,end_of_shift,start_of_shift, Mileage,license_number) VALUES ('"
                        + ui->lineEdit_61->text() +"','" + ui->lineEdit_66->text() + "','" + ui->lineEdit_64->text() + "','" + ui->lineEdit_70->text() + "','"
                        + ui->lineEdit_69->text() + "','" + ui->lineEdit_68->text() +"','" + ui->lineEdit_74->text() + "');"
                        ,count)

          /*  &&
            db->Command(pathHRM,
                        "INSERT INTO Employee (name,sex,INN,SNILS,passport,phone,date_of_birth,address) VALUES ('"
                        + ui->lineEdit_61->text() + "','" + ui->lineEdit_65->text() + "','" + ui->lineEdit_72->text() + "','" + ui->lineEdit_75->text()
                        + "','" + ui->lineEdit_67->text() + "','" + ui->lineEdit_62->text() + "','" + ui->lineEdit_73->text() + "','"  + ui->lineEdit_63->text() + "');"
                        ,count)
            &&
            db->Command(pathHRM,
                        "INSERT INTO Education (Name, Description) VALUES ('"
                        + ui->lineEdit_71->text().left(ui->lineEdit_71->text().indexOf(',')) + "','" + ui->lineEdit_71->text() + "');"
                        ,count)*/
            )

    {
        // основная информация о водителе из данных.
        QString startHtml = "<font color=\"Green\">";
        QString line = "Водитель №" + QString::number(count+1) + " был успешно добавлен.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_2->appendHtml(line);
    }
    else
    {
        QString startHtml = "<font color=\"Red\">";
        QString line = "Водитель №" + QString::number(count+1) + " не был добавлен. Заполните все поля ввода данных.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_2->appendHtml(line);
    }
    UpdateFrame();
}

void tms::on_addRouteButton_clicked()
{
    if(!ui->lineEdit_87->text().isEmpty() && !ui->lineEdit_88->text().isEmpty() && !ui->lineEdit_90->text().isEmpty()
            && !ui->lineEdit_91->text().isEmpty() && !ui->lineEdit_92->text().isEmpty()


    && db->Command(pathTMS,
                   "INSERT INTO Route (route_number, route_name, start_point, finish_point, delivery_time, id_driver, id_client, id_vehicle) VALUES ('"
                   + ui->lineEdit_87->text() + "','" + ui->lineEdit_88->text() +"','" + ui->comboBox_5->currentText() + "','" +
                   ui->comboBox_6->currentText() + "','" + ui->lineEdit_92->text() + "', (SELECT Driver.id FROM Driver where Driver.name ='"+ui->comboBox_3->currentText() +
                   "'), (SELECT Client.id FROM Client where Client.name ='" + ui->comboBox_4->currentText() + "'),(SELECT Vehicle.id FROM Vehicle where Vehicle.car_name ='"+
                   ui->comboBox->currentText() + "'));"
                   ,count)

    )
    {
        // основная информация о маршруте из данных.
        QString startHtml = "<font color=\"Green\">";
        QString line = "Маршрут №" + QString::number(count+1) + " был успешно создан.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_3->appendHtml(line);
    }
    else
    {
        QString startHtml = "<font color=\"Red\">";
        QString line = "Маршрут №" + QString::number(count+1) + " не был создан. Заполните все поля ввода данных.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_3->appendHtml(line);
    }
}

void tms::on_tmsDataButton_clicked()
{
    pp->Show(new QString("tms"));
}

void tms::UpdateFrame()
{
    ui->comboBox_4->clear(); ui->comboBox_3->clear();

    update++;
    QTableWidget*tb1 =db->transformModel(db->getModel(pathTMS,"SELECT name FROM Client",update));
    QStringList str1;
    for(int i=0;i<tb1->rowCount();++i)
        str1 << tb1->item(i,0)->text();

    ui->comboBox_4->addItems(str1);

    update++;

    QTableWidget*tb2 =db->transformModel(db->getModel(pathTMS,"SELECT name FROM Driver",update));
    QStringList str2;
    for(int i=0;i<tb2->rowCount();++i)
        str2 << tb2->item(i,0)->text();

    ui->comboBox_3->addItems(str2);


}

void tms::paintEvent(QPaintEvent *)
{
        QImage img("/home/unfort/workspace/geocoding/1.jpeg"); // загружаем картинку


        QPainter painter(this); // определяем объект painter, который обеспечивает рисование


        painter.drawImage(0,0, img.scaled(this->size()));
}
