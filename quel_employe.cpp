#include "quel_employe.h"
#include "historique_employe.h"
#include "ui_quel_employe.h"
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

quel_employe::quel_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_employe::~quel_employe()
{
    delete ui;
}

void quel_employe::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_employe::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_employe::on_reduced_kiem_clicked()
{
    showMinimized();
}


void quel_employe::on_close_kiem_clicked()
{
    close();
}


void quel_employe::on_fullscreen_kiem_clicked()
{

}


void quel_employe::on_return_kiem_clicked()
{
    close();
}


void quel_employe::on_send_kiem_clicked()
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
                      "LEFT JOIN profil AS p ON (p.user_id = u.id AND p.type = 11) "
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
                    historique_employe *HistoEmploye = new historique_employe();
                    User userToCheck;
                    userToCheck.getInformations(userId.toInt());
                    HistoEmploye->setUserInformations(userToCheck);
                    HistoEmploye->show();
                    close();
                });

                // Ajouter le QPushButton à la mise en page de la zone de défilement
                layout->addWidget(button);

                // Gérer l'effet de survol (hover)
                button->installEventFilter(this);
            }
        } else {
        }
    }
}


