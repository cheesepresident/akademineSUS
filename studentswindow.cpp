#include "studentswindow.h"
#include "ui_studentswindow.h"
#include "student.h"
#include "database.h"
#include <vector>

studentswindow::studentswindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::studentswindow)
{
    ui->setupUi(this);
}

studentswindow::~studentswindow()
{
    delete ui;
}
void studentswindow::loadData()
{
    student* student = student::getInstance();
    student->loadUserInfo();

    ui->vardas->setText(student->getName());
    ui->pavarde->setText(student->getSurname());

    QString text1 =QString("Grupė: %1").arg(student->getGroup());
    ui->grupe->setText(text1);
    QString text2 =QString("Semestras: %1").arg(student->getSemester());
    ui->semestras->setText(text2);

    ui->dalykai->setStyleSheet("QListWidget {padding: 10px;} QListWidget::item { margin: 17px; }");
    int vectorSize = student->getSubjects().size();
    for(int i = 0; i < vectorSize; i++)
    {
        ui->dalykai->addItem(student->getSubjects()[i]);
    }
}

void studentswindow::on_dalykai_itemClicked(QListWidgetItem *item)
{
    student* student = student::getInstance();
    int row = 0;
    int vectorSize = student->getSubjects().size();
    for(int i = 0; i < vectorSize; i++)
    {
        if(item->text() == student->getSubjects()[i])row=i;
    }
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    query.prepare("SELECT `dalyko grupes`.pavadinimas, pazymis.pazymis FROM pazymis JOIN `studentu grupes` "
                  "ON `studentu grupes`.sgID = pazymis.sgrupes JOIN dalykaigrupesjoin ON pazymis.dalykasgr = "
                  "dalykaigrupesjoin.dgjID JOIN dalykas ON dalykaigrupesjoin.dalykas = dalykas.dID JOIN `dalyko grupes`"
                  " ON dalykaigrupesjoin.dgrupe = `dalyko grupes`.dgID WHERE `studentu grupes`.grupe = :group AND `studentu grupes`.studentas = :user AND dID = :subject; ");
    query.bindValue(":group", student->getGroupID());
    query.bindValue(":user", student->getUserID());
    query.bindValue(":subject", student->getSubjectsID()[row]);

    QStringList subjectgroup;
    QStringList verticalLabel = {"Pažymis"};
    vector<QString> grades;

    if(query.exec())
    {
        while(query.next())
        {
            subjectgroup.append(query.value("dalyko grupes.pavadinimas").toString());
            grades.push_back(query.value("pazymis.pazymis").toString());
            qDebug() << subjectgroup;
        }
    }
    ui->pazymiai->setColumnCount(subjectgroup.size());
    ui->pazymiai->setRowCount(1);
    ui->pazymiai->setHorizontalHeaderLabels(subjectgroup);
    ui->pazymiai->setVerticalHeaderLabels(verticalLabel);

    qDebug() << subjectgroup.size();
    for (int i = 0; i < subjectgroup.size() ; i++)
    {
        qDebug() << grades[i];
        ui->pazymiai->setItem(0, i, new QTableWidgetItem(QString(grades[i])));
    }
    ui->pazymiai->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}


void studentswindow::on_pushButton_clicked()
{
    QApplication::quit();
}

