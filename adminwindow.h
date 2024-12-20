#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class adminwindow;
}

class adminwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();
    void loadData();

private slots:
    void on_naudotojai_clicked();

    void on_pasalinti_clicked();

    void on_prideti_clicked();

    void on_dalykai_clicked();

    void on_pasalinti_2_clicked();

    void on_prideti_2_clicked();

    void on_programos_clicked();

    void on_pasalinti_3_clicked();

    void on_prideti_3_clicked();

    void on_pushButton_4_clicked();

    void on_pasalinti_4_clicked();

    void on_prideti_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::adminwindow *ui;
};

#endif // ADMINWINDOW_H
