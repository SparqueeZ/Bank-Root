#include "quel_stagiaire.h"
#include "historique_stagiaire.h"
#include "ui_quel_stagiaire.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "user.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayout>
#include <QEvent>
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

quel_stagiaire::quel_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_stagiaire)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_stagiaire::~quel_stagiaire()
{
    delete ui;
}

void quel_stagiaire::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_stagiaire::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_stagiaire::on_reduced_kist_clicked()
{
    showMinimized();
}


void quel_stagiaire::on_close_kist_clicked()
{
    close();
}

void quel_stagiaire::on_fullscreen_kist_clicked()
{

}


void quel_stagiaire::on_return_kist_clicked()
{
    close();
}


void quel_stagiaire::on_send_kist_clicked()
{
    // Récupérer le texte de la ligne de recherche
    QString searchQuery = ui->value->text().trimmed();

    // Vérifier si la recherche n'est pas vide
    if (!searchQuery.isEmpty()) {
        // Créer une instance de la classe User pour interagir avec la base de données
        User user;

        // Effectuer la requête pour rechercher les utilisateurs par nom
        QSqlQuery query;
        query.prepare("SELECT p.firstname, p.lastname, u.id "
                      "FROM users AS u "
                      "LEFT JOIN profil AS p ON (p.user_id = u.id AND p.type = 10) "
                      "WHERE p.firstname = :firstname");
        query.bindValue(":firstname", searchQuery);

        if (query.exec()) {
            // Effacer le contenu précédent de la liste
            QLayout *layout = ui->scrollArea->widget()->layout();
            if (layout) {
                QLayoutItem *child;
                while ((child = layout->takeAt(0)) != nullptr) {
                    delete child->widget();
                    delete child;
                }
            } else {
                layout = new QVBoxLayout();
                ui->scrollArea->widget()->setLayout(layout);
            }

            // Parcourir les résultats de la requête et afficher dans la liste
            while (query.next()) {
                QString userId = query.value("id").toString();
                QString firstName = query.value("firstname").toString();
                QString lastName = query.value("lastname").toString();

                // Créer un QPushButton pour afficher les informations de l'utilisateur
                QPushButton *button = new QPushButton(this);
                button->setText(QString("%1 %2 (ID: %3)").arg(firstName, lastName, userId));

                // Définir le style pour rendre le texte en blanc
                button->setStyleSheet("color: white;");

                // Connecter le signal clicked() du bouton à un slot pour gérer le clic
                connect(button, &QPushButton::clicked, this, [=]() {
                    qDebug() << "Bouton cliqué pour l'utilisateur ID:" << userId;
                    historique_stagiaire *HistoStagiaire = new historique_stagiaire();
                    HistoStagiaire->setUserId(userId);
                    HistoStagiaire->show();
                    close();
                });

                // Ajouter le QPushButton à la mise en page de la zone de défilement
                layout->addWidget(button);

                // Gérer l'effet de survol (hover)
                button->installEventFilter(this);
            }
        } else {
            qDebug() << "Erreur lors de la recherche des utilisateurs :" << query.lastError().text();
        }
    }
}

