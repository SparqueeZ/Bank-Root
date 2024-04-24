#include "debit_admin.h"
#include "home.h"
#include "operations.h"
#include "qevent.h"
#include "qscreen.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_debit_admin.h"

debit_admin::debit_admin(User *user, informations_client *parentHome, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::debit_admin)
    , currentUser(user)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery getAccounts(db);

    getAccounts.prepare("SELECT type, id FROM accounts WHERE userId = :userId");
    getAccounts.bindValue(":userId", currentUser->getUserId());

    if (!getAccounts.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
        // Gérer l'erreur ici, par exemple en fermant la fenêtre de débit
        close();
        return;
    }

    while (getAccounts.next()) {
        QString accountOwnerType = getAccounts.value("type").toString();
        QString accountId = getAccounts.value("id").toString();

        if(accountOwnerType.toInt() == 0) {
            accountOwnerType = "Principal";
        } else if(accountOwnerType.toInt() == 1) {
            accountOwnerType = "PEL";
            continue;
        } else if(accountOwnerType.toInt() == 2) {
            accountOwnerType = "Livret C";
        }

        ui->debit_acc_choice->addItem(accountOwnerType, accountId);
    }
}

debit_admin::~debit_admin()
{
    delete ui;
}

void debit_admin::on_reduced_clicked()
{
    showMinimized();
}

void debit_admin::on_close_clicked()
{
    close();
}

void debit_admin::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void debit_admin::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void debit_admin::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}



void debit_admin::on_send_clicked()
{
    Home home;
    Operations operations;

    QString amount = ui->value->text();
    int accountId = ui->debit_acc_choice->currentData().toInt();
    operations.removeBalance(amount.toInt(), accountId, "Retrait administrateur.");

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}

void debit_admin::on_return2_clicked()
{
    close();
}

