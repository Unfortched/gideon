#ifndef TMS_H
#define TMS_H

#include <QWidget>
#include <popwindow.h>
#include <QPicture>
#include <QImage>
#include <QPainter>
#include <QStringBuilder>
#include <dbmanager.h>
#include <QThread>
#include <QTimer>

namespace Ui {
class tms;
}

class tms : public QWidget
{
    Q_OBJECT

public:
    explicit tms(QWidget *parent = 0);
    ~tms();

private slots:
    void on_addOrderButton_clicked();

    void on_addDriverButton_clicked();

    void on_addRouteButton_clicked();

    void on_tmsDataButton_clicked();

    void UpdateFrame();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::tms *ui;
    popwindow *pp;
    QString pathTMS = "/home/unfort/workspace/geocoding/tms.db";
    QString pathHRM = "/home/unfort/workspace/geocoding/hrm.db";
    DbManager *db;
    int count = 0;
    int update = 1000;
    QTimer *tmr;
};

#endif // TMS_H
