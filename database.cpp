#include "database.h"
using namespace std;

Database* Database::databaseconnection = nullptr;

Database::Database()
{}
void Database::setDBname()
{
    if(!db.isValid())
    {
        db = QSqlDatabase::addDatabase("QODBC");
        QString dsn = "Driver={MySQL ODBC 9.1 Unicode Driver};Server=127.0.0.1,3306;Database=akademine;Uid=root;Pwd=;MULTI_HOST=1;";
        db.setDatabaseName(dsn);
    }
}
void Database::closeDB()
{
    if(db.open())
    {
        db.close();
        QSqlDatabase::removeDatabase("akademine");
        qDebug() << "Database is closed";
    }
}
bool Database::isDatabaseOpen()
{
    return db.open();
}
Database* Database::getdbconnection()
{
    if (!databaseconnection)
    {
        databaseconnection = new Database();
    }
    return databaseconnection;
}
QSqlDatabase Database::getDB()
{
    return db;
}
