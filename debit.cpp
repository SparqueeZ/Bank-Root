#include "debit.h"
#include "ui_debit.h"
#include "qevent.h"
#include <QGuiApplication>
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#include "ui_home.h"
#include "user.h"
#include "operations.h"
#include "home.h"
#include "login.h"

debit::debit(User *user, Home *parentHome, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debit)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
    parentHome = dynamic_cast<Home*>(parent);
    if (!parentHome) {
        qDebug() << "Erreur : Le parent n'est pas une instance de la classe Home.";
        // Gérer l'erreur ici
    }
}

debit::~debit()
{
    delete ui;
}

void debit::on_reduced_clicked()
{
    showMinimized();
}


void debit::on_close_clicked()
{
    close();
}

void debit::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void debit::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void debit::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}



void debit::on_send_clicked()
{
    Home home;
    QString value = ui->value->text();
    Operations operations;
    operations.removeBalance(value.toInt(), currentUser->getUserId());

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}

void debit::on_return2_clicked()
{
    close();
}
