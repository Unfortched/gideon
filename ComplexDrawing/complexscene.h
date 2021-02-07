#ifndef COMPLEXSCENE_H
#define COMPLEXSCENE_H
#include <QGraphicsScene>
#include <QPoint>

class ComplexScene: public QGraphicsScene
{
public:
    ComplexScene(QObject *parent);
    void Input(int x, int y, int z);
    static int X,Y,Z;
protected:
    void Draw();
    void DrawLines();
    void DrawPoints();
    QPoint x1,x2,z1,z2;
    QPoint Tx,Ty1,Ty2,Tz,center;
    QPoint T1,T2,T3;
    QPen black,red, blue;
    QGraphicsTextItem *text;
    QList <QPoint> points;
    QList <QString> pointsName;
};

#endif // COMPLEXSCENE_H
