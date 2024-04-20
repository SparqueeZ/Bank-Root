#include "credit.h"
#include "ui_credit.h"
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

credit::credit(User *user, Home *parentHome, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::credit)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    parentHome = dynamic_cast<Home*>(parent);
    if (!parentHome) {
        qDebug() << "Erreur : Le parent n'est pas une instance de la classe Home.";
        // Gérer l'erreur ici
    }

    currentUser = user;
}

credit::~credit()
{
    delete ui;
}

void credit::on_reduced_clicked()
{
    showMinimized();
}


void credit::on_close_clicked()
{
    close();
}

void credit::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void credit::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void credit::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}



void credit::on_send_clicked()
{
    Home home;
    QString value = ui->value->text();
    Operations operations;
    operations.addBalance(value.toInt(), currentUser->getPpl_id(), "description a completer");

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}

void credit::on_return2_clicked()
{
    close();
}
