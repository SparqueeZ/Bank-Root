#include "choix_principal.h"
#include "ui_choix_principal.h"
#include "admin_homepage.h"
#include "home.h"
#include "qevent.h"

choix_principal::choix_principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::choix_principal)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

choix_principal::~choix_principal()
{
    delete ui;
}

void choix_principal::on_personnel_clicked() {
    Home *home = new Home();
    home->setUserInformation(currentUser); // Envoyer les informations de l'utilisateur à la page d'accueil
    home->show();
    this->hide();
}

void choix_principal::on_admin_clicked(){
    admin_homepage *adminHome = new admin_homepage(currentUser);
    adminHome->setUserInformation(currentUser);
    adminHome->show();
    this->hide();
}

void choix_principal::setUserInformation(const User& user) {
    currentUser = user;
}
