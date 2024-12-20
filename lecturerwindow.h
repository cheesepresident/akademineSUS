#ifndef LECTURERWINDOW_H
#define LECTURERWINDOW_H

#include "qlistwidget.h"
#include <QWidget>

namespace Ui {
class lecturerwindow;
}

class lecturerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit lecturerwindow(QWidget *parent = nullptr);
    ~lecturerwindow();
    void loadData();

private slots:
    void on_dalykai_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::lecturerwindow *ui;
};

#endif // LECTURERWINDOW_H
