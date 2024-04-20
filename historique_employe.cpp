#include "historique_employe.h"
#include "ui_historique_employe.h"
#include <synchapi.h>
#include "qevent.h"
#include <QGuiApplication>

historique_employe::historique_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

historique_employe::~historique_employe()
{
    delete ui;
}

void historique_employe::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_employe::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void historique_employe::on_reduced_em_clicked()
{
    showMinimized();
}


void historique_employe::on_close_em_clicked()
{
    close();
}


void historique_employe::on_lastconnect_em_clicked()
{

}


void historique_employe::on_lastcons_em_clicked()
{

}

void historique_employe::on_lastop_em_clicked()
{

}



void historique_employe::on_fullscreen_em_clicked()
{

}


void historique_employe::setUserId(const QString &userId)
{

}
