#include "historique_stagiaire.h"
#include "ui_historique_stagiaire.h"

historique_stagiaire::historique_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_stagiaire)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

historique_stagiaire::~historique_stagiaire()
{
    delete ui;
}

void historique_stagiaire::on_reduced_st_clicked()
{
    showMinimized();
}


void historique_stagiaire::on_close_st_clicked()
{
    close();
}


void historique_stagiaire::on_fullscreen_st_clicked()
{

}


void historique_stagiaire::on_lastconnect_st_clicked()
{

}


void historique_stagiaire::on_lastcons_st_clicked()
{

}

void historique_stagiaire::setUserId(const QString &userId)
{

}
