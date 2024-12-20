#include "login.h"
#include "admin.h"
#include "database.h"
#include "student.h"
#include "lecturer.h"



login::login() {}
QString login::getPassword(QString Username, QString Password, login lg)
{
    Database* logindb = Database::getdbconnection();
    logindb->setDBname();
    QSqlQuery loginQuery(logindb->getDB());

    if(logindb->isDatabaseOpen()){
        loginQuery.prepare("SELECT pID FROM prisijungimas WHERE prisijungimonr = :username AND slaptazodis = :password");
        loginQuery.bindValue(":username", Username);
        loginQuery.bindValue(":password", Password);
    }
    else
    {
        qDebug() << "Problem connecting for loginDB";
        return "Serverio klaida";
    }
    if(loginQuery.exec())
    {
        qDebug() << "Connected to database";
    }
    else
    {
        qDebug() << "Problems fetching from database;" << loginQuery.lastError().text();
        return "Serverio klaida";
    }
    if(loginQuery.next())
    {
        qDebug() << "Login was successful";
        lg.getID(loginQuery.value("pID").toInt());
        return "Sėkmingai prisijungta, uždarykite langą";
    }
    else
    {
        qDebug()<< "Login was not succesful";
        return "Neteisingas slaptažodis arba vartojo vardas";
    }
}
void login::getID(int temp)
{
    Database* logindb = Database::getdbconnection();

    QSqlQuery loginQuery(logindb->getDB());


    qDebug() << "pID " << temp;
    loginQuery.prepare("SELECT tipas.tID, naudotojas.nID FROM naudotojas JOIN tipas ON naudotojas.tipas = tipas.tID WHERE naudotojas.prisijungimas = :userID");
    loginQuery.bindValue(":userID", temp);

    loginQuery.exec();
    if (!loginQuery.exec()) {
        qDebug() << "Query execution error:" << loginQuery.lastError().text();
        return;
    }
    if (loginQuery.next()) {
        int userType = loginQuery.value("tipas.tID").toInt();
        int userId = loginQuery.value("naudotojas.nID").toInt();

        switch (userType) {
        case 1:
        {
            admin* a = admin::getInstance();
            a->setUserId(userId);
            qDebug() << "Admin UserID: " << a->getUserID();
            a->setLoggedIn(true);
            break;
        }
        case 2: { // Lecturer
            lecturer* l = lecturer::getInstance();
            l->setUserId(userId);
            qDebug() << "Lecturer UserID: " << l->getUserID();
            l->setLoggedIn(true);
            break;
        }
        case 3: { // Student
            student* s = student::getInstance();
            s->setUserId(userId);
            qDebug() << "Student UserID: " << s->getUserID();
            s->setLoggedIn(true);
            break;
        }
        default:
            qDebug() << "Unknown user type!";
            break;
        }
    } else {
        qDebug() << "Invalid login credentials.";
    }
    }
