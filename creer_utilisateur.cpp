#include "creer_utilisateur.h"
#include "ui_creer_utilisateur.h"

creer_utilisateur::creer_utilisateur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_utilisateur)
{
    ui->setupUi(this);
}

creer_utilisateur::~creer_utilisateur()
{
    delete ui;
}