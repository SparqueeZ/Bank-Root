#include "creer_utilisateur.h"
#include "f_admin.h"
#include "ui_creer_utilisateur.h"
#include "qsqlquery.h"

creer_utilisateur::creer_utilisateur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_utilisateur)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
    ui->type_utilisateur->addItem("Administrateur", 1);
    ui->type_utilisateur->addItem("Utilisateur", 0);


}

creer_utilisateur::~creer_utilisateur()
{
    delete ui;
}

void creer_utilisateur::on_reduced_cruser_clicked()
{
    showMinimized();
}


void creer_utilisateur::on_close_cruser_clicked()
{
    close();
}

void creer_utilisateur::on_fullscreen_cruser_clicked()
{

}

void creer_utilisateur::on_return_cruser_clicked()
{

}

void creer_utilisateur::on_send_cruser_clicked()
{
    f_admin admin;
    QString type_compte = ui->type_utilisateur->currentData().toString();
    QString firstname = ui->name_user->text();
    admin.createUser(firstname, type_compte.toInt());


    close();
}


