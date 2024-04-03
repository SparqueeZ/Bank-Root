#include "choix_principal.h"
#include "ui_choix_principal.h"

choix_principal::choix_principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::choix_principal)
{
    ui->setupUi(this);
}

choix_principal::~choix_principal()
{
    delete ui;
}
