#include "historique_employe.h"
#include "ui_historique_employe.h"

historique_employe::historique_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_employe)
{
    ui->setupUi(this);
}

historique_employe::~historique_employe()
{
    delete ui;
}
