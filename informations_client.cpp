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


    qDebug() << this->m_userId.toInt() << userId.toInt();

    double balance = 0.0;
    double PELBalance = 0.0;
    double LCBalance = 0.0;

    QSqlQuery queryGetUser;
    queryGetUser.prepare("SELECT u.id AS id, u.firstname AS firstname, u.lastname AS lastname, u.dateOfBirth AS dateofbirth, u.role AS role, u.login AS login, a1.balance AS balance, a1.id AS firstAccountId, a2.balance AS balancePEL, a2.id AS PELAccountId, a3.balance AS balanceLC, a3.id AS LCAccountId FROM users u LEFT JOIN accounts a1 ON u.id = a1.userId AND a1.type = 0 LEFT JOIN accounts a2 ON u.id = a2.userId AND a2.type = 1 LEFT JOIN accounts a3 ON u.id = a3.userId AND a3.type = 2 WHERE u.id = :userId");
    queryGetUser.bindValue(":userId", userId.toInt());
    if (queryGetUser.exec() && queryGetUser.next()) {
        // Tes informations utlisateurs
        //qDebug() << queryGetUser.value("balance").toString();
        balance = queryGetUser.value("balance").toDouble();
        PELBalance = queryGetUser.value("balancePEL").toDouble();
        LCBalance = queryGetUser.value("balanceLC").toDouble();
        Sleep(3000);
        return;
    } else {
        // Gère tes erreurs ici Romain.

        qDebug() << "Erreur";
    }

    QSqlQuery query;
    query.prepare("SELECT firstname, lastname, dateOfBirth FROM users WHERE id = :userId");
    query.bindValue(":userId", this->m_userId);

    if (query.exec()) {
        if (query.next()) {
            QString firstName = query.value("firstname").toString();
            QString lastName = query.value("lastname").toString();
            QString dateOfBirthStr = query.value("dateOfBirth").toString();

            // Convertir la date de naissance dans le format désiré
            QDate dateOfBirth = QDate::fromString(dateOfBirthStr, "yyyy-MM-dd");
            QString formattedDateOfBirth = dateOfBirth.toString("dd.MM.yyyy");

            ui->labelFirstName_12->setText(firstName);
            ui->labelFirstAccountBalance_89->setText("Nom : " + lastName);
            ui->labelFirstAccountBalance_90->setText("Prénom : " + firstName); // Prénom
            ui->labelFirstAccountBalance_91->setText(formattedDateOfBirth); // Date de naissance

            // Maintenant, récupérons les soldes des comptes
            QSqlQuery accountQuery;
            accountQuery.prepare("SELECT type, balance FROM accounts WHERE user_id = :userId");
            accountQuery.bindValue(":userId", this->m_userId);

            if (accountQuery.exec()) {
                while (accountQuery.next()) {
                    int type = accountQuery.value("type").toInt();
                    QString accountBalance = accountQuery.value("balance").toString();

                    // Mettre à jour les étiquettes en fonction du type de compte
                    switch (type) {
                    case 0: // Compte courant
                        ui->labelFirstAccountBalance_96->setText(QString("Compte courant : %1").arg(balance));
                        break;
                    case 1: // PEL
                        ui->labelPELAccountBalance_12->setText(QString("PEL : %1").arg(PELBalance));
                        break;
                    case 2: // Livret C
                        ui->labelLCAccountBalance_12->setText(QString("Livret C : %1").arg(LCBalance));
                        break;
                    default:
                        qDebug() << "Type de compte inconnu pour l'utilisateur ID:" << this->m_userId;
                        break;
                    }
                }
            } else {
                qDebug() << "Erreur lors de la récupération des soldes des comptes :" << accountQuery.lastError().text();
            }

        } else {
            qDebug() << "Aucun utilisateur trouvé avec l'ID:" << this->m_userId;
        }
    } else {
        qDebug() << "Erreur lors de la récupération des informations de l'utilisateur :" << query.lastError().text();
    }
}
