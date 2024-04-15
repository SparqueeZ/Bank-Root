#include "creer_compte.h"
#include "f_admin.h"
#include "ui_creer_compte.h"

creer_compte::creer_compte(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_compte)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
    ui->comboBox->addItem("Compte Courant", 0);
    ui->comboBox->addItem("Livret C", 2);
    ui->comboBox->addItem("PEL", 1);
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
    f_admin admin;
    QString type_compte = ui->comboBox->currentData().toString();
    QString userid = ui->userid->text();
    QString balance = ui->balance->text();
    admin.createAccount(userid.toInt(), type_compte.toInt(), balance.toInt());


    close();
}
