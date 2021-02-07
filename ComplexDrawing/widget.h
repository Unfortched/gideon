#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "projectscene.h"
#include "complexscene.h"
#include <QPainter>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_X_valueChanged(int value);

    void on_Y_valueChanged(int value);

    void on_Z_valueChanged(int value);

    void on_alpha_valueChanged(int value);

    void on_beta_valueChanged(int value);

    void on_gamma_valueChanged(int value);

private:
    Ui::Widget *ui;
    ProjectScene *prj;
    ComplexScene *cmp;
    QGraphicsTextItem *text;
    QPainter *p1, *p2;
};

#endif // WIDGET_H
