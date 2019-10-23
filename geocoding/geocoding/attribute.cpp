#include "attribute.h"
#include "ui_attribute.h"

attribute::attribute(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::attribute)
{
    ui->setupUi(this);
    db = new DbManager();

    if(ui->comboBox->currentText() == "")
        clearLayout();
}

attribute::~attribute()
{
    delete ui;
}

void attribute::on_comboBox_currentTextChanged(const QString &arg1)
{
    atrib = arg1;
    setTableName();
    selectedColumns.clear();

    clearLayout();


    QString path;
    if (dbChoose == 1)
        path = db->pathTMS;
    else path = db->pathHRM;
    QTableWidget *tb = db->transformModel(db->getModel(path, "PRAGMA TABLE_INFO(" + getTableName()  + ")", count));
    for(int i=0;i<tb->rowCount();++i)
    {
        QCheckBox *box;
        if(dbChoose==1)
            box = new QCheckBox(getNameToText(getTableName() + "." + tb->item(i,1)->text(), "tms", 0, 1));
        else box = new QCheckBox(getNameToText(getTableName() + "." + tb->item(i,1)->text(), "hrm", 0, 1));

        connect(box, SIGNAL(stateChanged(int)), this, SLOT(getNameByClick(int)));
        ui->horizontalLayout_3->addWidget(box);
    }

}

void attribute::on_lineEdit_textChanged(const QString &arg1)
{
    info = arg1;
}

void attribute::on_pushButton_clicked()
{
    toDel = false;
}

void attribute::getNameByClick(int state)
{
    QCheckBox* box = qobject_cast<QCheckBox*>(sender());
         if (!box) return;
     QVariant var = box->property("text");
     if(state == Qt::Checked)
     {
         if(dbChoose==1)
            selectedColumns << getNameToText(box->property("text").toString(),"tms",1,0);
         else selectedColumns << getNameToText(box->property("text").toString(),"hrm",1,0);
     }
     if(state == Qt::Unchecked)
     {
         if(dbChoose==1)
            selectedColumns.removeOne(getNameToText(box->property("text").toString(),"tms",1,0));
         else selectedColumns.removeOne(getNameToText(box->property("text").toString(),"hrm",1,0));
     }
     qDebug() << selectedColumns;
     if (!var.isValid()) return;
}

int attribute::getDbNumber()
{
    return dbChoose;
}

QString attribute::getTableName()
{
    return tableName;
}

void attribute::LoadList(QList<QList<QString> > forTms[], QList<QList<QString>> forHrm[])
{
    tms[0] = forTms[0]; tms[1] = forTms[1];
    hrm[0] = forHrm[0]; hrm[1] = forHrm[1];

    QStringList tmsNames = {"Depot","Driver","Vehicle","Route","Goods","Client"};
    QStringList hrmNames = {"Internal_info","Education", "Employee","Company","Time_schedule","Work_history"};


    for(int j=0;j<tms[0].count();++j)
            for(int p=0;p<tms[0][j].count();++p)
                tms[0][j][p] = tmsNames[j] + "." + tms[0][j][p];


        for(int j=0;j<hrm[0].count();++j)
            for(int p=0;p<hrm[0][j].count();++p)
                hrm[0][j][p] = hrmNames[j] + "." + hrm[0][j][p];
}

void attribute::setTableName()
{
        QStringList lst = atrib.split(" ");
        if(lst.back()=="авто")
        {   dbChoose = 1;
            tableName = "Vehicle";

        }

        if(lst.back()=="отделения")
        {   dbChoose = 1;
            tableName = "Depot";
        }

        if(lst.back()== "водителя")
        {   dbChoose = 1;
            tableName = "Driver";
        }

        if(lst.back()=="маршрута")
        {   dbChoose = 1;
           tableName = "Route";
        }

        if(lst.back()=="товара")
        {   dbChoose = 1;
            tableName = "Goods";
        }

        if(lst.back()=="клиента")
        {   dbChoose = 1;
            tableName = "Client";
        }

        if(lst.back()=="заказа")
        {   dbChoose = 2;
           tableName = "Internal_info";
        }

        if(lst.back()=="образования")
        {   dbChoose = 2;
            tableName = "Education";
        }

        if(lst.back()=="сотрудника")
        {   dbChoose = 2;
            tableName = "Employee";
        }

        if(lst.back()=="компании")
        {   dbChoose = 2;
            tableName = "Company";
        }

        if(lst.back()=="бухгалтерии")
        {   dbChoose = 2;
            tableName = "Time_schedule";
        }

        if(lst.back()=="должности")
        {   dbChoose = 2;
            tableName = "Work_history";
        }



         /*  switch(lst.back())
           {
            case "авто" :
                return "Vehicle";
                break;
            case "отделения":
                return "Depot";
                break;
            case "водителя" :
                return "Driver";
                break;
            case "маршрута":
                return "Route" ;
                break;
            case "товара" :
                return "Goods";
                break;
            case "клиента" :
                return "Client";
                break;
           case "заказа" :
               return "Internal_info";
               break;
           case "образования" :
               return "Education";
               break;
           case "сотрудника" :
               return "Employee";
               break;
           case "компании" :
               return "Company";
               break;
           case "бухгалтерии" :
               return "Time_schedule";
               break;
           case "должности" :
               return "Work_history";
               break;
            default :
                 return "";
           }*/
}

void attribute::Update(QList<QList<QString> > s, QList<QList<QString> > n)

{
    ui->comboBox->clear();
    ui->comboBox->addItem("");
    for(int i=0;i<s.count();++i)
        for(int j=0;j<s[i].count();++j)
            ui->comboBox->addItem(s[i][j]);

    for(int i=0;i<n.count();++i)
        for(int j=0;j<n[i].count();++j)
            ui->comboBox->addItem(n[i][j]);
}

QString attribute::getNameToText(QString id, QString db, int startListNumber, int finishListNumber)
{
   int p=0, k=0;
    QString result;
    if(db == "tms")
    {
        for(int i=0; i<tms[startListNumber].count();++i)
        {
            if(tms[startListNumber][i].contains(id))
            {
                p = i;
                k = tms[startListNumber][i].indexOf(id);
                break;
            }
        }
        result = tms[finishListNumber][p][k];
    }
    else
    {
        for(int i=0; i<hrm[startListNumber].count();++i)
        {
            if(hrm[startListNumber][i].contains(id))
            {
                p = i;
                k = hrm[startListNumber][i].indexOf(id);
                break;
            }
        }
        result = hrm[finishListNumber][p][k];
    }
    return result;
}

void attribute::clearLayout()
{
    QLayoutItem *child;
      while ((child = ui->horizontalLayout_3->takeAt(0)) != 0)
      {
          delete child->widget();
          delete child;
      }
}
