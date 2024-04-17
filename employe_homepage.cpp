#include "employe_homepage.h"
#include "ui_employe_homepage.h"
#include "qevent.h"
#include <QGuiApplication>

employe_homepage::employe_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::employe_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

employe_homepage::~employe_homepage()
{
    delete ui;
}

void employe_homepage::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void employe_homepage::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void employe_homepage::on_reduced_em_clicked()
{
    showMinimized();
}


void employe_homepage::on_close_em_clicked()
{
    close();
}

void employe_homepage::on_fullscreen_em_clicked()
{

}

void employe_homepage::on_logcl_em_clicked()
{

}

void employe_homepage::on_cruser_em_clicked()
{

}
void employe_homepage::on_associer_em_clicked()
{

}
void employe_homepage::on_crprofil_em_clicked()
{

}
void employe_homepage::on_crcompte_em_clicked()
{

}
