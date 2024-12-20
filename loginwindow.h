#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>


namespace Ui {
class loginWindow;
}

class loginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();
    int getUserType();
    void setUsertype(int type);

private slots:
    void on_prisijungti_clicked();

    void on_pushButton_clicked();

private:
    Ui::loginWindow *ui;
    int userType;
};

#endif // LOGINWINDOW_H
