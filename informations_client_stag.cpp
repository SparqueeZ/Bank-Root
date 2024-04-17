#include "informations_client_stag.h"
#include "ui_informations_client_stag.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>
#include "qscreen.h"

informations_client_stag::informations_client_stag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client_stag)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

informations_client_stag::~informations_client_stag()
{
    delete ui;
}

void informations_client_stag::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client_stag::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client_stag::on_reduced_infost_clicked()
{
    showMinimized();
}


void informations_client_stag::on_close_infost_clicked()
{
    close();
}

void informations_client_stag::on_fullscreen_infost_clicked()
{

}

void informations_client_stag::on_deco_infost_clicked()
{

}
