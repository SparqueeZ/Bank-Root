#include "virement.h"
#include "qevent.h"
#include "ui_virement.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "operations.h"

virement::virement(User *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::virement)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

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
    QSqlQuery getBeneficiaires;
    getBeneficiaires.prepare("SELECT "
                             "u.firstname AS prop_firstname, "
                             "ab.beneficiaire_id, "
                             "a.type, "
                             "u_beneficiary.firstname AS beneficiary_firstname, "
                             "a_beneficiary.userId AS beneficiary_user_id "
                             "FROM added_beneficiaires AS ab "
                             "JOIN accounts AS a ON ab.beneficiaire_id = a.id "
                             "JOIN users AS u ON u.id = ab.prop_id "
                             "JOIN accounts AS a_beneficiary ON ab.beneficiaire_id = a_beneficiary.id "
                             "JOIN users AS u_beneficiary ON a_beneficiary.userId = u_beneficiary.id "
                             "WHERE u.id = :userId");

    // Liaison de la valeur de l'ID utilisateur à la requête
    getBeneficiaires.bindValue(":userId", 1);

    // Exécution de la requête
    if (!getBeneficiaires.exec()) {
        //        qDebug() << "Erreur lors de l'exécution de la requête :" << getBeneficiaires.lastError().text();
        // Affichez un message d'erreur, mais ne retournez pas de valeur
    }

    // Remplissage de la ComboBox avec les valeurs récupérées de la base de données
    while (getBeneficiaires.next()) {
        QString accountOwnerId = getBeneficiaires.value("beneficiary_firstname").toString();
        QString accountId = getBeneficiaires.value("beneficiary_user_id").toString(); // Récupère l'ID de l'utilisateur
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

void virement::on_toolButton_3_clicked()
{
    close();
}

void virement::mousePressEvent(QMouseEvent *event) {
    if (ui->widget_7->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void virement::mouseMoveEvent(QMouseEvent *event) {
    if (ui->widget_7->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void virement::on_Envoyer_clicked()
{
    Operations operations;
    QString montant = ui->lineEdit->text();
    QString idProprietaire = ui->comboBoxProp->currentData().toString();
    QString idDestinataire = ui->combo->currentData().toString();

    //qDebug() << idProprietaire << idDestinataire << montant ;
    operations.virement(idProprietaire.toInt(), idDestinataire.toInt(), montant.toDouble());
    close();
}

