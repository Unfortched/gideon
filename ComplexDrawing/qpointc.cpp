#include "qpointc.h"
#include <QGraphicsScene>

QPointC::QPointC()
{

}

void QPointC::paint(QGraphicsScene *c, QPen *p, QBrush *b)
{
    c->addEllipse(x,y)
}

