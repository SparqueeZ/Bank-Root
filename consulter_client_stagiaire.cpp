#include "consulter_client_stagiaire.h"
#include "ui_consulter_client_stagiaire.h"

consulter_client_stagiaire::consulter_client_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::consulter_client_stagiaire)
{
    ui->setupUi(this);
}

consulter_client_stagiaire::~consulter_client_stagiaire()
{
    delete ui;
}
