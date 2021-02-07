#include "widget.h"
#include "ui_widget.h"
#include "vertex.h"
#include <queue>
#include <stack>
#include <QDebug>

int k,start,end;
bool st,en;

QList<Vertex*> vertex;
QList<int> Near[50];
int levels[50];
int mas[50][50];
int mas1[50][50];
int dgr[50];
int ves[]={1,3,5,10,11,1,6,1,1,3,4};
//static int vert;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->centerOn(0,0);
    scene->setSceneRect(0,0,ui->graphicsView->width() - 5,ui->graphicsView->height() - 5);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPen black(Qt::black);
    black.setWidth(2);
    QPen red(Qt::red);
    red.setWidth(2);

    for(int i=0;i<vertex.count();++i)
        vertex[i]->Draw(scene,red,black);
}


void Widget::mousePressEvent(QMouseEvent *event)
{

  // QPoint globalPos = this->mapToGlobal( event->pos() );
   QPointF scenePos = ui->graphicsView->mapToScene( event->pos() );

    if(event->button() == Qt::LeftButton)
    {
        k++;
       // qDebug() << event->pos();
        Vertex *a = new Vertex(scenePos.x() - 30,scenePos.y() - 30,false);
        vertex.push_back(a);
        number = scene->addText(QString::number(k));
        number->setScale(2);
        number->setPos(scenePos.x() - 20,scenePos.y() - 30);
    }

    if(event->button() == Qt::RightButton)
    {
        for(int i=0;i<vertex.count(); ++i)
        {
            if(scenePos.x() >= vertex[i]->x && scenePos.x() <= vertex[i]->x + 50 && scenePos.y() >= vertex[i]->y && scenePos.y() <= vertex[i]->y + 50)
            {

                if(!st)
                {
                    st = true;
                    vertex[i]->IsClicked = !vertex[i]->IsClicked;
                    start = i;
                }

                else
                {
                    if(i!=start)
                    {
                        en = true;
                        vertex[i]->IsClicked = !vertex[i]->IsClicked;
                        end = i;
                    }
                }
            }

        }

        if(st && en)
        {
            Near[start].push_back(end);
            Near[end].push_back(start);
            st = en = false;

            int vert = rand()%15;
            mas[start][end] = vert;
            mas[end][start] = vert;

            vertex[start]->IsClicked = !vertex[start]->IsClicked;
            vertex[end]->IsClicked = !vertex[end]->IsClicked;

            line = scene->addLine(vertex[start]->x + 25,vertex[start]->y + 25,vertex[end]->x + 25,vertex[end]->y + 25,QPen(Qt::red));
            number = scene->addText(QString::number(vert));
            number->setScale(2);
            number->setPos((vertex[end]->x + vertex[start]->x - 25)/2,(vertex[end]->y + vertex[start]->y - 25)/2);
        }
    }
     repaint();

}

void Widget::dfs(int start, bool check_dfs[])
{
    check_dfs[start] = true;
    ui->listWidget->addItem(QString::number(start+1));
    for(int i=0;i<Near[start].count();++i)
        if(!check_dfs[Near[start][i]])
            dfs(Near[start][i],check_dfs);
}

void Widget::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    bool check_dfs[vertex.count()];
    dfs(ui->lineEdit_2->text().toInt()-1,check_dfs);
}

void Widget::bfs(int start, bool check_bfs[])
{
    check_bfs[start] = true;
    std::queue<int> bfsqueue;
    bfsqueue.push(start);
    ui->listWidget_2->addItem(QString::number(start+1));
    while(!bfsqueue.empty())
    {
        int fr = bfsqueue.front();
        bfsqueue.pop();

        for(int i=0;i<Near[fr].count();++i)
        {
            int v = Near[fr][i];
            if(!check_bfs[v])
            {
                check_bfs[v] = true;
                ui->listWidget_2->addItem(QString::number(v+1));
                bfsqueue.push(v);
            }
        }
    }
}

void Widget::Dijkstra(int start, int end)
{
      int temp; // временный вес ребра
      int minindex, min; // индекс и вес ребра
      int dk[vertex.count()]; // метки вершин
      bool visited[vertex.count()]; // посещение вершин
      int pred[vertex.count()];

     for (int i = 0; i<vertex.count(); i++)
         dk[i] = 10000; // расставляем метки для вершин

       dk[start] = 0;

    do {

        minindex = 10000;
        min = 10000;
        for (int i = 0; i<vertex.count(); i++)
        {
          if (!visited[i] && (dk[i]<min))
          {
            min = dk[i]; //запоминаем метку вершины
            minindex = i; // и ее номер
          }
        }

        if (minindex != 10000)
        {
          for (int i = 0; i<vertex.count(); i++)
          {
            if (mas[minindex][i] > 0) // если у этой вершины есть ребра
            {
              temp = min + mas[minindex][i]; // к метке прибавляем вес ребра
              if (temp < dk[i])
              { // если новая метка меньше старой,
                dk[i] = temp; // то замена
                pred[i] = minindex; // запоминаем "предка"
              }

            }
          }
          visited[minindex] = true; // помечаем вершину как пройденную
        }
      } while (minindex < 10000);

       ui->listWidget->clear();
       QString str; str.push_front(QString::number(end+1));
       SearchPath(pred,end,start,&str);
       ui->lineEdit_4->setText(QString::number(dk[end]) + "    Path: " + str);
}

bool Widget::CheckforEul()
{

    for(int i=0;i<50;++i)
        for(int j=0;j<50;++j)
            if(mas[i][j] > 0)
                dgr[i]++;

    int count = 0;
    for(int i=0;i<50;++i)
        if(dgr[i]%2 == 1)
            count++;

    bool after[vertex.count()];
    bool yes = true;

    dfs(0,after);
    ui->listWidget->clear();

    for(int i=0;i<vertex.count();++i)
        if(!after[i])
            yes = false;

    if(count > 2 || !yes)
        return false;
    return true;
}

void Widget::findEulerPath()
{
    std::stack<int> euler;
    int start;
    QString str;

    for(int i=0;i<50;++i)
        if(dgr[i]%2 == 1)
        {
            start = i;
            break;
        }

     euler.push(start);
     str.push_back("");
     //str.push_back(QString::number(start+1));

    while(!euler.empty())
    {
      int top = euler.top();

      for(int i=0;i<50;++i)
          if(mas1[top][i] > 0)
          {
              euler.push(i);
              mas1[top][i] = 0;
              mas1[i][top] = 0;
              break;
          }

      if(top == euler.top())
      {
          euler.pop();
          str.push_back(QString::number(top+1));
      }
    }
    std::reverse(str.begin(),str.end());
    ui->listWidget_3->addItem(str);

}

void Widget::SearchPath(int d[], int end, int start, QString *str) // Дейкстры
{
    str->push_front(QString::number(d[end]+1));
    if(d[end]!=start)
        SearchPath(d,d[end],start,str);
}

void Widget::on_pushButton_clicked()
{
    ui->listWidget_2->clear();
    bool check_bfs[vertex.count()];
    bfs(ui->lineEdit_2->text().toInt()-1,check_bfs);
}

void Widget::on_pushButton_3_clicked()
{
    ui->lineEdit_4->clear();
    Dijkstra(ui->lineEdit_2->text().toInt()-1,ui->lineEdit->text().toInt()-1);
}

void Widget::on_pushButton_4_clicked()
{
    for(int i=0;i<50;++i)
        for(int j=0;j<50;++j)
            mas1[i][j] = mas[i][j];

    ui->listWidget_3->clear();
    if(CheckforEul())
        findEulerPath();
    else
        ui->listWidget_3->addItem("No Euler Path");
}
