#include "creer_utilisateur.h"
#include "ui_creer_utilisateur.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

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

void creer_utilisateur::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void creer_utilisateur::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void creer_utilisateur::on_reduced_cruser_clicked()
{
    showMinimized();
}


void creer_utilisateur::on_close_cruser_clicked()
{
    close();
}

void creer_utilisateur::on_fullscreen_cruser_clicked()
{

}

void creer_utilisateur::on_return_cruser_clicked()
{

}

void creer_utilisateur::on_send_cruser_clicked()
{

}
