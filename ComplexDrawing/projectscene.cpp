#include "projectscene.h"
#include <QGraphicsTextItem>
#include "cpoint.h"
#include <math.h>

int ProjectScene::X = 0;
int ProjectScene::Y = 0;
int ProjectScene::dz = 0;
double ProjectScene::alpha = 0;
double ProjectScene::beta = 0;
double ProjectScene::gamma = 0;


ProjectScene::ProjectScene(QObject *parent) : QGraphicsScene(parent)
{
    pointsName.push_back("T");   points.push_back(T); //     0
    pointsName.push_back("T2");  points.push_back(T1); //    1
    pointsName.push_back("T3");  points.push_back(T2); //    2
    pointsName.push_back("Tz");  points.push_back(center);// 3
    pointsName.push_back("T1");  points.push_back(Z); //     4
    pointsName.push_back("Tx");  points.push_back(Z1); //    5
    pointsName.push_back("Ty");  points.push_back(Z2); //    6
    pointsName.push_back("O");   points.push_back(centerZ);//7
    pointsName.push_back("X+");  points.push_back(ox1); //   8
    pointsName.push_back("X-");  points.push_back(ox2); //   9
    pointsName.push_back("Y+");  points.push_back(oy1); //   10
    pointsName.push_back("Y-");  points.push_back(oy2); //   11
    pointsName.push_back("Z+");  points.push_back(oz1); //   12
    pointsName.push_back("Z-");  points.push_back(oz2); //   13

    red.setColor(Qt::red);
    black.setColor(Qt::black);
    blue.setColor(Qt::blue);
}


void ProjectScene::DrawXYZ()
{
    points[0].setCoord(X,Y,dz);
    points[1].setCoord(X,0,dz);
    points[2].setCoord(0,Y,dz);
    points[3].setCoord(0,0,dz);

    points[4].setCoord(X,Y,0);
    points[5].setCoord(X,0,0);
    points[6].setCoord(0,Y,0);
    points[7].setCoord(0,0,0);

    points[8].setCoord(120,0,0);
    points[9].setCoord(-120,0,0);
    points[10].setCoord(0,-120,0);
    points[11].setCoord(0,120,0);
    points[12].setCoord(0,0,120);
    points[13].setCoord(0,0,-120);

    DrawPoints();
    DrawLines();
}

void ProjectScene::DrawPoints()
{
    for(int i=0;i<points.count();++i)
    {

         if(pointsName[i] == "T")
            addEllipse(points[i]._x()- 6,points[i]._y() - 6,12,12,blue,QBrush(Qt::green));
         if(pointsName[i] == "T1")
            addEllipse(points[i]._x()- 5,points[i]._y() - 5,10,10,blue,QBrush(Qt::yellow));
         if(pointsName[i] == "T2")
            addEllipse(points[i]._x()- 5,points[i]._y() - 5,10,10,blue,QBrush(Qt::darkCyan));
         if(pointsName[i] == "T3")
            addEllipse(points[i]._x()- 5,points[i]._y() - 5,10,10,blue,QBrush(Qt::darkMagenta));

        addEllipse(points[i]._x() - 2, points[i]._y() - 2, 3,3,blue);

        text = new QGraphicsTextItem(pointsName[i]);
        text->setPos(points[i]._x() + 2,points[i]._y() + 2);
        addItem(text);
    }
}

void ProjectScene::DrawLines()
{
    addLine(points[8]._x(),points[8]._y(),points[9]._x(),points[9]._y(),red);
    addLine(points[10]._x(),points[10]._y(),points[11]._x(),points[11]._y(),red);
    addLine(points[12]._x(),points[12]._y(),points[13]._x(),points[13]._y(),red);

    addLine(points[1]._x(),points[1]._y(),points[3]._x(),points[3]._y(),black);
    addLine(points[2]._x(),points[2]._y(),points[3]._x(),points[3]._y(),black);
    addLine(points[0]._x(),points[0]._y(),points[2]._x(),points[2]._y(),black);
    addLine(points[0]._x(),points[0]._y(),points[1]._x(),points[1]._y(),black);

    addLine(points[0]._x(),points[0]._y(),points[4]._x(),points[4]._y(),black);
    addLine(points[1]._x(),points[1]._y(),points[3]._x(),points[3]._y(),black);
    addLine(points[1]._x(),points[1]._y(),points[5]._x(),points[5]._y(),black);
    addLine(points[2]._x(),points[2]._y(),points[6]._x(),points[6]._y(),black);
    addLine(points[1]._x(),points[1]._y(),points[3]._x(),points[3]._y(),black);
    addLine(points[3]._x(),points[3]._y(),points[7]._x(),points[7]._y(),black);
    addLine(points[4]._x(),points[4]._y(),points[6]._x(),points[6]._y(),black);
    addLine(points[4]._x(),points[4]._y(),points[5]._x(),points[5]._y(),black);
    addLine(points[6]._x(),points[6]._y(),points[7]._x(),points[7]._y(),black);
}

void ProjectScene::InputCoord(int x, int y, int z)
{
   if(x) X = x;
   if(y) Y = y;
   if(z) dz = z;

   DrawXYZ();
}

void ProjectScene::InputAngle(double a, double b, double c)
{
    if(a) alpha = a;
    if(b) beta = b;
    if(c) gamma = c;

    DrawXYZ();
}




