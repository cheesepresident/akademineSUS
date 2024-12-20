#ifndef USER_H
#define USER_H

#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

class User
{
protected:
    QString name, surname;
    int userId, userType;
    bool LoggedIn = false;
public:
    void setUserId(int id);
    int getUserID();
    void setLoggedIn(bool value);
    bool getLoggedIn();
    void loadUserInfo();
    QString getName();
    QString getSurname();
};

#endif // USER_H
