#ifndef PROJECTSCENE_H
#define PROJECTSCENE_H
#include <QGraphicsScene>
#include "cpoint.h"
#include <QPoint>

class CPoint;

class ProjectScene: public QGraphicsScene
{
public:
    ProjectScene(QObject *parent);
    void InputCoord(int x, int y, int z);
    void InputAngle(double a, double b, double c);
    static int X,Y,dz;
    static double alpha,beta,gamma;
private:
    void DrawXYZ();
    void DrawPoints();
    void DrawLines();
    CPoint ox1,oy1,oz1,ox2,oy2,oz2;
    CPoint Z,Z1,Z2,Z3,centerZ;
    CPoint T,T1,T2,T3,center;
    QPen red,black,blue;
    QList <CPoint> points;
    QList <QString> pointsName;
    QGraphicsTextItem *text;
};

#endif // PROJECTSCENE_H
