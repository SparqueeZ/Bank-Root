#include "virement.h"
#include "ui_virement.h"
#include <QSqlDatabase>
#include <QSqlQuery>

virement::virement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::virement)
{
    ui->setupUi(this);

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

    // Création de la QComboBox

    // Remplissage de la ComboBox avec les valeurs récupérées de la base de données
    while (getBeneficiaires.next()) {
        QString accountOwnerId = getBeneficiaires.value("beneficiary_firstname").toString();
        ui->combo->addItem(accountOwnerId);
    }

    // Ajout de la ComboBox au layout de la fenêtre
    //ui->verticalLayout->addWidget(comboBox);
}

virement::~virement()
{
    delete ui;
}

