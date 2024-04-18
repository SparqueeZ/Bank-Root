#include "informations_client.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_informations_client.h"
#include <synchapi.h>
#include "qscreen.h"
#include "qevent.h"
#include <QGuiApplication>

informations_client::informations_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

informations_client::~informations_client()
{
    delete ui;
}

void informations_client::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void informations_client::on_reduced_infoc_clicked()
{
    showMinimized();
}


void informations_client::on_close_infoc_clicked()
{
    close();
}

void informations_client::on_fullscreen_infoc_clicked()
{

}

void informations_client::on_deco_infoc_clicked()
{

}

void informations_client::setUserId(const QString &userId)
{
    this->m_userId = userId;

    QSqlDatabase db = QSqlDatabase::database();

    User client;
    // Récuperer les informations de l'user via son ID.
    client.getInformations(userId.toInt());
    // Mettre les infos des comptes en banque
    ui->labelFirstAccountBalance_96->setText(QString("%1").arg(client.getPpl_balance()));
    ui->labelPELAccountBalance_12->setText(QString("%1").arg(client.getPel_balance()));
    ui->labelLCAccountBalance_12->setText(QString("%1").arg(client.getLvc_balance()));

    // Mettre les informations user
    ui->labelFirstAccountBalance_89->setText("Nom : " + client.getOwner_lastname());
    ui->labelFirstAccountBalance_90->setText("Prénom : " + client.getOwner_firstname());
    ui->labelFirstAccountBalance_91->setText("Date de naissance : " + client.getOwner_firstname()); // TODO : A changer par la date de naissance
    ui->labelFirstAccountBalance_94->setText(QString("ID de l'utilisateur : %1").arg(client.getUserId()));

    // Mettre les informations profils

}
