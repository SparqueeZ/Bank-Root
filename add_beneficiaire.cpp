#include "add_beneficiaire.h"
#include "ui_add_beneficiaire.h"
#include "user.h"
#include "home.h"
#include "qevent.h"
#include <QGuiApplication>


add_beneficiaire::add_beneficiaire(User *user, Home *parentHome, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::add_beneficiaire)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    currentUser = user;
}

add_beneficiaire::~add_beneficiaire()
{
    delete ui;
}

void add_beneficiaire::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void add_beneficiaire::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void add_beneficiaire::on_reduced_addb_clicked()
{
    showMinimized();
}

void add_beneficiaire::on_close_addb_clicked()
{
    close();
}

void add_beneficiaire::on_fullscreen_addb_clicked()
{

}

void add_beneficiaire::on_return_addb_clicked()
{
    close();
}

void add_beneficiaire::on_send_addb_clicked()
{
    QString value_addb = ui->value_addb->text();

    currentUser->addBeneficiaire(value_addb.toInt(), currentUser->getUserId());

    parentHome->refreshUserInfo();

    close();
}
