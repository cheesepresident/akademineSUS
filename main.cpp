#include "adminwindow.h"
#include "loginwindow.h"
#include "student.h"
#include "studentswindow.h"
#include "database.h"
#include "lecturer.h"
#include "admin.h"
#include "lecturerwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    student* student = student::getInstance();
    lecturer* lecturer = lecturer::getInstance();
    admin * admin = admin::getInstance();

    loginWindow* lw = new loginWindow();

    int userType = 0;


    qDebug() << "Login window initialized";
    lw->show();
    lw->setWindowModality(Qt::WindowModal);
    a.exec();
    if(userType == 0)
    {
        if(student->getLoggedIn() == true) userType = 3;
        if(lecturer->getLoggedIn() == true) userType = 2;
        if(admin->getLoggedIn() == true) userType = 1;
    }
    qDebug() << userType;
    switch (userType) {
    case 1:{
        adminwindow* aw = new adminwindow();
        aw->setWindowFlag(Qt::WindowStaysOnTopHint);
        aw->show();
        aw->loadData();
        break;
    }
    case 2:{
        lecturerwindow* lew = new lecturerwindow();
        lew->setWindowFlag(Qt::WindowStaysOnTopHint);
        lew->show();
        lew->loadData();
        break;
    }
    case 3:{
        studentswindow* sw = new studentswindow();
        sw->setWindowFlag(Qt::WindowStaysOnTopHint);
        sw->show();
        sw->loadData();
        break;
    }
    lw->hide();
    }

    QObject::connect(&a, &QCoreApplication::aboutToQuit, []() {
        Database* dbInstance = Database::getdbconnection();
        dbInstance->closeDB();
        qDebug() <<"db closed after close";
    });
    return a.exec();
    return 0;
}
