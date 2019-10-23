#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QTableWidgetItem>
#include <dbmanager.h>
#include <QTimer>

namespace Ui {
class map;
}

class map : public QWidget
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = 0);
    ~map();

private slots:
    void on_tableWidget_itemSelectionChanged();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void paintEvent(QPaintEvent *);

    void UpdateFrame();
private:
    Ui::map *ui;
    QString from,to;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
    DbManager *db;
    QTimer *tmr;
    int count = 0;
};

#endif // MAP_H
