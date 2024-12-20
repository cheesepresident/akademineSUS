#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "login.h"

loginWindow::loginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_prisijungti_clicked()
{
    qDebug() << " login button pressed";
    ui->prisijungti->setEnabled(false);

    QString Username = ui -> txt_nvardas -> text();
    QString Password = ui -> txt_slaptazodis -> text();

    if (Username.isEmpty() || Password.isEmpty()) {
        qDebug() << "Username or password is empty";
        ui->loginerror->setText("Neįvesti duomenys");
        ui->prisijungti->setEnabled(true);
        return;
    }
    login lg;
    QString returns = lg.getPassword(Username, Password, lg);
    ui->loginerror->setText(returns);
    ui->prisijungti->setEnabled(true);
}


void loginWindow::on_pushButton_clicked()
{
    QApplication::quit();
}

