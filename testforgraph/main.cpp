#include "widget.h"
#include <QApplication>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setMouseTracking(true);
    w.show();

    return a.exec();
}
