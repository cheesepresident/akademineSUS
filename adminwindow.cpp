#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "admin.h"
#include "database.h"
#include <QSqlQueryModel>

adminwindow::adminwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::adminwindow)
{
    ui->setupUi(this);
}

adminwindow::~adminwindow()
{
    delete ui;
}
void adminwindow::loadData()
{
    ui->widgets->hide();

    qDebug() << "admin data";
    admin* admin = admin::getInstance();

    admin->loadUserInfo();

    ui->vardas->setText(admin->getName());
    ui->pavarde->setText(admin->getSurname());
}

void adminwindow::on_naudotojai_clicked()
{
    ui->widgets->show();
    ui->widgets->setCurrentWidget(ui->page_3);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("naudotojas");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->show();
}


void adminwindow::on_pasalinti_clicked()
{
    Database* db = Database::getdbconnection();
    QString id = ui->addid->text();

    QSqlQuery query(db->getDB());

    query.prepare("SELECT prisijungimas FROM naudotojas WHERE nID = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        if(query.next())
        {
            id = query.value("prisijungimas").toString();
        }
    }
    query.prepare("DELETE FROM prisijungimas WHERE pID = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        QSqlTableModel* model = new QSqlTableModel(this, db->getDB());
        model->setTable("naudotojas");
        model->select();
        ui->tableView->setModel(model);
    }
}

void adminwindow::on_prideti_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString Vardas = ui->addvardas->text();
    QString Pavarde = ui->addpavarde->text();
    QString telnr = ui->addtel->text();
    QString email = ui->addemail->text();
    QString asmenskodas = ui->addkodas->text();
    QString tipas = ui->addtipas->text();
    QString pID;
    if(Vardas.isEmpty() || Pavarde.isEmpty() || telnr.isEmpty() || email.isEmpty() || asmenskodas.isEmpty() || tipas.isEmpty()) ui->error->setText("Neužtenka duomenų");
        else{
            query.prepare("INSERT INTO prisijungimas (prisijungimonr, slaptazodis) VALUES (:vardas, :pavarde);");
            query.bindValue(":vardas", Vardas);
            query.bindValue(":pavarde", Pavarde);
            query.exec();
            if(query.exec("SELECT LAST_INSERT_ID();"))
            {
                if(query.next())
                    pID = query.value(0).toString();
            }
            qDebug() << pID;

            query.prepare("INSERT INTO naudotojas (vardas, pavarde, `tel nr`, email, `asmens kodas`, tipas, prisijungimas) VALUES (:vardas, :pavarde, :tel, :email , :kodas, :tipas, :prisijungimas);");
            query.bindValue(":vardas", Vardas);
            query.bindValue(":pavarde", Pavarde);
            query.bindValue(":tel", telnr);
            query.bindValue(":email", email);
            query.bindValue(":kodas", asmenskodas);
            query.bindValue(":tipas", tipas);
            query.bindValue(":prisijungimas", pID);

            if(query.exec())
            {
                ui->error->setText("Naudotojas pridėtas");
            }
            else ui->error->setText("Nepavyko pridėti");

            QSqlTableModel* model = new QSqlTableModel(this, db->getDB());
            model->setTable("naudotojas");
            model->select();
            ui->tableView->setModel(model);
        }

}


void adminwindow::on_dalykai_clicked()
{
    ui->widgets->show();
    ui->widgets->setCurrentWidget(ui->page_4);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("dalykas");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->show();
}


void adminwindow::on_pasalinti_2_clicked()
{
    Database* db = Database::getdbconnection();
    QString id = ui->addid_2->text();

    QSqlQuery query(db->getDB());


    query.prepare("DELETE FROM dalykas WHERE dID = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        QSqlTableModel* model = new QSqlTableModel(this, db->getDB());
        model->setTable("dalykas");
        model->select();
        ui->tableView->setModel(model);
    }
}


void adminwindow::on_prideti_2_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString dalykaspav = ui->adddalykas->text();
    QString aprasymas = ui->addaprasas->text();
    if(dalykaspav.isEmpty() || aprasymas.isEmpty()) ui->error->setText("Neužtenka duomenų");
    else{

        query.prepare("INSERT INTO dalykas (pavadinimas, aprasas) VALUES (:dalykas, :aprasas);");
        query.bindValue(":dalykas", dalykaspav);
        query.bindValue(":aprasas", aprasymas);

        if(query.exec())
        {
            ui->error->setText("Dalykas pridėtas");
        }
        else ui->error->setText("Nepavyko pridėti");

        QSqlTableModel* model = new QSqlTableModel(this, db->getDB());
        model->setTable("dalykas");
        model->select();
        ui->tableView->setModel(model);
    }
}


void adminwindow::on_programos_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    model->setQuery(R"(
        SELECT
            `programos dalykai`.pgID AS ID,
            dalykas.pavadinimas AS dalykas,
            sprograma.pavadinimas AS sprograma,
            `programos dalykai`.`semestras`,
            naudotojas.vardas,
            naudotojas.pavarde
        FROM `programos dalykai`
        JOIN dalykas ON `programos dalykai`.`dalykas` = dalykas.dID
        JOIN sprograma ON `programos dalykai`.`programa` = sprograma.pID
        JOIN naudotojas ON `programos dalykai`.`mokytojas` = naudotojas.nID
        ORDER BY ID ASC
    )");

    ui->programoslist->clear();
    ui->dalykaslist->clear();
    ui->mokytojaslist->clear();

    ui->widgets->show();
    ui->widgets->setCurrentWidget(ui->page);


    if (model->lastError().isValid()) {
        qDebug() << "Query error:" << model->lastError();
    }

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->resizeSection(0, 50);

    ui->tableView->show();

    query.prepare("SELECT DISTINCT pavadinimas FROM dalykas ORDER BY pavadinimas ASC");
        if(query.exec())
    {
        while(query.next())
        {
                ui->dalykaslist->addItem(query.value("pavadinimas").toString());
        }
    }

    query.prepare("SELECT DISTINCT pavadinimas FROM sprograma ORDER BY pavadinimas ASC");
        if(query.exec())
    {
        while(query.next())
        {
            ui->programoslist->addItem(query.value("pavadinimas").toString());
        }
    }

    query.prepare("SELECT DISTINCT vardas, pavarde FROM naudotojas WHERE tipas = 2 ORDER BY pavarde ASC");
        if(query.exec())
        {
            while(query.next())
            {
                QString text = QString("%1 %2").arg(query.value("vardas").toString(), query.value("pavarde").toString());
                ui->mokytojaslist->addItem(text);
            }
        }
}


void adminwindow::on_pasalinti_3_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString id = ui->addid_3->text();

    query.prepare("DELETE FROM `programos dalykai` WHERE pgID = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        QSqlQueryModel* model = new QSqlQueryModel(this);
        model->setQuery(R"(
        SELECT
            `programos dalykai`.pgID AS ID,
            dalykas.pavadinimas AS dalykas,
            sprograma.pavadinimas AS sprograma,
            `programos dalykai`.`semestras`,
            naudotojas.vardas,
            naudotojas.pavarde
        FROM `programos dalykai`
        JOIN dalykas ON `programos dalykai`.`dalykas` = dalykas.dID
        JOIN sprograma ON `programos dalykai`.`programa` = sprograma.pID
        JOIN naudotojas ON `programos dalykai`.`mokytojas` = naudotojas.nID
        ORDER BY ID ASC
    )");
        ui->tableView->setModel(model);
    }
}


void adminwindow::on_prideti_3_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString dalykaspav = ui->dalykaslist->currentText();
    QString programa = ui->programoslist->currentText();
    QString semestras = ui->semestras->text();
    QString mokytojas = ui->mokytojaslist->currentText();
    QStringList nameParts = mokytojas.split(" ");

    if (nameParts.size() >= 2) {
        QString vardas = nameParts[0];
        QString pavarde = nameParts[1];
        qDebug() << vardas << pavarde;

    if(dalykaspav.isEmpty() || programa.isEmpty() || semestras.isEmpty() || mokytojas.isEmpty()) ui->error->setText("Neužtenka duomenų");
    else{

        query.prepare("INSERT INTO `programos dalykai` (dalykas, programa, semestras, mokytojas) VALUES ((SELECT DISTINCT dID FROM dalykas WHERE pavadinimas = :dalykas),"
                      "(SELECT DISTINCT pID FROM sprograma WHERE pavadinimas = :programa), :sem, (SELECT DISTINCT nID FROM naudotojas WHERE vardas = :vardas AND pavarde = :pavarde));");

        query.bindValue(":dalykas", dalykaspav);
        query.bindValue(":programa", programa);
        query.bindValue(":sem", semestras);
        query.bindValue(":vardas", vardas);
        query.bindValue(":pavarde", pavarde);

        if(query.exec())
        {
            ui->error->setText("Programa pridėta");
        }
        else ui->error->setText("Nepavyko pridėti");

        QSqlQueryModel* model = new QSqlQueryModel(this);
        model->setQuery(R"(
        SELECT
            `programos dalykai`.pgID AS ID,
            dalykas.pavadinimas AS dalykas,
            sprograma.pavadinimas AS sprograma,
            `programos dalykai`.`semestras`,
            naudotojas.vardas,
            naudotojas.pavarde
        FROM `programos dalykai`
        JOIN dalykas ON `programos dalykai`.`dalykas` = dalykas.dID
        JOIN sprograma ON `programos dalykai`.`programa` = sprograma.pID
        JOIN naudotojas ON `programos dalykai`.`mokytojas` = naudotojas.nID
        ORDER BY ID ASC
    )");
        ui->tableView->setModel(model);
    }
}
}


void adminwindow::on_pushButton_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    ui->widgets->show();
    ui->widgets->setCurrentWidget(ui->page_2);

    model->setQuery(R"(
            SELECT
            `studentu grupes`.sgID AS ID,
            naudotojas.vardas AS vardas,
            naudotojas.pavarde AS pavarde,
            grupe.pavadinimas AS grupe
        FROM `studentu grupes`
        JOIN naudotojas ON `studentu grupes`.`studentas` = naudotojas.nID
        JOIN grupe ON `studentu grupes`.grupe = grupe.gID
        ORDER BY grupe.pavadinimas ASC
    )");

    ui->studentaslist->clear();
    ui->grupelist->clear();

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->resizeSection(0, 50);

    ui->tableView->show();
    query.prepare("SELECT DISTINCT pavadinimas FROM grupe ORDER BY pavadinimas ASC");
    if(query.exec())
    {
        while(query.next())
        {
            ui->grupelist->addItem(query.value("pavadinimas").toString());
        }
    }

    query.prepare("SELECT DISTINCT vardas, pavarde FROM naudotojas WHERE tipas = 3 ORDER BY pavarde ASC");
    if(query.exec())
    {
        while(query.next())
        {
            QString text = QString("%1 %2").arg(query.value("vardas").toString(), query.value("pavarde").toString());
            ui->studentaslist->addItem(text);
        }
    }

}


void adminwindow::on_pasalinti_4_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString id = ui->addid_4->text();

    query.prepare("DELETE FROM `studentu grupes` WHERE sgID = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        QSqlQueryModel* model = new QSqlQueryModel(this);
        model->setQuery(R"(
            SELECT
            `studentu grupes`.sgID AS ID,
            naudotojas.vardas AS vardas,
            naudotojas.pavarde AS pavarde,
            grupe.pavadinimas AS grupe
        FROM `studentu grupes`
        JOIN naudotojas ON `studentu grupes`.`studentas` = naudotojas.nID
        JOIN grupe ON `studentu grupes`.grupe = grupe.gID
        ORDER BY grupe.pavadinimas ASC
    )");
        ui->tableView->setModel(model);
    }
}


void adminwindow::on_prideti_4_clicked()
{
    Database* db = Database::getdbconnection();
    QSqlQuery query(db->getDB());

    QString grupe = ui->grupelist->currentText();
    QString studentas = ui->studentaslist->currentText();
    QStringList nameParts = studentas.split(" ");

    if (nameParts.size() >= 2) {
        QString vardas = nameParts[0];
        QString pavarde = nameParts[1];
        qDebug() << vardas << pavarde;

        if(grupe.isEmpty() || studentas.isEmpty()) ui->error->setText("Neužtenka duomenų");
        else{

            query.prepare("INSERT INTO `studentu grupes` (`grupe`, `studentas`) VALUES ((SELECT DISTINCT gID FROM grupe WHERE pavadinimas = :grupe),"
                          "(SELECT DISTINCT nID FROM naudotojas WHERE vardas = :vardas AND pavarde = :pavarde));");

            query.bindValue(":grupe", grupe);
            query.bindValue(":vardas", vardas);
            query.bindValue(":pavarde", pavarde);

            if(query.exec())
            {
                ui->error->setText("studentu grupe pridėta");
            }
            else ui->error->setText("Nepavyko pridėti");

            QSqlQueryModel* model = new QSqlQueryModel(this);
            model->setQuery(R"(
            SELECT
            `studentu grupes`.sgID AS ID,
            naudotojas.vardas AS vardas,
            naudotojas.pavarde AS pavarde,
            grupe.pavadinimas AS grupe
        FROM `studentu grupes`
        JOIN naudotojas ON `studentu grupes`.`studentas` = naudotojas.nID
        JOIN grupe ON `studentu grupes`.grupe = grupe.gID
        ORDER BY grupe.pavadinimas ASC
    )");
            ui->tableView->setModel(model);
    }
    }}


void adminwindow::on_pushButton_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery(R"(
            SELECT
            `studentu grupes`.sgID AS ID,
            naudotojas.vardas AS vardas,
            naudotojas.pavarde AS pavarde,
            grupe.pavadinimas AS grupe
        FROM `studentu grupes`
        JOIN naudotojas ON `studentu grupes`.`studentas` = naudotojas.nID
        JOIN grupe ON `studentu grupes`.grupe = grupe.gID
        ORDER BY ID ASC
    )");
    ui->tableView->setModel(model);
}


void adminwindow::on_pushButton_2_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery(R"(
            SELECT
            `studentu grupes`.sgID AS ID,
            naudotojas.vardas AS vardas,
            naudotojas.pavarde AS pavarde,
            grupe.pavadinimas AS grupe
        FROM `studentu grupes`
        JOIN naudotojas ON `studentu grupes`.`studentas` = naudotojas.nID
        JOIN grupe ON `studentu grupes`.grupe = grupe.gID
        ORDER BY grupe.pavadinimas ASC
    )");
    ui->tableView->setModel(model);
}


void adminwindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

