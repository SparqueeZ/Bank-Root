#include "credit_admin.h"
#include "home.h"
#include "operations.h"
#include "qevent.h"
#include "ui_credit_admin.h"

credit_admin::credit_admin(User *user, informations_client *parentHome, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::credit_admin)
    , currentUser(user)
    , parentHome(parentHome)
{
    ui->setupUi(this);
}

credit_admin::~credit_admin()
{
    delete ui;
}

void credit_admin::on_reduced_clicked()
{
    showMinimized();
}


void credit_admin::on_close_clicked()
{
    close();
}

void credit_admin::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void credit_admin::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void credit_admin::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}



void credit_admin::on_send_clicked()
{
    QString value = ui->credit_admin_value->text();
    Operations operations;
    qDebug() << currentUser->getPpl_id();
    operations.addBalance(value.toInt(), currentUser->getPpl_id(), "Credit Administrateur.");

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}

void credit_admin::on_return2_clicked()
{
    close();
}
