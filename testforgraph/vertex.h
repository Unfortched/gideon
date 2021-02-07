#ifndef VERTEX_H
#define VERTEX_H
#include<QPainter>
#include<QGraphicsItem>
#include<QGraphicsScene>


class Vertex
{
public:
    int x;
    int y;
    bool IsClicked;

    Vertex(){}

    Vertex(int X, int Y, bool Clicked)
    {
        x = X;
        y = Y;
        IsClicked = Clicked;
    }

    void Draw(QGraphicsScene *f,QPen red, QPen black)
    {
        if(IsClicked)
        {
            f->addEllipse(x,y,50,50,red);
            f->update();
        }

        else
        {
            f->addEllipse(x,y,50,50,black);
            f->update();
        }

    }
};

#endif // VERTEX_H
