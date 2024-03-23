#include "login.h"
#include "home.h"
#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "user.cpp"
#include "main.cpp"
#include "home.cpp"
#include <QMessageBox>
#include <QGuiApplication>

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

void Login::on_toolButton_3_clicked()
{
    close();
}


void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_3->text(); // Récupérer le nom d'utilisateur depuis le champ de saisie
    QString password = ui->lineEdit_2->text(); // Récupérer le mot de passe depuis le champ de saisie

    if (username.isEmpty() || password.isEmpty()) {
        // Afficher un message d'erreur si les champs sont vides
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
    } else {
        // Créer une instance de la classe User
        User user;

        // Appeler la fonction logIn avec les identifiants récupérés depuis l'interface graphique
        if (user.logIn(username, password)) {
            // Connexion réussie, créer une nouvelle fenêtre NewMainWindow et l'afficher
            Home *home = new Home();
            home->show();

            // Cacher la fenêtre actuelle
            this->hide();
        } else {
            // Afficher un message d'erreur si l'authentification a échoué

        }
    }
}

void Login::on_reduced_clicked()
{
    showMinimized(); // Réduire la fenêtre
}

void Login::on_fullscreen_clicked()
{
    // Mettre la fenêtre à la taille de l'écran de l'ordinateur
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

