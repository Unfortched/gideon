#include "cpoint.h"
#include "math.h"
#include "projectscene.h"

CPoint::CPoint()
{
}

int CPoint::_x()
{
    dx = x*cos(ProjectScene::alpha) - y*cos(ProjectScene::beta) + z*cos(ProjectScene::gamma);
    return dx;
}

int CPoint::_y()
{
    dy = x*sin(ProjectScene::alpha) - y*sin(ProjectScene::beta) + z*sin(ProjectScene::gamma);
    return dy;
}

void CPoint::setCoord(int a, int b, int c)
{
    x = a;
    y = b;
    z = c;
}
