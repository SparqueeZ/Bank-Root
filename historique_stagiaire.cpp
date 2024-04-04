#include "historique_stagiaire.h"
#include "ui_historique_stagiaire.h"

historique_stagiaire::historique_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_stagiaire)
{
    ui->setupUi(this);
}

historique_stagiaire::~historique_stagiaire()
{
    delete ui;
}
