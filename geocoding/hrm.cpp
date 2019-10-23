#include "hrm.h"
#include "ui_hrm.h"

hrm::hrm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hrm)
{
    ui->setupUi(this);
    //ui->functionChooseBox->addItems( QStringList() << "Обычная функция" << "U-образная функция" << "V-образная функция" <<  "Уровневая функция" << "V-образная функция с порогами безразличия" << "Функция Гаусса");
    ui->label_11->setStyleSheet("color: rgb(200, 0, 0)");
    pp = new popwindow();
    int check = 250;
    QTableWidget*tb =db->transformModel(db->getModel(pathHRM,"SELECT name FROM Employee",check));
    QStringList str;
    pp = new popwindow();
    for(int i=0;i<tb->rowCount();++i)
        str << tb->item(i,0)->text();
    ui->comboBox->addItems(str);

}

hrm::~hrm()
{
    delete ui;
}

void hrm::on_addEmpButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && !ui->lineEdit_4->text().isEmpty()
            && !ui->lineEdit_5->text().isEmpty() && !ui->lineEdit_6->text().isEmpty() && !ui->lineEdit_13->text().isEmpty() && !ui->lineEdit_14->text().isEmpty()
            && !ui->lineEdit_19->text().isEmpty() && !ui->lineEdit_20->text().isEmpty() &&  !ui->lineEdit_22->text().isEmpty()

       && db->Command(pathHRM,
                      "INSERT INTO Education (Name, Description) VALUES ('" +ui->lineEdit_3->text().left(ui->lineEdit_3->text().indexOf(' ')) +"','" +
                      ui->lineEdit_3->text() + "');"
                      ,count)
       && db->Command(pathHRM,
                      "INSERT INTO Employee (name,sex,INN_SNILS,passport,phone,date_of_birth,address,id_education) VALUES('" +
                      ui->lineEdit->text() + "','" + ui->lineEdit_6->text() + "','" + ui->lineEdit_5->text() +"','" + ui->lineEdit_22->text() + "','"
                      +ui->lineEdit_4->text() + "','" + ui->lineEdit_14->text() + "','" + ui->lineEdit_13->text() + "', (SELECT Education.id FROM Education WHERE" +
                      " Education.Description = '" + ui->lineEdit_3->text() + "'));"
                      ,count)

       && db->Command(pathHRM,
                      "INSERT INTO Company (name) VALUES ('" + ui->lineEdit_19->text() + "');"
                      ,count)

       && db->Command(pathHRM,
                      "INSERT INTO Work_history (id_employee, experience, id_company,name_position) VALUES ("
                       "(SELECT Employee.id FROM Employee WHERE Employee.name ='" + ui->lineEdit->text() + "'),'" +
                      ui->lineEdit_20->text() + "',(SELECT Company.id FROM Company WHERE Company.name ='" +  ui->lineEdit_19->text() +"'),'" +
                      ui->lineEdit_2->text() + "');"
                      ,count)
     )
    {

        // основная информация о Работнике из данных.
        QString startHtml = "<font color=\"Green\">";
        QString line = "Работник №" + QString::number(count+1) + " был успешно добавлен.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit->appendHtml(line);
    }
    else
    {
        QString startHtml = "<font color=\"Red\">";
        QString line = "Работник №" + QString::number(count+1) + " не был добавлен. Заполните все поля ввода данных.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit->appendHtml(line);
    }
    UpdateFrame();
}

void hrm::on_addRuleButton_clicked()
{

    if(!ui->lineEdit_8->text().isEmpty() && !ui->lineEdit_15->text().isEmpty() && !ui->lineEdit_16->text().isEmpty() && !ui->lineEdit_7->text().isEmpty()


            && db->Command(pathHRM,
                           "INSERT INTO Time_schedule (id_employee, status_of_day,payday_date,start_date,salary, bonus) VALUES ((SELECT Employee.id FROM Employee WHERE"
                           " Employee.name = '" + ui->comboBox->currentText() + "'),'" + ui->lineEdit_8->text() + "','" + ui->lineEdit_15->text() + "','" +
                           ui->lineEdit_16->text() + "','" + ui->lineEdit_7->text() +"','0');"
                           ,count)
            )
    {

        // основная информация о правиле из данных.
        QString startHtml = "<font color=\"Green\">";
        QString line = "Правило №" + QString::number(count+1) + " было успешно создано.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_2->appendHtml(line);
    }
    else
    {
        QString startHtml = "<font color=\"Red\">";
        QString line = "Правило №" + QString::number(count+1) + " не было создано. Заполните все поля ввода данных.";
        QString endHtml = "</font><br>";
        line = startHtml % line % endHtml;
        ui->plainTextEdit_2->appendHtml(line);
    }
}

void hrm::on_hrmDataButton_clicked()
{
    pp->Show(new QString("hrm"));
}

void hrm::UpdateFrame()
{
    ui->comboBox->clear();

    update++;
    QTableWidget*tb1 =db->transformModel(db->getModel(pathHRM,"SELECT name FROM Employee",update));
    QStringList str1;
    for(int i=0;i<tb1->rowCount();++i)
        str1 << tb1->item(i,0)->text();

    ui->comboBox->addItems(str1);

}

void hrm::paintEvent(QPaintEvent *)
{
        QImage img("/home/unfort/workspace/geocoding/3.jpeg"); // загружаем картинку


        QPainter painter(this); // определяем объект painter, который обеспечивает рисование


        painter.drawImage(0,0, img.scaled(this->size()));
}

void hrm::on_comboBox_currentTextChanged(const QString &arg1)
{

 /*      QTableWidget *t =  db->transformModel(db->getModel(pathHRM,
                                                          "SELECT status_of_day FROM Time_schedule, Employee WHERE id_employee= Employee.id AND Employee.name='" + arg1 + "';"
                                                          ,rewrite));
       ui->label_9->setText(t->item(0,0)->text());
       if(label == "Выходной")
           ui->label_9->setStyleSheet("color: rgb(0, 255, 0);");
       else ui->label_9->setStyleSheet("color: rgb(255, 0, 0);");
*/
}
