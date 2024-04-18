#include "home.h"
#include "credit.h"
#include "qevent.h"
#include "ui_home.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QDebug>
#include <synchapi.h>
#include "debit.h"
#include "login.h"
#include "qsqlquery.h"
#include "virement.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

Home::~Home()
{
    delete ui;
}

void Home::on_reduced_clicked()
{
    showMinimized();
}


void Home::on_close_clicked()
{
    close();
}

void Home::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void Home::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void Home::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

void Home::setUserInformation(const User& user)
{
    // Style
    ui->ActionBtnName->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_2->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_3->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_4->setAttribute(Qt::WA_TransparentForMouseEvents);
    // Convertir le solde en une chaîne de caractères avec le symbole €
    QString balanceString = QString::number(user.getBalance()) + " €";
    QString PELString = QString::number(user.getPELBalance()) + " €";
    QString LivretCString = QString::number(user.getLCBalance()) + " €";

    QSqlDatabase db = QSqlDatabase::database();

    //--------------------------------------------------------------------------------

    if (db.isValid()) {
        // Exécuter la requête SQL pour récupérer les données de l'historique
        QSqlQuery query(db);
        query.prepare("SELECT h.montant, h.id_compte_emetteur, h.id_compte_destinataire, h.type, h.title, h.description, h.date FROM users AS u LEFT JOIN accounts AS ppl ON ppl.userId = u.id AND ppl.type = 0 LEFT JOIN accounts AS pel ON pel.userId = u.id AND pel.type = 1 LEFT JOIN accounts AS lvc ON lvc.userId = u.id AND lvc.type = 2 LEFT JOIN history AS h ON h.id_compte_emetteur = ppl.id OR h.id_compte_emetteur = pel.id OR h.id_compte_emetteur = lvc.id OR h.id_compte_destinataire = ppl.id OR h.id_compte_destinataire = pel.id OR h.id_compte_destinataire = lvc.id WHERE u.id = :id ORDER BY h.date DESC LIMIT 8");
        query.bindValue(":id", user.getUserId());

        if (!query.exec()) {
            return;
        }
        int count = 1;
        // Itérer sur les résultats de la requête
        while (query.next()) {
            QString historyValue = QString("historyvalue%1").arg(count);
            QLabel *label1 = findChild<QLabel *>(historyValue);
            QString euro = "€";

            // Récupérer les valeurs des colonnes
            double montant = query.value(0).toDouble();
            QDateTime date = query.value(6).toDateTime();
            int id_compte_emetteur = query.value(1).toInt();
            int id_compte_destinataire = query.value(2).toInt();
            QString type = query.value(3).toString();
            QString title = query.value(4).toString();
            QString description = query.value(5).toString();

            QString historyTitle = QString("historytitle%1").arg(count);
            QLabel *label2 = findChild<QLabel *>(historyTitle);

            if (query.value(3) == 0) {
                type = "Virement";
                label2->setText(type);
                label1->setStyleSheet("color: red");
                QString signe = "-";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            } else if (query.value(3) == 1) {
                type = "Credit";
                label2->setText(type);
                label1->setStyleSheet("color: green");
                QString signe = "+";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            } else if (query.value(3) == 2) {
                type = "Debit";
                label2->setText(type);
                label1->setStyleSheet("color: red");
                QString signe = "-";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            }

            QString accID = QString("accID%1").arg(count);
            QLabel *label3 = findChild<QLabel *>(accID);
            label3->setText(QString::number(id_compte_emetteur));

            QString historyDescription = QString("historyDescription%1").arg(count);
            QLabel *label4 = findChild<QLabel *>(historyDescription);
            label4->setText(description);

            count = count + 1;


            // Afficher les valeurs récupérées sur la console avec un menu

        }
    } else {

    }

    //----------------------------------------------------------------------------------------------------------

    double lcBalance = user.getLCBalance();
    int progressPercentage = static_cast<int>((lcBalance / 10000.0) * 100.0);
    progressPercentage = std::min(std::max(progressPercentage, 0), 100);
    ui->progressBar_4->setValue(progressPercentage);

    // Utiliser les informations de l'utilisateur pour mettre à jour l'interface graphique de la page d'accueil
    ui->labelFirstName->setText(user.getFirstName());
    //ui->labelLastName->setText(user.getLastName());
    ui->labelFirstAccountBalance->setText(balanceString);

    // Ajoutez d'autres mises à jour d'interface utilisateur si nécessaire
    ui->labelPELAccountBalance->setText(PELString);
    ui->labelLCAccountBalance->setText(LivretCString);
    currentUser = new User(user);
}
//test
void Home::on_virement_clicked()
{
    virement *virementWindow = new virement(currentUser, this); // Passer la référence à la fenêtre principale
    virementWindow->show();
    //this->hide();
}

void Home::on_debit_clicked()
{
    debit *debit = new class debit(currentUser, this); // Passer la référence à la fenêtre principale
    debit->show();
    //this->hide();
}

void Home::on_credit_clicked()
{
    credit *credit = new class credit(currentUser, this); // Passer la référence à la fenêtre principale
    credit->show();
    //this->hide();
}

void Home::on_logoff_clicked()
{
    Login *login = new class Login();
    login->show();
    close();
}

void Home::refreshUserInfo() {
    // Récupérer l'utilisateur actuellement connecté
    //User newUser; // Implémentez cette fonction pour récupérer l'utilisateur actuel

    // Rafraîchir les données de l'utilisateur depuis la base de données
    currentUser->refreshUserData(); // Implémentez cette fonction dans la classe User

    // Mettre à jour l'interface utilisateur avec les nouvelles données de l'utilisateur
    ui->labelFirstName->setText(currentUser->getFirstName());
    ui->labelFirstAccountBalance->setText(QString::number(currentUser->getBalance()) + " €");
    ui->labelPELAccountBalance->setText(QString::number(currentUser->getPELBalance()) + " €");
    ui->labelLCAccountBalance->setText(QString::number(currentUser->getLCBalance()) + " €");

    // Mettez à jour d'autres éléments de l'interface utilisateur si nécessaire

    QSqlDatabase db = QSqlDatabase::database();

    //--------------------------------------------------------------------------------

    if (db.isValid()) {
        // Exécuter la requête SQL pour récupérer les données de l'historique
        QSqlQuery query(db);
        query.prepare("SELECT h.montant, h.id_compte_emetteur, h.id_compte_destinataire, h.type, h.title, h.description, h.date FROM users AS u LEFT JOIN accounts AS ppl ON ppl.userId = u.id AND ppl.type = 0 LEFT JOIN accounts AS pel ON pel.userId = u.id AND pel.type = 1 LEFT JOIN accounts AS lvc ON lvc.userId = u.id AND lvc.type = 2 LEFT JOIN history AS h ON h.id_compte_emetteur = ppl.id OR h.id_compte_emetteur = pel.id OR h.id_compte_emetteur = lvc.id OR h.id_compte_destinataire = ppl.id OR h.id_compte_destinataire = pel.id OR h.id_compte_destinataire = lvc.id WHERE u.id = :id ORDER BY h.date DESC LIMIT 8");
        query.bindValue(":id", currentUser->getUserId());


        if (!query.exec()) {
            return;
        }
        int count = 1;
        // Itérer sur les résultats de la requête
        while (query.next()) {
            QString historyValue = QString("historyvalue%1").arg(count);
            QLabel *label1 = findChild<QLabel *>(historyValue);
            QString euro = "€";

            // Récupérer les valeurs des colonnes
            double montant = query.value(0).toDouble();
            QDateTime date = query.value(6).toDateTime();
            int id_compte_emetteur = query.value(1).toInt();
            int id_compte_destinataire = query.value(2).toInt();
            QString type = query.value(3).toString();
            QString title = query.value(4).toString();
            QString description = query.value(5).toString();

            QString historyTitle = QString("historytitle%1").arg(count);
            QLabel *label2 = findChild<QLabel *>(historyTitle);

            if (query.value(3) == 0) {
                type = "Virement";
                label2->setText(type);
                label1->setStyleSheet("color: red");
                QString signe = "-";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            } else if (query.value(3) == 1) {
                type = "Credit";
                label2->setText(type);
                label1->setStyleSheet("color: green");
                QString signe = "+";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            } else if (query.value(3) == 2) {
                type = "Debit";
                label2->setText(type);
                label1->setStyleSheet("color: red");
                QString signe = "-";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
            }

            QString accID = QString("accID%1").arg(count);
            QLabel *label3 = findChild<QLabel *>(accID);
            label3->setText(QString::number(id_compte_emetteur));

            QString historyDescription = QString("historyDescription%1").arg(count);
            QLabel *label4 = findChild<QLabel *>(historyDescription);
            label4->setText(description);

            count = count + 1;


            // Afficher les valeurs récupérées sur la console avec un menu

        }
    } else {

    }
}

void Home::on_addbenef_cl_clicked() {

}
