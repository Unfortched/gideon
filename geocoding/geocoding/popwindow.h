#ifndef POPWINDOW_H
#define POPWINDOW_H

#include <QWidget>
#include <dbmanager.h>

namespace Ui {
class popwindow;
}

class popwindow : public QWidget
{
    Q_OBJECT

public:
    explicit popwindow(QWidget *parent = 0);
    ~popwindow();
    void Show(QString *mode);
    void Rating();

private slots:
    void on_pushButton_clicked();

    void MySlot();
private:
    Ui::popwindow *ui;
    DbManager* db;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
    int count = 300;
    QString name;
};

#endif // POPWINDOW_H
