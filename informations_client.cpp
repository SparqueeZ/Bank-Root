#include "informations_client.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_informations_client.h"
#include <synchapi.h>
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

informations_client::informations_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

informations_client::~informations_client()
{
    delete ui;
}

void informations_client::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client::on_reduced_infoc_clicked()
{
    showMinimized();
}


void informations_client::on_close_infoc_clicked()
{
    close();
}

void informations_client::on_fullscreen_infoc_clicked()
{

}

void informations_client::on_deco_infoc_clicked()
{

}

void informations_client::setUserId(const QString &userId)
{
    this->m_userId = userId;

    QSqlDatabase db = QSqlDatabase::database();

    User client;
    // Récuperer les informations de l'user via son ID.
    client.getInformations(userId.toInt());
    // Mettre les infos des comptes en banque
    ui->labelFirstAccountBalance_96->setText(QString("%1").arg(client.getPpl_balance()));
    ui->labelPELAccountBalance_12->setText(QString("%1").arg(client.getPel_balance()));
    ui->labelLCAccountBalance_12->setText(QString("%1").arg(client.getLvc_balance()));

    // Mettre les informations proprietaire
    ui->inf_cli_owner_lastname->setText("Nom : " + client.getOwner_lastname());
    ui->inf_cli_owner_firstname->setText("Prénom : " + client.getOwner_firstname());
    ui->inf_cli_owner_dateOfBirth->setText("Date de naissance : " + client.getOwner_firstname()); // TODO : A changer par la date de naissance
    ui->inf_cli_owner_profilId->setText(QString("ID du profil : %1").arg(client.getOwner_profilId()));
    ui->inf_cli_owner_login->setText("Identifiant : " + client.getOwner_firstname());

    // Mettre les informations conjoint
    ui->inf_cli_coowner_lastname->setText("Nom : " + client.getCoowner_lastname());
    ui->inf_cli_coowner_firstname->setText("Prénom : " + client.getCoowner_firstname());
    ui->inf_cli_coowner_dateOfBirth->setText("Date de naissance : " + client.getCoowner_firstname()); // TODO : A changer par la date de naissance
    ui->inf_cli_coowner_profilId->setText(QString("ID de l'utilisateur : %1").arg(client.getCoowner_profilId()));
    ui->inf_cli_coowner_login->setText("Identifiant : " + client.getCoowner_firstname());

    // Mettre les informations utilisateur
    ui->inf_cli_username->setText("Utilisateur : " + client.getUsername());
    QString userRole = client.getRole() == 1 ? "Administrateur" : "Utilisateur";
    ui->inf_cli_userrole->setText("Role : " + userRole);

    if (db.isValid()) {
        // Exécuter la requête SQL pour récupérer les données de l'historique
        QSqlQuery query(db);
        query.prepare("SELECT h.montant, h.id_compte_emetteur, h.id_compte_destinataire, h.type, h.title, h.description, h.date FROM users AS u LEFT JOIN accounts AS ppl ON ppl.userId = u.id AND ppl.type = 0 LEFT JOIN accounts AS pel ON pel.userId = u.id AND pel.type = 1 LEFT JOIN accounts AS lvc ON lvc.userId = u.id AND lvc.type = 2 LEFT JOIN history AS h ON h.id_compte_emetteur = ppl.id OR h.id_compte_emetteur = pel.id OR h.id_compte_emetteur = lvc.id OR h.id_compte_destinataire = ppl.id OR h.id_compte_destinataire = pel.id OR h.id_compte_destinataire = lvc.id WHERE u.id = :id ORDER BY h.date DESC LIMIT 8");
        query.bindValue(":id", m_userId);

        if (!query.exec() || !query.next()) {
            return;
        }
        int count = 1;
        // Itérer sur les résultats de la requête
        while (query.next()) {
            QString image = QString("image%1").arg(count);
            QWidget *widget1 = findChild<QWidget *>(image);
            widget1->setStyleSheet("background-color: #595554");


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
                QString accID = QString("accID%1").arg(count);
                QLabel *label3 = findChild<QLabel *>(accID);
                label3->setText(QString::number(id_compte_emetteur));
            } else if (query.value(3) == 1) {
                type = "Credit";
                label2->setText(type);
                label1->setStyleSheet("color: green");
                QString signe = "+";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
                QString accID = QString("accID%1").arg(count);
                QLabel *label3 = findChild<QLabel *>(accID);
                label3->setText(QString::number(id_compte_destinataire));
            } else if (query.value(3) == 2) {
                type = "Debit";
                label2->setText(type);
                label1->setStyleSheet("color: red");
                QString signe = "-";
                QString value = QString("%1%2%3").arg(signe).arg(QString::number(montant)).arg(euro);
                label1->setText(value);
                QString accID = QString("accID%1").arg(count);
                QLabel *label3 = findChild<QLabel *>(accID);
                label3->setText(QString::number(id_compte_emetteur));
            }


            QString historyDescription = QString("historyDescription%1").arg(count);
            QLabel *label4 = findChild<QLabel *>(historyDescription);
            label4->setText(description);

            count = count + 1;


            // Afficher les valeurs récupérées sur la console avec un menu

        }
    } else {

    }
}
