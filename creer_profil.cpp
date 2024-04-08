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

void creer_profil::on_reduced_2_clicked()
{
    showMinimized();
}


void creer_profil::on_toolButton_4_clicked()
{
    close();
}

