#include "quel_employe.h"
#include "ui_quel_employe.h"
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

quel_employe::quel_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_employe::~quel_employe()
{
    delete ui;
}

void quel_employe::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_employe::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void quel_employe::on_reduced_kiem_clicked()
{
    showMinimized();
}


void quel_employe::on_close_kiem_clicked()
{
    close();
}


void quel_employe::on_fullscreen_kiem_clicked()
{

}


void quel_employe::on_return_kiem_clicked()
{

}


void quel_employe::on_send_kiem_clicked()
{

}
