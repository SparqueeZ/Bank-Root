#include "login.h"
#include "admin_homepage.h"
#include "home.h"
#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "user.cpp"
#include "main.cpp"
#include "home.cpp"
#include <QMessageBox>
#include <QGuiApplication>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "admin_homepage.h"
#include "choix_principal.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
}

Login::~Login()
{
    delete ui;
}

void Login::mousePressEvent(QMouseEvent *event) {
    // Fenetre moovable
    cur_pos = event->globalPosition().toPoint();
}

void Login::mouseMoveEvent(QMouseEvent *event) {
    // Fenetre moovable
    new_pos = QPoint(event-> globalPosition().toPoint() - cur_pos );
    move(x()+new_pos.x(), y() + new_pos.y());
    cur_pos = event->globalPosition().toPoint();
}


QString getCurrentDateTimeForSQL() {
    // Récupérer l'heure actuelle
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Formater l'heure pour une requête SQL (format YYYY-MM-DD HH:MM:SS)
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    return formattedDateTime;
}


void Login::on_pushButton_clicked()
{
    
    QString username = ui->username->text();
    QString password = ui->password->text();
    User user;
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
    } else {
        if (user.signin(username, password)) {
            user.checkPELIncome(user.getPpl_id(), user.getPel_id(), user.getUserId());
            user.updateLastConnexion(user.getUserId());

            if (user.getRole() == 1) {
                // Ouvrir la page d'administration

                if (user.getPpl_id() || user.getPel_id() || user.getLvc_id()) {
                    choix_principal *choixPrincipal = new choix_principal();
                    choixPrincipal->setUserInformation(user);
                    choixPrincipal->show();
                    this->hide();
                } else {
                    admin_homepage *adminHome = new admin_homepage();
                    adminHome->setUserInformation(user);
                    adminHome->show();
                    this->hide();
                }


            } else {
                // Ouvrir la page d'accueil normale
                Home *home = new Home();
                home->setUserInformation(user); // Envoyer les informations de l'utilisateur à la page d'accueil
                home->show();
                this->hide();
            }
        } else  {
            // Afficher un message d'erreur si l'authentification a échoué
            QMessageBox::warning(this, "Erreur d'authentification", "Identifiants incorrects.");
        }
    }
}


void Login::on_toolButton_3_clicked()
{
    close();
}


void Login::on_reduced_clicked()
{
    showMinimized();
}

void Login::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

