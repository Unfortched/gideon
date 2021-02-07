#include "widget.h"
#include "ui_widget.h"
#include "projectscene.h"
#include <math.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    prj = new ProjectScene(this);
    cmp = new ComplexScene(this);
    ui->graphicsView->setScene(prj);
    ui->graphicsView_2->setScene(cmp);
    //prj->setSceneRect(0,0,ui->graphicsView->width() - 5,ui->graphicsView->height() - 5);
    ui->graphicsView->centerOn(0,0);
    ui->graphicsView->fitInView(0,0,
                                ui->graphicsView->width()/100 - 100, ui->graphicsView->height()/100 - 100, Qt::KeepAspectRatio);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->X->setMaximum(100); ui->X->setMinimum(-100); ui->X->setValue(0);
    ui->Y->setMaximum(100); ui->Y->setMinimum(-100); ui->Y->setValue(0);
    ui->Z->setMaximum(100); ui->Z->setMinimum(-100); ui->Z->setValue(0);
    ui->alpha->setMaximum(628); ui->alpha->setMinimum(0); ui->alpha->setValue(0);
    ui->beta->setMaximum(628-157); ui->beta->setMinimum(-157); ui->beta->setValue(-157);
    ui->gamma->setMaximum(628+65); ui->gamma->setMinimum(65); ui->gamma->setValue(65);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_X_valueChanged(int value)
{
    prj->clear();
    cmp->clear();
    ui->XText->setText("X: " + QString::number(value));

    prj->InputCoord(value,0,0);
    cmp->Input(value,0,0);
}

void Widget::on_Y_valueChanged(int value)
{
    prj->clear();
    cmp->clear();
    ui->YText->setText("Y: " + QString::number(value));

    prj->InputCoord(0,-value,0);
    cmp->Input(0,-value,0);
}

void Widget::on_Z_valueChanged(int value)
{
    prj->clear();
    cmp->clear();
    ui->ZText->setText("Z: " + QString::number(value));


    prj->InputCoord(0,0,value);
    cmp->Input(0,0,value);
}

void Widget::on_alpha_valueChanged(int value)
{
    prj->clear();
    ui->AText->setText("alpha: " + QString::number(value*180/314));
    prj->InputAngle((double)value/100,0,0);
}

void Widget::on_beta_valueChanged(int value)
{
    prj->clear();

    ui->BText->setText("beta: " + QString::number((value+157)*180/314));
    prj->InputAngle(0,(double)value/100,0);
}

void Widget::on_gamma_valueChanged(int value)
{
    prj->clear();

    ui->GText->setText("gamma: " + QString::number((value-65)*180/314));
    prj->InputAngle(0,0,(double)value/100);
}
