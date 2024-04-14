#include "add_beneficiaire.h"
#include "ui_add_beneficiaire.h"
#include "user.h"
#include "qscreen.h"
#include "home.h"

add_beneficiaire::add_beneficiaire(User *user, Home *parentHome, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_beneficiaire)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

 currentUser = user;

}
add_beneficiaire::~add_beneficiaire()
{
    delete ui;
}

void add_beneficiaire::on_reduced_addb_clicked()
{
    showMinimized();
}


void add_beneficiaire::on_close_addb_clicked()
{
    close();
}


void add_beneficiaire::on_fullscreen_addb_clicked()
{

}

void add_beneficiaire::on_return_addb_clicked()
{
    close();
}

void add_beneficiaire::on_send_addb_clicked()
{
    Home home;
    QString value_addb = ui->value_addb->text();

    currentUser->addBeneficiaire(value_addb.toInt(),currentUser->getUserId());

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}
