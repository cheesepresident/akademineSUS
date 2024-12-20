#include "lecturer.h"
#include "database.h"

lecturer* lecturer::instance = nullptr;

lecturer::lecturer()
{}
lecturer* lecturer::getInstance()
{
    if (!instance)
    {
        instance = new lecturer();
    }
    return instance;
}
void lecturer::setSubjects()
{
    Database* db = Database::getdbconnection();

    QSqlQuery query(db->getDB());

    query.prepare("SELECT DISTINCT dalykas.pavadinimas, dalykas.dID, grupe.pavadinimas, grupe.gID FROM dalykas JOIN `programos dalykai`"
                  " ON `programos dalykai`.dalykas = dalykas.dID JOIN sprograma ON sprograma.pID = "
                  "`programos dalykai`.programa JOIN grupe ON sprograma.pID = grupe.programa WHERE `programos dalykai`.mokytojas = :id");
    query.bindValue(":id", userId);
    if(query.exec())
    {
        while (query.next())
        {
            subjects.push_back(query.value("dalykas.pavadinimas").toString());
            subjectSGroups.push_back(query.value("grupe.pavadinimas").toString());
            subjectsID.push_back(query.value("dalykas.dID").toString());
            subjectSGroupsID.push_back(query.value("grupe.gID").toString());
        }
    }
    else qDebug() << query.lastError();
}
vector<QString> lecturer::getSubjects()
{
    return subjects;
}
vector<QString> lecturer::getSubjectSGroups()
{
    return subjectSGroups;
}
vector<QString> lecturer::getSubjectsID()
{
    return subjectsID;
}
vector<QString> lecturer::getSubjectSGroupsID()
{
    return subjectSGroupsID;
}
