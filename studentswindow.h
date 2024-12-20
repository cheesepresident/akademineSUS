#ifndef STUDENTSWINDOW_H
#define STUDENTSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <QListWidgetItem>

namespace Ui {
class studentswindow;
}

class studentswindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentswindow(QWidget *parent = nullptr);
    ~studentswindow();
    void loadData();

private slots:
    void on_dalykai_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::studentswindow *ui;
};

#endif // STUDENTSWINDOW_H
