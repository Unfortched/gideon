#ifndef CPOINT_H
#define CPOINT_H


class CPoint
{
public:
    CPoint();
    int _x();
    int _y();
    void setCoord(int a, int b, int c);
private:
    int x,y,z,dx,dy;
};

#endif // CPOINT_H
