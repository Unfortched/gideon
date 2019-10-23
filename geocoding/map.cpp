#include "map.h"
#include "ui_map.h"
#include <QWebView>
#include <QFileInfo>
#include <qfile.h>
#include <QMainWindow>


map::map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
    tmr = new QTimer();
    tmr->setInterval(5000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(UpdateFrame()));
    tmr->start();

  /*  ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Откуда" << "Куда");
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "1" << "2");
    ui->tableWidget->setItem(0,0, new QTableWidgetItem(QString ("Москва")));
    ui->tableWidget->setItem(0,1, new QTableWidgetItem(QString ("Уфа")));
    ui->tableWidget->setItem(1,0, new QTableWidgetItem(QString ("Киев")));
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(QString ("Минск")));*/

    from = "Ufa1"; to = "Ufa2";

   UpdateFrame();

}

map::~map()
{
    delete ui;
}

void map::on_tableWidget_itemSelectionChanged()
{
}

void map::on_tableWidget_itemClicked(QTableWidgetItem *item)
{

    QFile file("/home/unfort/public/newproject/public_html/index.html");

    if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
        {
        QString text = QString::fromUtf8(file.readAll().constData());
        QString new_from = ui->tableWidget->item(item->row(),6)->text();
        QString new_to = ui->tableWidget->item(item->row(),7)->text();
        ui->tableWidget->setItem(2,0, new QTableWidgetItem(QString::number(item->row())));

        text.replace(from, new_from);
        text.replace(to, new_to);

       // ui->webView->settings()->setObjectCacheCapacities(0,0,0);
        ui->webView->setHtml(text, QUrl("http://newproject.loc/"));
        file.close();
    }
}

void map::paintEvent(QPaintEvent *)
{
    QImage img("/home/unfort/workspace/geocoding/5.jpeg"); // загружаем картинку


    QPainter painter(this); // определяем объект painter, который обеспечивает рисование


    painter.drawImage(0,0, img.scaled(this->size()));
}

void map::UpdateFrame()
{
    ui->tableWidget->clear();


    QTableWidget *t = db->transformModel(db->getModel(pathTMS,
                                                      "SELECT route_number, route_name, Driver.name, Client.name, Vehicle.car_name, Vehicle.car_number, start_point, finish_point FROM "
                                                      "Route, Driver, Client, Vehicle WHERE Route.id_driver = Driver.id AND Route.id_client = Client.id AND Route.id_vehicle = Vehicle.id"
                                                      ,count));


   int row = t->rowCount(); int column = t->columnCount();
   ui->tableWidget->setRowCount(row);
   ui->tableWidget->setColumnCount(column);
   for(int i=0;i<row;++i)
       for(int j=0;j<column;++j)
           ui->tableWidget->setItem(i,j, new QTableWidgetItem(t->item(i,j)->text()));

   for(int i=0;i<ui->tableWidget->columnCount();++i)
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Номер маршрута" << "Название маршрута" << "Имя водителя" << "Имя клиента" <<
                                               "Название машины" << "Номер машины" << "Откуда" << "Куда");


}
