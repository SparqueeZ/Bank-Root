#include "stagiaire_homepage.h"
#include "ui_stagiaire_homepage.h"

stagiaire_homepage::stagiaire_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stagiaire_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

stagiaire_homepage::~stagiaire_homepage()
{
    delete ui;
}

void stagiaire_homepage::on_reduced_st_clicked()
{
    showMinimized();
}


void stagiaire_homepage::on_close_st_clicked()
{
    close();
}


void stagiaire_homepage::on_fullscreen_st_clicked()
{

}


void stagiaire_homepage::on_consulter_st_clicked()
{

}


