#include "creer_compte.h"
#include "ui_creer_compte.h"
#include "user.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

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

void creer_compte::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void creer_compte::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
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
