#include "historique_stagiaire.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "qstandarditemmodel.h"
#include "ui_historique_stagiaire.h"
#include "qevent.h"
#include <QGuiApplication>
#include <synchapi.h>

historique_stagiaire::historique_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_stagiaire)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
}

historique_stagiaire::~historique_stagiaire()
{
    delete ui;
}

void historique_stagiaire::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_stagiaire::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_stagiaire::on_reduced_st_clicked()
{
    showMinimized();
}


void historique_stagiaire::on_close_st_clicked()
{
    close();
}


void historique_stagiaire::on_fullscreen_st_clicked()
{

}


void historique_stagiaire::on_lastconnect_st_clicked()
{

}


void historique_stagiaire::on_lastcons_st_clicked()
{

}

void historique_stagiaire::setUserInformations(User &user)
{
    // Récupération de la connexion existante à la base de données
    QSqlDatabase db = QSqlDatabase::database();

    int userToCheckPplId = user.getPpl_id() ? user.getPpl_id() : -1;
    int userToCheckPelId = user.getPel_id() ? user.getPel_id() : -1;
    int userToCheckLvcId = user.getLvc_id() ? user.getLvc_id() : -1;

    // Vérifier si la connexion à la base de données est valide
    if (db.isValid()) {
        // Exécuter la requête SQL pour récupérer les données de l'historique
        QSqlQuery query(db);
        query.prepare("SELECT * FROM history "
                      "WHERE id_compte_emetteur = :PPLAccountId OR id_compte_destinataire = :PPLAccountId "
                      "OR id_compte_emetteur = :PELAccountId OR id_compte_destinataire = :PELAccountId "
                      "OR id_compte_emetteur = :LVCAccountId OR id_compte_destinataire = :LVCAccountId "
                      "ORDER BY date ASC");
        query.bindValue(":PPLAccountId", userToCheckPplId);
        query.bindValue(":PELAccountId", userToCheckPelId);
        query.bindValue(":LVCAccountId", userToCheckLvcId);

        // Exécuter la requête
        if (query.exec()) {
            // Créer un QStandardItemModel pour stocker les données
            QStandardItemModel *model = new QStandardItemModel();

            // Ajouter les en-têtes de colonnes au modèle
            model->setHorizontalHeaderLabels(QStringList() << "Date" << "Type" << "Montant" << "Compte emetteur" << "Compte destinataire" << "Titre" << "Description");

            // Changer la couleur du texte des en-têtes de colonnes et des cellules
            ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->setStyleSheet("QTableView { color: white; }");

            int count = 0;

            // Itérer sur les résultats de la requête et ajouter chaque ligne au modèle
            while (query.next()) {
                count ++;
                // Récupérer les valeurs des colonnes
                double montant = query.value("montant").toDouble();
                QDateTime date = query.value("date").toDateTime();
                QString formattedDate = date.toString("dd/MM/yyyy - hh:mm:ss");
                int idCompteEmetteur = query.value("id_compte_emetteur").toInt();
                int idCompteDestinataire = query.value("id_compte_destinataire").toInt();
                int typeValue = query.value("type").toInt();
                QString title = query.value("title").toString();
                QString description = query.value("description").toString();
                QString type;
                switch (typeValue) {
                case 0:
                    type = "Virement";
                    break;
                case 1:
                    type = "Crédit";
                    break;
                case 2:
                    type = "Débit";
                    break;
                default:
                    type = "Inconnu";
                    break;
                }

                QString montantStr = QString::number(montant);
                QString idEmetteurStr = QString::number(idCompteEmetteur);
                QString idDestinataireStr = QString::number(idCompteDestinataire);

                // Créer les items correspondants et les ajouter au modèle
                QList<QStandardItem*> rowItems;
                rowItems.append(new QStandardItem(formattedDate));
                rowItems.append(new QStandardItem(type));
                rowItems.append(new QStandardItem(montantStr));
                rowItems.append(new QStandardItem(idEmetteurStr));
                rowItems.append(new QStandardItem(idDestinataireStr));
                rowItems.append(new QStandardItem(title));
                rowItems.append(new QStandardItem(description));
                model->appendRow(rowItems);
            }

            if (count == 0) {
                delete model;
                ui->tableView->setModel(nullptr);
                return;
            }

            ui->tableView->setModel(model);

        } else {
            qDebug() << "Erreur lors de l'exécution de la requête SQL:" << query.lastError().text();
        }
    }
}
