#include "user.h"
#include "database.h"
void User::setUserId(int id)
{
    userId = id;
}
int User::getUserID()
{
    return userId;
}

void User::setLoggedIn(bool value)
{
    LoggedIn = value;
}
bool User::getLoggedIn()
{
    return LoggedIn;
}
void User::loadUserInfo()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    query.prepare("SELECT vardas, pavarde FROM naudotojas WHERE nID = :id");
    query.bindValue(":id", userId);

    if (query.exec()) {
        if (query.next()) {
            name = query.value("vardas").toString();
            surname = query.value("pavarde").toString();
            qDebug() << name << " " << surname;
        } else {
            qDebug() << "No data found!";
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
}
QString User::getName()
{
    return name;
}
QString User::getSurname()
{
    return surname;
}
