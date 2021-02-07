#include "complexscene.h"
#include <QPainter>
#include <QGraphicsTextItem>
#include <math.h>

int ComplexScene::X = 0;
int ComplexScene::Y = 0;
int ComplexScene::Z = 0;

ComplexScene::ComplexScene(QObject *parent) : QGraphicsScene(parent)
{
    pointsName.push_back("T1");   points.push_back(T1); //     0
    pointsName.push_back("T2");   points.push_back(T2); //     1
    pointsName.push_back("T3");   points.push_back(T3); //     2
    pointsName.push_back("Y+");   points.push_back(x1); //     3
    pointsName.push_back("X+");   points.push_back(x2); //     4
    pointsName.push_back("Y+");   points.push_back(z1); //     5
    pointsName.push_back("Z+");   points.push_back(z2); //     6
    pointsName.push_back("Tx");   points.push_back(Tx); //     7
    pointsName.push_back("Ty");   points.push_back(Ty1); //    8
    pointsName.push_back("Ty");   points.push_back(Ty2); //    9
    pointsName.push_back("Tz");   points.push_back(z2); //    10
    pointsName.push_back("O");    points.push_back(center);// 11

    red.setColor(Qt::red);
    black.setColor(Qt::black);
    blue.setColor(Qt::blue);

}

void ComplexScene::Draw()
{
    points[0].setX(-X);  points[0].setY(-Y);
    points[1].setX(-X);  points[1].setY(-Z);
    points[2].setX(-Y);  points[2].setY(-Z);
    points[3].setX(150); points[4].setX(-150);
    points[5].setY(150); points[6].setY(-150);
    points[7].setX(-X);  points[7].setY(0);
    points[8].setX( 0);  points[8].setY(-Y);
    points[9].setX(-Y);  points[9].setY(0);
    points[10].setX( 0); points[10].setY(-Z);
    points[11].setX(0);  points[11].setY(0);

    DrawPoints();
    DrawLines();
}

void ComplexScene::Input(int x, int y, int z)
{
   if(x) X = x;
   if(y) Y = y;
   if(z) Z = z;

   Draw();
}

void ComplexScene::DrawLines()
{
    addLine(QLine(points[3],points[4]),red);
    addLine(QLine(points[5],points[6]),red);

    addLine(QLine(points[1],points[10]),black);
    addLine(QLine(points[1],points[7]),black);
    addLine(QLine(points[7],points[0]),black);
    addLine(QLine(points[0],points[8]),black);
    addLine(QLine(points[10],points[2]),black);
    addLine(QLine(points[2],points[9]),black);

    int start = 0;
    int span = -1440;
    QRectF *rect = new QRectF(0,0,-Y+1,-Y+1);
    if(-Y < 0) { start = 1440; span = 1440; }
    QPoint top(-Y,-Y);
    rect->setTopLeft(center - top);
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(*rect);
    item->setStartAngle(start);
    item->setSpanAngle(span);
    addItem(item);

    update();
}

void ComplexScene::DrawPoints()
{
    for(int i=0;i<points.count();++i)
    {
        if(pointsName[i] == "T1")
           addEllipse(points[i].x()- 5,points[i].y() - 5,10,10,blue,QBrush(Qt::yellow));
        if(pointsName[i] == "T2")
           addEllipse(points[i].x()- 5,points[i].y() - 5,10,10,blue,QBrush(Qt::darkCyan));
        if(pointsName[i] == "T3")
           addEllipse(points[i].x()- 5,points[i].y() - 5,10,10,blue,QBrush(Qt::darkMagenta));

           addEllipse(points[i].x() - 2, points[i].y() - 2, 3,3,blue);

       /*if(pointsName[i]!="T")
        addEllipse(points[i]._x() - 2, points[i]._y() - 2, 3,3,blue);

        addEllipse(points[i]._x()- 5,points[i]._y() - 5,8,8,blue,QBrush(Qt::green));*/

       text = new QGraphicsTextItem(pointsName[i]);
       text->setPos(points[i].x() + 2,points[i].y() + 2);
       addItem(text);
    }
}

