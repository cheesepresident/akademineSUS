#ifndef LOGIN_H
#define LOGIN_H

#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

class login
{
public:
    login();
    QString getPassword(QString Username, QString Password, login lg);
    void getID(int temp);
};

#endif // LOGIN_H
