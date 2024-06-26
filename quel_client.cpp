#include "quel_client.h"
#include "informations_client.h"
#include "qsqlquery.h"
#include "ui_quel_client.h"
#include "user.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLayout>
#include <QEvent>
#include "qevent.h"
#include <QGuiApplication>

quel_client::quel_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_client::~quel_client()
{
    delete ui;
}

void quel_client::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_client::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_client::on_reduced_kiclient_clicked()
{
    showMinimized();
}


void quel_client::on_close_kiclient_clicked()
{
    close();
}


void quel_client::on_fullscreen_kiclient_clicked()
{

}


void quel_client::on_return_kiclient_clicked()
{
    close();
}

void quel_client::setUserInformations(User &user) {
    currentUser = &user;
}

void quel_client::on_send_kiclient_clicked()
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
                      "LEFT JOIN profil AS p ON (p.user_id = u.id AND p.type != 12) "
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
                    informations_client *InfoClient = new informations_client();
                    User userToCheck;
                    userToCheck.getInformations(userId.toInt());
                    User TheUser = *currentUser;
                    InfoClient->setUserInformations(TheUser, userToCheck);
                    InfoClient->show();
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
