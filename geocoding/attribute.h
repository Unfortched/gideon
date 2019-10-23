#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QWidget>
#include <dbmanager.h>
#include <QCheckBox>
#include <QTimer>

namespace Ui {
class attribute;
}

class attribute : public QWidget
{
    Q_OBJECT

public:
    explicit attribute(QWidget *parent = 0);
    ~attribute();
    void Update(QList<QList<QString>> s, QList<QList<QString>> n);

    void setTableName();

    int getDbNumber();

    QString getTableName();

    void LoadList(QList<QList<QString> > forTms[], QList<QList<QString> > forHrm[]);

    QStringList selectedColumns;

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void getNameByClick(int state);

    QString getNameToText(QString id, QString db, int startListNumber, int finishListNumber);

private:

    void clearLayout();

    Ui::attribute *ui;
    DbManager *db;
    QList<QList<QString>> tms[2], hrm[2];
public:
    int dbChoose;
    QString tableName;
    QString atrib, info;
    int count = 777;
    bool toDel = true;
};

#endif // ATTRIBUTE_H
