#include "creer_profil.h"
#include "ui_creer_profil.h"

creer_profil::creer_profil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_profil)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

creer_profil::~creer_profil()
{
    delete ui;
}

void creer_profil::on_close_crprofil_clicked()
{
    close();
}


void creer_profil::on_reduced_crprofil_clicked()
{
    showMinimized();
}

void creer_profil::on_fullscreen_crprofil_clicked()
{

}

void creer_profil::on_return_crprofil_clicked()
{

}

void creer_profil::on_send_crprofil_clicked()
{

}
