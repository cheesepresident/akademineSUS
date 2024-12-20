#include "lecturerwindow.h"
#include "ui_lecturerwindow.h"
#include "lecturer.h"
#include "database.h"


lecturerwindow::lecturerwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::lecturerwindow)
{
    ui->setupUi(this);
}

lecturerwindow::~lecturerwindow()
{
    delete ui;
}
void lecturerwindow::loadData()
{
    qDebug() << "loading lecturer data";
    lecturer* lecturer = lecturer::getInstance();
    lecturer->setSubjects();
    lecturer->loadUserInfo();

    ui->vardas->setText(lecturer->getName());
    ui->pavarde->setText(lecturer->getSurname());

    ui->dalykai->setStyleSheet("QListWidget {padding: 10px;} QListWidget::item { margin: 17px; }");

    int vectorSize = lecturer->getSubjects().size();
    for(int i = 0; i < vectorSize; i++)
    {
        QString text = QString("%1 %2").arg(lecturer->getSubjects()[i], lecturer->getSubjectSGroups()[i]);
        ui->dalykai->addItem(text);
    }
}

void lecturerwindow::on_dalykai_itemClicked(QListWidgetItem *item)
{
    lecturer* lecturer = lecturer::getInstance();
    int row = 0;

    int vectorSize = lecturer->getSubjects().size();
    for(int i = 0; i < vectorSize; i++)
    {
        QString text = QString("%1 %2").arg(lecturer->getSubjects()[i], lecturer->getSubjectSGroups()[i]);
        if(item->text() == text)row = i;
    }
    qDebug() << lecturer->getSubjectsID()[row];
    QString view = QString("d %1").arg(lecturer->getSubjectsID()[row]);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(view);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->show();


}


void lecturerwindow::on_pushButton_clicked()
{

}


void lecturerwindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

