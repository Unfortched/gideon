#ifndef HRM_H
#define HRM_H

#include <QWidget>
#include <popwindow.h>
#include <QPicture>
#include <QImage>
#include <QPainter>
#include <QStringBuilder>
#include <QTableWidget>
#include <dbmanager.h>
namespace Ui {
class hrm;
}

class hrm : public QWidget
{
    Q_OBJECT

public:
    explicit hrm(QWidget *parent = 0);
    ~hrm();


private slots:
    void on_addEmpButton_clicked();

    void on_addRuleButton_clicked();

    void on_hrmDataButton_clicked();

    void UpdateFrame();

    void on_comboBox_currentTextChanged(const QString &arg1);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::hrm *ui;
    popwindow *pp;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
    int count = 0;
    int update = 2000;
    int rewrite = 50;
    DbManager *db;
};

#endif // HRM_H
