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
    currentUser = user;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery getAccounts(db);

    getAccounts.prepare("SELECT type, id FROM accounts WHERE userId = :userId");

    getAccounts.bindValue(":userId", currentUser->getUserId());
    if (!getAccounts.exec()) {
        //qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
        return;
    }

    while (getAccounts.next()) {
        QString accountOwnerType = getAccounts.value("type").toString();
        QString accountId = getAccounts.value("id").toString();

        if(accountOwnerType.toInt() == 0) {
            accountOwnerType = "Principal";
        } else if(accountOwnerType.toInt() == 1) {
            accountOwnerType = "PEL";
            continue; // Eviter l'affihage du compte PEL
        } else if(accountOwnerType.toInt() == 2) {
            accountOwnerType = "Livret C";
        }

        ui->debit_acc_choice->addItem(accountOwnerType, accountId);
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
    Operations operations;

    QString amount = ui->value->text();
    int accountId = ui->debit_acc_choice->currentData().toInt();
    operations.removeBalance(amount.toInt(), accountId, "Description a completer.");

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}

void debit::on_return2_clicked()
{
    close();
}
