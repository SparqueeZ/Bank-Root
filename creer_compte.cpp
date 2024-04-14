#include "creer_compte.h"
#include "ui_creer_compte.h"

creer_compte::creer_compte(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_compte)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);


}

creer_compte::~creer_compte()
{
    delete ui;
}

void creer_compte::on_close_crcompte_clicked()
{
    close();
}


void creer_compte::on_reduced_crcompte_clicked()
{
    showMinimized();
}

void creer_compte::on_fullscreen_crcompte_clicked()
{

}

void creer_compte::on_return_crcompte_clicked()
{

}

void creer_compte::on_send_crcompte_clicked()
{

}
