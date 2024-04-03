#include "consulter_client_stagiaire.h"
#include "ui_consulter_client_stagiaire.h" // Assurez-vous d'inclure ce fichier

consulter_client_stagiaire::consulter_client_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::consulter_client_stagiaire()) // Initialisez ui avec une nouvelle instance
{
    ui->setupUi(this); // Appelez setupUi() sur le pointeur ui initialisé
}

consulter_client_stagiaire::~consulter_client_stagiaire()
{
    delete ui;
}
