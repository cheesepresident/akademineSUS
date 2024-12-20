#include "student.h"
#include "database.h"
#include <ctime>
student* student::instance = nullptr;

student::student()
{}
student* student::getInstance()
{
    if (!instance)
    {
        instance = new student();
    }
    return instance;
}
void student::loadUserInfo()
{
    int date;
        Database* db = Database::getdbconnection();
        QSqlQuery query(db->getDB());

        query.prepare("SELECT vardas, pavarde FROM naudotojas WHERE nID = :id");
        query.bindValue(":id", userId);

        if (query.exec() and query.next()) {

                name = query.value("vardas").toString();
                surname = query.value("pavarde").toString();
                qDebug() << name << " " << surname;
        }else {
            qDebug() << "Query failed: " << query.lastError().text();
        }
        query.prepare("SELECT DISTINCT gID, pavadinimas, `pradzios metai` FROM grupe JOIN `studentu grupes` ON grupe.gID = `studentu grupes`.grupe JOIN naudotojas ON `studentu grupes`.studentas = :id");
        query.bindValue(":id", userId);
        if (query.exec() and query.next()) {

            groupID = query.value("gID").toInt();
            group = query.value("pavadinimas").toString();
            date = query.value("pradzios metai").toInt();
            time_t currentTime = time(nullptr);

            tm* localTime = localtime(&currentTime);

            int year = 1900 + localTime->tm_year;
            int month = 1 + localTime->tm_mon;
            semester = (year - date) * 2;
            if(month > 8) semester++;
        }else {
            qDebug() << "Query failed: " << query.lastError().text();
        }
        query.prepare("SELECT dalykas.dID, dalykas.pavadinimas FROM dalykas JOIN `programos dalykai` ON dalykas.dID = "
                      "`programos dalykai`.dalykas JOIN sprograma ON `programos dalykai`.programa = sprograma.pID JOIN "
                      "grupe ON sprograma.pID = grupe.programa WHERE grupe.gID = :gID AND `programos dalykai`.semestras = :semester; ");
        query.bindValue(":gID", groupID);
        query.bindValue(":semester", semester);
        if(query.exec())
        {
            while(query.next())
            {
                subjectsID.push_back(query.value("dalykas.dID").toInt());
                subjects.push_back(query.value("dalykas.pavadinimas").toString());
            }
        }
}
QString student::getGroup()
{
    return group;
}
int student::getSemester()
{
    return semester;
}
int student::getGroupID()
{
    return groupID;
}
vector<QString> student::getSubjects()
{
    return subjects;
}
vector<int> student::getSubjectsID()
{
    return subjectsID;
}
