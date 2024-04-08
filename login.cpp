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
#include "admin_homepage.h"

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





void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_3->text();
    QString password = ui->lineEdit_2->text();
    User user;
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
    } else {
        if (user.signin(username, password)) {
            if (user.getRole() == 1) {
                // Ouvrir la page d'administration
                admin_homepage *adminHome = new admin_homepage();
                adminHome->setUserInformation(user); // Envoyer les informations de l'utilisateur à la page d'accueil admin
                adminHome->show();
                this->hide();
            } else {
                // Ouvrir la page d'accueil normale
                Home *home = new Home();
                home->setUserInformation(user); // Envoyer les informations de l'utilisateur à la page d'accueil
                home->show();
                this->hide();
            }
        } else  {
            // Afficher un message d'erreur si l'authentification a échoué
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

