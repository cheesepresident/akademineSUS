#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QtDebug>
#include <QSqlDatabase>
class Database
{
protected:
    static Database* databaseconnection;
    QSqlDatabase db;
    Database();
public:
    void setDBname();
    void closeDB();
    static Database* getdbconnection();
    bool isDatabaseOpen();
    QSqlDatabase getDB();
};

#endif // CONNECTTODATABASE_H
