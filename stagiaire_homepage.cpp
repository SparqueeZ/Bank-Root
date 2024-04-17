#include "stagiaire_homepage.h"
#include "ui_stagiaire_homepage.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

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

void stagiaire_homepage::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void stagiaire_homepage::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
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
