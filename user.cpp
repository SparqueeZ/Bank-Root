#include "user.h"
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include <synchapi.h>

#include <QSettings>
#include <QDir>
#include <QSqlDatabase>
#include <QCoreApplication>

User::User() {}

User::User(
    int isLoggedIn,
    // User
    int userId,
    QString username,
    int role,
    QDate creationDate,
    // Profils
    int actual_profilId,
    int actual_type,
    QString actual_firstname,
    QString actual_lastname,
    QString actual_login,
    QString actual_password,
    QDate actual_dateOfBirth,
    // Proprietaire
    int owner_profilId,
    int owner_type,
    QString owner_firstname,
    QString owner_lastname,
    QString owner_login,
    QString owner_password,
    QDate owner_dateOfBirth,
    // Conjoint
    int coowner_profilId,
    int coowner_type,
    QString coowner_firstname,
    QString coowner_lastname,
    QString coowner_login,
    QString coowner_password,
    QDate coowner_dateOfBirth,
    // Accounts
    // Principal
    double ppl_balance,
    int ppl_id,
    double pel_balance,
    int pel_id,
    double lvc_balance,
    int lvc_id)
    :
    m_isLoggedIn(isLoggedIn),
    // User
    m_userId(userId),
    m_username(username),
    m_role(role),
    m_creationDate(creationDate),
    // Profils
    m_actual_profilId(actual_profilId),
    m_actual_type(actual_type),
    m_actual_firstname(actual_firstname),
    m_actual_lastname(actual_lastname),
    m_actual_login(actual_login),
    m_actual_dateOfBirth(actual_dateOfBirth),
    // Proprietaire
    m_owner_profilId(owner_profilId),
    m_owner_type(owner_type),
    m_owner_firstname(owner_firstname),
    m_owner_lastname(owner_lastname),
    m_owner_login(owner_login),
    m_owner_dateOfBirth(owner_dateOfBirth),
    // Conjoint
    m_coowner_profilId(coowner_profilId),
    m_coowner_type(coowner_type),
    m_coowner_firstname(coowner_firstname),
    m_coowner_lastname(coowner_lastname),
    m_coowner_login(owner_login),
    m_coowner_dateOfBirth(coowner_dateOfBirth),
    // Accounts
    // Principal
    m_ppl_balance(ppl_balance),
    m_ppl_id(ppl_id),
    m_pel_balance(pel_balance),
    m_pel_id(pel_id),
    m_lvc_balance(lvc_balance),
    m_lvc_id(lvc_id) {
}

bool User::signin(QString login, QString password) {
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString configFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("config.ini");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSettings settings(configFilePath, QSettings::IniFormat);
    db.setHostName("90.26.217.25");
    db.setUserName("test");
    db.setPassword("I-B*!O0vGqyFkMed");
    db.setDatabaseName("bank_root");
    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion a  la base de donnees :" << db.lastError().text();
        return false;
    };

    // Requete pour recuperer les informations de l'utilisateur
    QSqlQuery query;
    /*query.prepare("SELECT u.id AS id, u.firstname AS firstname, u.lastname AS lastname, u.dateOfBirth AS dateofbirth, u.role AS role, u.login AS login, a1.balance AS balance, a1.id AS firstAccountId, a2.balance AS balancePEL, a2.id AS PELAccountId, a3.balance AS balanceLC, a3.id AS LCAccountId "
                  "FROM users u "
                  "LEFT JOIN accounts a1 ON u.id = a1.userId AND a1.type = 0 "
                  "LEFT JOIN accounts a2 ON u.id = a2.userId AND a2.type = 1 "
                  "LEFT JOIN accounts a3 ON u.id = a3.userId AND a3.type = 2 "
                  "WHERE u.login = :login AND u.password = :password");*/
    query.prepare("SELECT "
                  "p.firstname AS p_firstname, "
                  "p.lastname AS p_lastname, "
                  "p.login AS p_login, "
                  "p.type AS p_type, "
                  "u.id AS userId, "
                  "u.username AS username, "
                  "u.role AS user_role, "
                  "u.creationDate AS user_creation_date, "
                  "ppl.balance AS ppl_balance, "
                  "ppl.id AS ppl_id, "
                  "pel.balance AS pel_balance, "
                  "pel.id AS pel_id, "
                  "lvc.balance AS lvc_balance, "
                  "lvc.id AS lvc_id "
                  "FROM users AS u "
                  "LEFT JOIN profil AS p ON p.user_id = u.id "
                  "LEFT JOIN accounts AS ppl ON p.user_id = ppl.userId AND ppl.type = 0 "
                  "LEFT JOIN accounts AS pel ON p.user_id = pel.userId AND pel.type = 1 "
                  "LEFT JOIN accounts AS lvc ON p.user_id = lvc.userId AND lvc.type = 2 "
                  "WHERE p.login = :login AND p.password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        // Utilisateur trouve
        m_isLoggedIn = 1;
        // Profils
        m_actual_firstname = query.value("p_firstname").toString();
        m_actual_lastname = query.value("p_lastname").toString();
        m_actual_login = query.value("p_login").toString();
        m_actual_type = query.value("p_type").toInt();

        // User
        m_username = query.value("username").toString();
        m_role = query.value("user_role").toInt();
        m_creationDate = query.value("user_creation_date").toDate();
        m_userId = query.value("userId").toInt();

        // Accounts
        m_ppl_balance = query.value("ppl_balance").toDouble();
        m_pel_balance = query.value("pel_balance").toDouble();
        m_lvc_balance = query.value("lvc_balance").toDouble();
        m_ppl_id = query.value("ppl_id").toInt();
        m_pel_id = query.value("pel_id").toInt();
        m_lvc_id = query.value("lvc_id").toInt();
        return true;
    } else {

        std::system("cls");
        qDebug() << "Erreur SQL : " << query.lastError().text();
        std::cout << "Identifiants incorrects" << std::endl;
        Sleep(1500);
        return false;
    }
}

void User::addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description){

    // Définir la date actuelle en tant que variable utilisable ici
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString date = currentDateTime.toString(Qt::ISODate);


    QSqlQuery addToHistory;
    addToHistory.prepare("INSERT INTO history"
                         "(montant, date, id_compte_emetteur, id_compte_destinataire, type, title, description)"
                         "VALUES (:montant, :date, :idCompteEmetteur, :idCompteRecepteur, :type, :title, :description)");
    addToHistory.bindValue(":montant", montant);
    addToHistory.bindValue(":date", date);
    addToHistory.bindValue(":idCompteEmetteur", idCompteEmetteur);
    if(idCompteRecepteur == 0) {
        addToHistory.bindValue(":idCompteRecepteur", NULL);
    } else {
        addToHistory.bindValue(":idCompteRecepteur", idCompteRecepteur);
    }
    addToHistory.bindValue(":type", type);
    addToHistory.bindValue(":title", title);
    addToHistory.bindValue(":description", description);
    // INSERT INTO `history`(`id_history`, `montant`, `date`, `id_compte_emetteur`, `id_compte_destinataire`, `type`, `title`, `description`) VALUES ('[value-1]','[value-2]','[value-3]','[value-4]','[value-5]','[value-6]','[value-7]','[value-8]')
    if (addToHistory.exec()) {
        // Afficher un message, ou return true.
        std::cout << "Ajout a l'historique effectue.";
        Sleep(3000);
    } else {
        // Gestion de l"erreur.
        std::cerr << "Erreur lors de l'ajout a l'historique : " << addToHistory.lastError().text().toStdString() << std::endl;
        Sleep(3000);
    }
}

void User::disconnect() {
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    // Réinitialiser les informations de l'utilisateur
    m_isLoggedIn = 0;
    // Profils
    m_owner_firstname.clear();
    m_owner_lastname.clear();
    m_owner_login.clear();
    m_owner_type = 0;
    m_coowner_firstname.clear();
    m_coowner_lastname.clear();
    m_coowner_login.clear();
    m_coowner_type = 0;
    // User
    m_username.clear();
    m_role = 0;
    m_creationDate.setDate(1000, 1, 1);

    // Accounts
    m_ppl_balance = 0;
    m_pel_balance = 0;
    m_lvc_balance = 0;
    m_ppl_id = 0;
    m_pel_id = 0;
    m_lvc_id = 0;

    system("cls");
}

void User::refreshUserData() {
    QSqlQuery query;
    query.prepare("SELECT "
                  "p.firstname AS p_firstname, "
                  "p.lastname AS p_lastname, "
                  "p.login AS p_login, "
                  "p.type AS p_type, "
                  "u.username AS username, "
                  "u.role AS user_role, "
                  "u.creationDate AS user_creation_date, "
                  "ppl.balance AS ppl_balance, "
                  "ppl.id AS ppl_id, "
                  "pel.balance AS pel_balance, "
                  "pel.id AS pel_id, "
                  "lvc.balance AS lvc_balance, "
                  "lvc.id AS lvc_id "
                  "FROM users AS u "
                  "LEFT JOIN profil AS p ON p.user_id = u.id "
                  "LEFT JOIN accounts AS ppl ON p.user_id = ppl.userId AND ppl.type = 0 "
                  "LEFT JOIN accounts AS pel ON p.user_id = pel.userId AND pel.type = 1 "
                  "LEFT JOIN accounts AS lvc ON p.user_id = lvc.userId AND lvc.type = 2 "
                  "WHERE u.id = :userId");
    query.bindValue(":userId", m_userId);
    if (query.exec() && query.next()) {
        // Utilisateur trouve
        // Accounts
        m_ppl_balance = query.value("ppl_balance").toDouble();
        m_pel_balance = query.value("pel_balance").toDouble();
        m_lvc_balance = query.value("lvc_balance").toDouble();
        return;
    } else {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        std::cout << "Erreur lors de la mise a jour des donnees." << std::endl;
        Sleep(1500);
        return;
    }
}

void User::addBeneficiaire(int beneficiaireId, int propId) {
    // Verification si l'identifiant du beneficiaire existe.
    QSqlQuery idCheckQuery;
    idCheckQuery.prepare("SELECT COUNT(*) FROM accounts WHERE id = :beneficiaireId");
    idCheckQuery.bindValue(":beneficiaireId", beneficiaireId);
    if (!idCheckQuery.exec()) {
        qDebug() << "Erreur lors de la verification de l'identifiant du beneficiaire :" << idCheckQuery.lastError().text();
        Sleep(2000);
        return;
    }
    idCheckQuery.next();
    int idCount = idCheckQuery.value(0).toInt();
    if (idCount == 0) {
        std::cout << "L'identifiant du beneficiaire n'existe pas.";
        Sleep(2000);
        return;
    }

    // Verification si le beneficiaire est deja ajoute au compte.
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM saved_accounts WHERE user_id = :propId AND account_id = :beneficiaireId");
    checkQuery.bindValue(":propId", propId);
    checkQuery.bindValue(":beneficiaireId", beneficiaireId);
    if (!checkQuery.exec()) {
        qDebug() << "Erreur lors de la verification du beneficiaire existant :" << checkQuery.lastError().text();
        return;
    }
    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count > 0) {
        std::cout << "Le beneficiaire est deja ajoute a ce compte.";
        Sleep(2000);
        return;
    }

    // Insertion du beneficiaire dans la table added_beneficiaires.
    QSqlQuery query;
    query.prepare("INSERT INTO saved_accounts (user_id, account_id) VALUES (:user_id, :account_id)");
    query.bindValue(":user_id", propId);
    query.bindValue(":account_id", beneficiaireId);

    //std::cout << propId << beneficiaireId;
    //Sleep(2000);

    if (query.exec()) {
        std::cout << "Beneficiaire ajoute avec succes.";
        Sleep(2000);
    } else {
        qDebug() << "Erreur lors de l'insertion du beneficiaire :" << query.lastError().text();
        Sleep(5000);
    }
}

int User::checkIfProfileExists(int userId) {
    // Récupération de la connexion existante à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid()) {
        QSqlQuery query(db);
        query.prepare("SELECT pro.id AS pro_id, con.id AS con_id, sta.id AS sta_id, emp.id AS emp_id, dir.id AS dir_id "
                      "FROM users AS u "
                      "LEFT JOIN profil AS pro ON pro.user_id = u.id AND pro.type = 0 "
                      "LEFT JOIN profil AS con ON con.user_id = u.id AND con.type = 1 "
                      "LEFT JOIN profil AS sta ON sta.user_id = u.id AND sta.type = 10 "
                      "LEFT JOIN profil AS emp ON emp.user_id = u.id AND emp.type = 11 "
                      "LEFT JOIN profil AS dir ON dir.user_id = u.id AND dir.type = 12 "
                      "WHERE u.id = :userId");
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            std::cout << "Erreur lors de l'execution de la requete : " << query.lastError().text().toStdString() << std::endl;
            Sleep(3000);
            return -2;
        }

        if (query.next()) {
            if(query.value("con_id") != NULL && query.value("pro_id") != NULL) {
                return -1; // Prop. et Con. remplis
            } else if (query.value("con_id") == NULL && query.value("pro_id") == NULL) {
                return 0; // Prop. et Con. vides
            } else if(query.value("pro_id") != NULL) {
                return 1; // Prop. rempli
            } else if (query.value("con_id") != NULL) {
                return 2; // Con. rempli
            } else if (query.value("sta_id") != NULL) {
                return 10; // Sta. rempli
            } else if (query.value("emp_id") != NULL) {
                return 11; // Emp. rempli
            } else if (query.value("dir_id") != NULL) {
                return 12; // Dir. rempli
            }
            return -2;

        }
    }
    return -1;
}

bool User::checkIfUserIsAdmin(int userId) {
    // Récupération de la connexion existante à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid()) {
        QSqlQuery query(db);
        // TODO : A update pour la table users
        query.prepare("SELECT role FROM users WHERE id = :userId");
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            std::cout << "Erreur lors de l'execution de la requete : " << query.lastError().text().toStdString() << std::endl;
            return false;
        }

        if (query.next() && query.value("role") == 1) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

int User::createUser(QString username, int role){
    // Créer l'utilisateur
    QSqlQuery insertUserQuery;
    insertUserQuery.prepare("INSERT INTO users (username, role) VALUES (:username, :role)");
    insertUserQuery.bindValue(":username", username);
    insertUserQuery.bindValue(":role", role);

    if (insertUserQuery.exec()){
        return insertUserQuery.lastInsertId().toInt();
    } else {
        qDebug() << "Erreur lors de la création de l'utilisateur :" << insertUserQuery.lastError().text();
        return 0;
    }
}

bool User::createAccount(int userId, int type, double balance){
    // Créer le compte bancaire
    QSqlQuery insertAccountQuery;
    insertAccountQuery.prepare("INSERT INTO accounts (userId, type, balance) "
                            "VALUES (:userId, :type, :balance)");
    insertAccountQuery.bindValue(":userId", userId);
    insertAccountQuery.bindValue(":type", type);
    insertAccountQuery.bindValue(":balance", balance);

    if(insertAccountQuery.exec()){
        return true;
    } else {
        return false;
    }
};

bool User::createProfil(int userId, QString firstname, QString lastname, QString login, QString password, int type){
    // Créer le profil
    QSqlQuery insertProfilQuery;
    insertProfilQuery.prepare("INSERT INTO profil (user_id, firstname, lastname, login, password, type) "
                               "VALUES (:userId, :firstname, :lastname, :login, :password, :type)");
    insertProfilQuery.bindValue(":userId", userId);
    insertProfilQuery.bindValue(":firstname", firstname);
    insertProfilQuery.bindValue(":lastname", lastname);
    insertProfilQuery.bindValue(":login", login);
    insertProfilQuery.bindValue(":password", password);
    insertProfilQuery.bindValue(":type", type);

    if(insertProfilQuery.exec()){
        return true;
    } else {
        return false;
    }
};

void User::getInformations(int userId) {
    // Requete pour recuperer les informations de l'utilisateur
    QSqlQuery query;
    //query.prepare("SELECT u.id AS id, u.firstname AS firstname, u.lastname AS lastname, u.login AS login, u.type AS profilType, a1.balance AS balance, a1.id AS firstAccountId, a2.balance AS balancePEL, a2.id AS PELAccountId, a3.balance AS balanceLC, a3.id AS LCAccountId FROM profil AS u LEFT JOIN accounts a1 ON u.id = a1.userId AND a1.type = 0 LEFT JOIN accounts a2 ON u.id = a2.userId AND a2.type = 1 LEFT JOIN accounts a3 ON u.id = a3.userId AND a3.type = 2 WHERE u.id = 1");
    query.prepare(  "SELECT "
                        "p1.firstname AS p1_firstname, "
                        "p1.lastname AS p1_lastname, "
                        "p1.login AS p1_login, "
                        "p1.type AS p1_type, "
                        "p1.id AS p1_id, "
                        "p2.firstname AS p2_firstname, "
                        "p2.lastname AS p2_lastname, "
                        "p2.login AS p2_login, "
                        "p2.type AS p2_type, "
                        "p2.id AS p2_id, "
                        "u.id AS userId, "
                        "u.username AS username, "
                        "u.role AS user_role, "
                        "u.creationDate AS user_creation_date, "
                        "ppl.balance AS ppl_balance, "
                        "ppl.id AS ppl_id, "
                        "pel.balance AS pel_balance, "
                        "pel.id AS pel_id, "
                        "lvc.balance AS lvc_balance, "
                        "lvc.id AS lvc_id "
                    "FROM users AS u "
                    "LEFT JOIN profil AS p1 ON p1.user_id = u.id AND p1.type = 0 "
                    "LEFT JOIN profil AS p2 ON p2.user_id = u.id AND p2.type = 1 "
                    "LEFT JOIN accounts AS ppl ON p1.user_id = ppl.userId AND ppl.type = 0 "
                    "LEFT JOIN accounts AS pel ON p1.user_id = pel.userId AND pel.type = 1 "
                    "LEFT JOIN accounts AS lvc ON p1.user_id = lvc.userId AND lvc.type = 2 "
                    "WHERE u.id = :userId");
    query.bindValue(":userId", userId);
    if (query.exec() && query.next()) {
        // Utilisateur trouve

        // Profils
        m_owner_firstname = query.value("p1_firstname").toString();
        m_owner_lastname = query.value("p1_lastname").toString();
        m_owner_login = query.value("p1_login").toString();
        m_owner_type = query.value("p1_type").toInt();
        m_owner_profilId = query.value("p1_id").toInt();
        m_coowner_firstname = query.value("p2_firstname").toString();
        m_coowner_lastname = query.value("p2_lastname").toString();
        m_coowner_login = query.value("p2_login").toString();
        m_coowner_type = query.value("p2_type").toInt();
        m_coowner_profilId = query.value("p2_id").toInt();

        // User
        m_username = query.value("username").toString();
        m_role = query.value("user_role").toInt();
        m_creationDate = query.value("user_creation_date").toDate();
        m_userId = query.value("userId").toInt();

        // Accounts
        m_ppl_balance = query.value("ppl_balance").toDouble();
        m_pel_balance = query.value("pel_balance").toDouble();
        m_lvc_balance = query.value("lvc_balance").toDouble();
        m_ppl_id = query.value("ppl_id").toInt();
        m_pel_id = query.value("pel_id").toInt();
        m_lvc_id = query.value("lvc_id").toInt();
        return;
    } else {
        std::system("cls");
        std::cout << "User not found." << userId << std::endl;
        Sleep(1500);
        return;
    }
}

QString User::generateAccountNumber() const {
    QRandomGenerator generator(QDateTime::currentMSecsSinceEpoch());
    int randomNumber = generator.bounded(10000);
    QString accountNumber = QString::number(randomNumber).rightJustified(4, '0');
    return accountNumber;
}

QString User::generateRandomPassword() const {
    QRandomGenerator generator(QDateTime::currentMSecsSinceEpoch() + 1);
    int randomNumber = generator.bounded(1000000);
    QString randomPassword = QString::number(randomNumber).rightJustified(6, '0');
    return randomPassword;
}

bool User::isAdmin(const QString& login) const {
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE login = :login");
    query.bindValue(":login", login);
    if (query.exec() && query.next()) {
        int role = query.value("role").toInt();
        return (role == 1);
    } else {
        qDebug() << "Erreur lors de la recuperation du role de l'utilisateur :" << query.lastError().text();
        return false;
    }
}

User User::getLoggedInUser() const {
    return *this;
}
int User::getIsLoggedIn() const {
    return m_isLoggedIn;
}

/*void User::setCredentials(const QString& username, const QString& password) {
    m_login = username;
    m_password = password;
}*/

// User getters
int User::getUserId() const {
    return m_userId;
}

QString User::getUsername() const {
    return m_username;
}

int User::getRole() const {
    return m_role;
}

QDate User::getCreationDate() const {
    return m_creationDate;
}
// Actual User infos
int User::getActual_profilId() const {
    return m_actual_profilId;
}

int User::getActual_type() const {
    return m_actual_type;
}

QString User::getActual_login() const {
    return m_actual_login;
}

QString User::getActual_firstname() const {
    return m_actual_firstname;
}

QString User::getActual_lastname() const {
    return m_actual_lastname;
}

QDate User::getActual_dateOfBirth() const {
    return m_actual_dateOfBirth;
}

// ProfilProprietaire getters
int User::getOwner_profilId() const {
    return m_owner_profilId;
}

int User::getOwner_type() const {
    return m_owner_type;
}

QString User::getOwner_login() const {
    return m_owner_login;
}

QString User::getOwner_firstname() const {
    return m_owner_firstname;
}

QString User::getOwner_lastname() const {
    return m_owner_lastname;
}

QDate User::getOwner_dateOfBirth() const {
    return m_owner_dateOfBirth;
}

// ProfilConjoint getters
int User::getCoowner_profilId() const {
    return m_coowner_profilId;
}

int User::getCoowner_type() const {
    return m_coowner_type;
}

QString User::getCoowner_login() const {
    return m_coowner_login;
}

QString User::getCoowner_firstname() const {
    return m_coowner_firstname;
}

QString User::getCoowner_lastname() const {
    return m_coowner_lastname;
}

QDate User::getCoowner_dateOfBirth() const {
    return m_coowner_dateOfBirth;
}

// AccountPrincipal getters
double User::getPpl_balance() const {
    return m_ppl_balance;
}

int User::getPpl_id() const {
    return m_ppl_id;
}

// AccountPEL getters
double User::getPel_balance() const {
    return m_pel_balance;
}

int User::getPel_id() const {
    return m_pel_id;
}

// AccountLVC getters
double User::getLvc_balance() const {
    return m_lvc_balance;
}

int User::getLvc_id() const {
    return m_lvc_id;
}
