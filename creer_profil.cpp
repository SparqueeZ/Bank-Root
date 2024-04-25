#include "creer_profil.h"
#include "f_admin.h"
#include "ui_creer_profil.h"
#include "qevent.h"
#include <QGuiApplication>

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

void creer_profil::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void creer_profil::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
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
    close();
}

void creer_profil::on_send_crprofil_clicked()
{
    f_admin admin;
    QString type_profil = ui->comboBox->currentData().toString();
    QString firstname = ui->firstname->text();
    QString userID = ui->userid->text();
    QString lastname = ui->lastname->text();
    QString login = ui->login->text();
    QString password = ui->password->text();

    User user;
    user.getInformations(userID.toInt());

    if (user.getRole() == 1) {
        ui->comboBox->addItem("Stagiaire", 10);
        ui->comboBox->addItem("Employé", 11);
        ui->comboBox->addItem("Directeur", 12);
    } else {
        ui->comboBox->addItem("Proprietaire", 0);
        ui->comboBox->addItem("Conjoint", 1);
    }

    if (ui->password->text()==""){
        user.generateRandomPassword();
        password = user.generateRandomPassword();
    }

    admin.createProfil(userID.toInt(), firstname, lastname, login, password, type_profil.toInt());
    close();
}

void creer_profil::on_userid_textChanged(const QString &arg1)
{
    if(ui->userid->text() != "") {
        ui->comboBox->clear();
        QString userID = ui->userid->text();
        User user;
        user.getInformations(userID.toInt());

        if (user.getRole() == 1) {
            ui->comboBox->addItem("Stagiaire", 10);
            ui->comboBox->addItem("Employé", 11);
            ui->comboBox->addItem("Directeur", 12);
        } else {
            ui->comboBox->addItem("Proprietaire", 0);
            ui->comboBox->addItem("Conjoint", 1);
        }
    }
}

