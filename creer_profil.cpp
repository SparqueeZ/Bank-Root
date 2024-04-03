#include "creer_profil.h"
#include "ui_creer_profil.h"

creer_profil::creer_profil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_profil)
{
    ui->setupUi(this);
}

creer_profil::~creer_profil()
{
    delete ui;
}
