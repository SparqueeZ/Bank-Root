#include "quel_stagiaire.h"
#include "ui_quel_stagiaire.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

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

void quel_stagiaire::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_stagiaire::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
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

