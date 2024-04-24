#include "virement.h"
#include "home.h"
#include "qevent.h"
#include "ui_virement.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "operations.h"
#include "qscreen.h"
#include <QGuiApplication>

virement::virement(User *user, Home *parentHome, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::virement)
    , parentHome(parentHome)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
    parentHome = dynamic_cast<Home*>(parent);
    if (!parentHome) {
        qDebug() << "Erreur : Le parent n'est pas une instance de la classe Home.";
        // Gérer l'erreur ici
    }

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    currentUser = user;

    // Assurez-vous que vous avez déjà une connexion à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Erreur : la connexion à la base de données n'est pas ouverte.";
        // Affichez un message d'erreur, mais ne retournez pas de valeur
    }

    // Préparation de la requête SQL
    QSqlQuery getBeneficiaires(db);
    getBeneficiaires.prepare("SELECT DISTINCT u_prop.id AS prop_uid, "
                             "a_dest.id AS dest_acc_id , p_dest.firstname AS dest_firstname, a_dest.type AS dest_acc_type "
                             "FROM saved_accounts AS sa "
                             "LEFT JOIN users AS u_prop ON u_prop.id = sa.user_id "
                             "LEFT JOIN accounts AS a_prop ON a_prop.userId = u_prop.id "
                             "LEFT JOIN accounts AS a_dest ON a_dest.id = sa.account_id "
                             "LEFT JOIN users AS u_dest ON u_dest.id = a_dest.userId "
                             "LEFT JOIN profil AS p_dest ON p_dest.user_id = u_dest.id "
                             "WHERE u_prop.id =  :userId");
    getBeneficiaires.bindValue(":userId", currentUser->getUserId());

    // Exécution de la requête
    if (!getBeneficiaires.exec()) {
        //        qDebug() << "Erreur lors de l'exécution de la requête :" << getBeneficiaires.lastError().text();
        // Affichez un message d'erreur, mais ne retournez pas de valeur
    }

    // Remplissage de la ComboBox avec les valeurs récupérées de la base de données
    while (getBeneficiaires.next()) {
        QString accountOwnerId = getBeneficiaires.value("dest_firstname").toString();
        QString accountId = getBeneficiaires.value("dest_acc_id").toString(); // Récupère l'ID de l'utilisateur
        ui->combo->addItem(accountOwnerId, accountId); // Ajoute le nom de l'utilisateur avec son ID dans la comboBox
    }

    QString selectedPropId;
    QSqlQuery getAccounts(db);

    getAccounts.prepare("SELECT type, id FROM accounts WHERE userId = :userId");

    getAccounts.bindValue(":userId", user->getUserId());
    if (!getAccounts.exec()) {
        //qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
        return;
    }

    while (getAccounts.next()) {
        QString accountOwnerId = getAccounts.value("type").toString();
        QString accountId = getAccounts.value("id").toString();

        if(accountOwnerId.toInt() == 0) {
            accountOwnerId = "Principal";
        } else if(accountOwnerId.toInt() == 1) {
            accountOwnerId = "PEL";
            continue;
        } else if(accountOwnerId.toInt() == 2) {
            accountOwnerId = "Livret C";
        }

        ui->comboBoxProp->addItem(accountOwnerId, accountId);
    }
}

virement::~virement()
{
    delete ui;
}

void virement::on_close_clicked()
{
    close();
}

void virement::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void virement::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void virement::on_send_clicked()
{
    Operations operations;
    QString montant = ui->value->text();
    QString idProprietaire = ui->comboBoxProp->currentData().toString();
    QString idDestinataire = ui->combo->currentData().toString();

    operations.virement(idProprietaire.toInt(), idDestinataire.toInt(), montant.toDouble());

    // Rafraîchissement des informations de l'utilisateur sur la page d'accueil
    parentHome->refreshUserInfo();

    close();
}


void virement::on_reduced_clicked()
{
    showMinimized();
}

void virement::on_return_2_clicked()
{
    close();
}
