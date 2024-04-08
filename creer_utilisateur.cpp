#include "creer_utilisateur.h"
#include "ui_creer_utilisateur.h"

creer_utilisateur::creer_utilisateur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_utilisateur)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

creer_utilisateur::~creer_utilisateur()
{
    delete ui;
}

void creer_utilisateur::on_reduced_2_clicked()
{
    showMinimized();
}


void creer_utilisateur::on_toolButton_4_clicked()
{
    close();
}

