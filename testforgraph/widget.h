#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
   virtual void paintEvent(QPaintEvent *pevent);
   virtual void mousePressEvent(QMouseEvent *event);
   void dfs(int start, bool check_dfs[]);
   void bfs(int start, bool check_bfs[]);
   void Dijkstra(int start, int end);
   bool CheckforEul();
   void findEulerPath();
   void SearchPath(int d[], int end, int start, QString *str);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

  //  void on_pushButton_4_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem *number;
    QGraphicsLineItem *line;
};

#endif // WIDGET_H
