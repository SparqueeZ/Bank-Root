#include "historique_employe.h"
#include "qboxlayout.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_historique_employe.h"
#include <synchapi.h>
#include "qevent.h"
#include <QGuiApplication>
#include <QTableView>
#include <QStandardItemModel>

historique_employe::historique_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

historique_employe::~historique_employe()
{
    delete ui;
}

void historique_employe::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_employe::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_employe::on_reduced_em_clicked()
{
    showMinimized();
}


void historique_employe::on_close_em_clicked()
{
    close();
}


void historique_employe::on_lastconnect_em_clicked()
{

}


void historique_employe::on_lastcons_em_clicked()
{

}

void historique_employe::on_lastop_em_clicked()
{

}



void historique_employe::on_fullscreen_em_clicked()
{

}

void historique_employe::setUserInformations(User &user)
{
    // Récupération de la connexion existante à la base de données
    QSqlDatabase db = QSqlDatabase::database();

    // Vérifier si la connexion à la base de données est valide
    if (db.isValid()) {
        // Exécuter la requête SQL pour récupérer les données de l'historique
        QSqlQuery query(db);
        query.prepare("SELECT * FROM history_admin "
                      "WHERE user_id = :userId "
                      "ORDER BY date ASC");
        query.bindValue(":userId", user.getUserId());

        // Exécuter la requête
        if (query.exec()) {
            // Créer un QStandardItemModel pour stocker les données
            QStandardItemModel *model = new QStandardItemModel();

            // Ajouter les en-têtes de colonnes au modèle
            model->setHorizontalHeaderLabels(QStringList() << "Date" << "Type" << "Description");

            // Changer la couleur du texte des en-têtes de colonnes et des cellules
            ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->setStyleSheet("QHeaderView::section { background-color: transparent; color: white; }");
            ui->tableView->setStyleSheet("QTableView { color: white; }");

            // Itérer sur les résultats de la requête et ajouter chaque ligne au modèle
            while (query.next()) {
                // Récupérer les valeurs des colonnes
                QDateTime date = query.value(2).toDateTime();
                QString formattedDate = date.toString("dd/MM/yyyy - hh:mm:ss");
                int typeValue = query.value(3).toInt();
                QString type;
                switch (typeValue) {
                case 0:
                    type = "Connexion";
                    break;
                case 1:
                    type = "Consultation";
                    break;
                case 2:
                    type = "Operation";
                    break;
                default:
                    type = "Inconnu";
                    break;
                }
                QString description = query.value(4).toString();

                // Créer les items correspondants et les ajouter au modèle
                QList<QStandardItem*> rowItems;
                rowItems.append(new QStandardItem(formattedDate));
                rowItems.append(new QStandardItem(type));
                rowItems.append(new QStandardItem(description));
                model->appendRow(rowItems);
            }

            // Ajouter le modèle au QTableView
            ui->tableView->setModel(model);

            // Ajuster la largeur des colonnes
            int totalWidth = ui->tableView->width();
            int column1Width = totalWidth * 0.1;
            int column2Width = totalWidth * 0.2; // Ajustez la largeur de la nouvelle colonne
            int column3Width = totalWidth * 0.65; // Ajustez la largeur de la colonne de description
            ui->tableView->setColumnWidth(0, column1Width);
            ui->tableView->setColumnWidth(1, column2Width);
            ui->tableView->setColumnWidth(2, column3Width);
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête SQL:" << query.lastError().text();
        }
    }
}

