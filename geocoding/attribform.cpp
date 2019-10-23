#include "attribform.h"
#include "ui_attribform.h"

AttribForm::AttribForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttribForm)
{
    ui->setupUi(this);
}

AttribForm::AttribForm(QList<QString> list)
{
    for(int i=0;i<list.count();++i)
        ui->comboBox->addItem(list[i]);
}

AttribForm::~AttribForm()
{
    delete ui;
}
