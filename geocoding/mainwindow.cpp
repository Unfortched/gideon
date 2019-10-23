
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tm = new tms();
    hr = new hrm();
    gl = new global();
    mp = new map();

    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
    QString tabStyle =
                       "QTabBar::tab:!selected {height: 50px; width: 160px;font-size:10pt;}"
                       "QTabBar::tab:selected {height: 50px; width: 160px;font-size:12pt;}";
    ui->tabWidget->setStyleSheet(tabStyle);

    ui->tabWidget->setIconSize(QSize(50,50));
    QIcon qtms("/home/unfort/workspace/geocoding/tms.png");
    ui->tabWidget->addTab(tm, qtms, "TMS");
    QIcon qhrm("/home/unfort/workspace/geocoding/hrm.png");
    ui->tabWidget->addTab(hr,qhrm, "HRM");
    QIcon qglobal("/home/unfort/workspace/geocoding/global.png");
    ui->tabWidget->addTab(gl,qglobal, "Global");
    QIcon qmap("/home/unfort/workspace/geocoding/map.png");
    ui->tabWidget->addTab(mp,qmap, "Map");

}

MainWindow::~MainWindow()
{
    delete ui;
}
