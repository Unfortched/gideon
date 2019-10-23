#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tms.h>
#include <hrm.h>
#include <global.h>
#include <map.h>
#include <popwindow.h>
#include <dbmanager.h>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    tms *tm;
    hrm *hr;
    global *gl;
    map *mp;
    popwindow *pp;
};

#endif // MAINWINDOW_H
