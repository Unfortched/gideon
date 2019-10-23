#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QPicture>
#include <QImage>
#include <QPainter>
#include <popwindow.h>
#include <attribute.h>
#include <QTimer>
#include <QTime>
#include <dbmanager.h>
#include <QMap>
#include <QStringList>


namespace Ui {
class global;
}

class global : public QWidget
{
    Q_OBJECT

public:
    explicit global(QWidget *parent = 0);
    ~global();

private slots:
    void on_searchButton_clicked();
    void on_pushButton_clicked();
    void on_addAttButton_clicked();
    void UpdateFrame();
    QString getNameForDb(QString &id, QString db);

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::global *ui;
    popwindow *pp;
    QTimer *tmr;
    QList<attribute*> atribInfo;
    int count = 15000;
    QList<QList<QString>> tms[2];
    QList<QList<QString>> hrm[2];
    DbManager* db;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
};

#endif // GLOBAL_H
