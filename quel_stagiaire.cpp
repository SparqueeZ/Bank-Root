#include "quel_stagiaire.h"
#include "ui_quel_stagiaire.h"

quel_stagiaire::quel_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_stagiaire)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_stagiaire::~quel_stagiaire()
{
    delete ui;
}

void quel_stagiaire::on_reduced_kist_clicked()
{
    showMinimized();
}


void quel_stagiaire::on_close_kist_clicked()
{
    close();
}


void quel_stagiaire::on_fullscreen_kist_clicked()
{

}


void quel_stagiaire::on_return_kist_clicked()
{

}


void quel_stagiaire::on_send_kist_clicked()
{

}
