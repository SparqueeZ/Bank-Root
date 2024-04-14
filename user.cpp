#include "user.h"
#include "operations.h"
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

User::User(const QString& login, const QString& username, const QString& lastName, const QString& firstName, const QDate& dateOfBirth, double balance, int isLoggedIn, int role, double PELBalance, double LCBalance, int firstAccountId, int PELAccountId, int LCAccountId, int userId)
    : m_role(role), m_login(login), m_lastName(lastName), m_firstName(firstName), m_dateOfBirth(dateOfBirth), m_balance(balance), m_PELBalance(PELBalance), m_LCBalance(LCBalance), m_isLoggedIn(isLoggedIn), m_firstAccountId(firstAccountId), m_PELAccountId(PELAccountId), m_LCAccountId(LCAccountId), m_userId(userId) {
}
/*
int User::getprofil(QString login, QString password) {
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

    QSqlQuery query;
    query.prepare("SELECT type FROM profil WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    int profil1 = -1;
    int profil2 = -1;
    int profil3 = -1;
    while (query.next)
}

*/
//lol

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
    query.prepare("SELECT u.id AS id, u.role AS role, "
                  "p.firstname AS firstname, p.lastname AS lastname, p.type AS type, p.login AS login, "
                  "a1.balance AS balance, a1.id AS firstAccountId, "
                  "a2.balance AS balancePEL, a2.id AS PELAccountId, "
                  "a3.balance AS balanceLC, a3.id AS LCAccountId "
                  "FROM profil p "
                  "LEFT JOIN users u ON p.user_id = u.id "
                  "LEFT JOIN accounts a1 ON u.id = a1.userId AND a1.type = 0 "
                  "LEFT JOIN accounts a2 ON u.id = a2.userId AND a2.type = 1 "
                  "LEFT JOIN accounts a3 ON u.id = a3.userId AND a3.type = 2 "
                  "WHERE p.login = :login AND p.password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        // Utilisateur trouve
        m_firstName = query.value("firstname").toString();
        m_lastName = query.value("lastname").toString();
        m_balance = query.value("balance").toDouble();
        m_login = query.value("login").toString();
        m_role = query.value("role").toInt();
        m_isLoggedIn = 1;

        m_PELBalance = query.value("balancePEL").toDouble();
        m_LCBalance = query.value("balanceLC").toDouble();

        m_firstAccountId = query.value("firstAccountId").toInt();
        m_PELAccountId = query.value("PELAccountId").toInt();
        m_LCAccountId = query.value("LCAccountId").toInt();

        //TODO: Récupérer les usernames

        m_userId = query.value("id").toInt();
        return true;
    } else {
        std::system("cls");
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
    m_firstName.clear();
    m_lastName.clear();
    m_balance = 0;
    m_PELBalance = 0;
    m_LCBalance = 0;
    m_login.clear();
    m_isLoggedIn = 0;

    system("cls");
}

void User::refreshUserData() {
    QSqlQuery query;
    query.prepare("SELECT u.id AS id, u.role AS role, "
                  "p.firstname AS firstname, p.lastname AS lastname, p.login AS login, "
                  "a1.balance AS balance, a1.id AS firstAccountId, "
                  "a2.balance AS balancePEL, "
                  "a3.balance AS balanceLC "
                  "FROM profil p "
                  "LEFT JOIN users u ON p.user_id = u.id "
                  "LEFT JOIN accounts a1 ON u.id = a1.userId AND a1.type = 0 "
                  "LEFT JOIN accounts a2 ON u.id = a2.userId AND a2.type = 1 "
                  "LEFT JOIN accounts a3 ON u.id = a3.userId AND a3.type = 2 "
                  "WHERE u.id = :userId");
    query.bindValue(":userId", m_userId);

    if (query.exec() && query.next()) {
        m_firstName = query.value("firstname").toString();
        m_lastName = query.value("lastname").toString();
        m_balance = query.value("balance").toDouble();
        m_PELBalance = query.value("balancePEL").toDouble();
        m_LCBalance = query.value("balanceLC").toDouble();

    } else {
        qDebug() << "Erreur lors de la mise a jour des donnaes de l'utilisateur :" << query.lastError().text();
        Sleep(5000);
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
    checkQuery.prepare("SELECT COUNT(*) FROM added_beneficiaires WHERE prop_id = :propId AND beneficiaire_id = :beneficiaireId");
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
    query.prepare("INSERT INTO added_beneficiaires (prop_id, beneficiaire_id) VALUES (:propId, :beneficiaireId)");
    query.bindValue(":propId", propId);
    query.bindValue(":beneficiaireId", beneficiaireId);

    std::cout << propId << beneficiaireId;
    Sleep(2000);

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
                      "FROM newusers AS u "
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
        // TODO : A update pour la table newusers
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

// A Supprimer
/*
void User::createAccount() {
    QTextStream stream(stdin);
    Operations operations;

    // Demander les informations nécessaires pour créer un compte.
    std::cout << "Nom du client :";
    QString clientLastname = stream.readLine().trimmed();
    std::cout << "Prenom du client : ";
    QString clientFirstname = stream.readLine().trimmed();
    std::cout << "Date de naissance du client (format : YYYY-MM-DD) : ";
    QString clientDateOfBirth = stream.readLine().trimmed();

    // Générer un numéro de compte aléatoire
    QString accountNumber = generateAccountNumber();
    QString randomPassword = generateRandomPassword();

    QSqlQuery insertUserQuery;
    QSqlQuery insertAccountQuery;
    QSqlQuery getIdQuery;

    // Créer l'utilisateur
    insertUserQuery.prepare("INSERT INTO users (login, lastname, firstname, dateOfBirth, password) "
                            "VALUES (:login, :lastName, :firstName, :dateOfBirth, :password)");
    insertUserQuery.bindValue(":login", clientFirstname);
    insertUserQuery.bindValue(":lastName", clientLastname);
    insertUserQuery.bindValue(":firstName", clientFirstname);
    insertUserQuery.bindValue(":dateOfBirth", clientDateOfBirth);
    insertUserQuery.bindValue(":password", randomPassword);

    if (!insertUserQuery.exec()) {
        std::cout << "Erreur lors de la creation de l'utilisateur : " << insertUserQuery.lastError().text().toStdString() << std::endl;
        return;
    }

    // Récupérer l'ID de l'utilisateur nouvellement créé
    getIdQuery.prepare("SELECT id FROM users WHERE login = :login");
    getIdQuery.bindValue(":login", clientFirstname);
    if (!getIdQuery.exec() || !getIdQuery.next()) {
        std::cout << "Erreur lors de la recuperation de l'ID de l'utilisateur : " << getIdQuery.lastError().text().toStdString() << std::endl;
        return;
    }
    int userId = getIdQuery.value(0).toInt();

    // Créer le compte
    insertAccountQuery.prepare("INSERT INTO accounts (id, userId, balance) "
                               "VALUES (:id, :userId, :balance)");
    insertAccountQuery.bindValue(":id", accountNumber);
    insertAccountQuery.bindValue(":userId", userId);
    insertAccountQuery.bindValue(":balance", 0);

    if (!insertAccountQuery.exec()) {
        std::cout << "Erreur lors de la creation du compte : " << insertAccountQuery.lastError().text().toStdString() << std::endl;
        return;
    }

    // Mettre à jour l'ID du compte dans l'utilisateur
    QSqlQuery updateAccountQuery;
    updateAccountQuery.prepare("UPDATE users SET accountId = :accountId WHERE id = :userId");
    updateAccountQuery.bindValue(":accountId", accountNumber);
    updateAccountQuery.bindValue(":userId", userId);

    if (!updateAccountQuery.exec()) {
        std::cout << "Erreur lors de la mise a jour de l'ID du compte dans l'utilisateur : " << updateAccountQuery.lastError().text().toStdString() << std::endl;
        return;
    }

    std::cout << "Le compte utilisateur a ete cree avec succes. Numero de compte utilisateur : " << accountNumber.toStdString() << std::endl;
    std::cout << "Mot de passe provisoire : " << randomPassword.toStdString() << std::endl;

    Sleep(3000);
    //operations.choices();
}
*/

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
                        "p.firstname AS profil_firstname, "
                        "p.lastname AS profil_lastname, "
                        "p.login AS profil_login, "
                        "p.password AS profil_password, "
                        "p.type AS profil_type, "
                        "u.username AS username, "
                        "u.role AS user_role, "
                        "u.creationDate AS user_creation_date, "
                        "ppl.balance AS ppl_balance, "
                        "ppl.id AS ppl_id, "
                        "pel.balance AS pel_balance, "
                        "pel.id AS pel_id, "
                        "lvc.balance AS lvc_balance, "
                        "lvc.id AS lvc_id "
                    "FROM "
                        "newusers AS u "
                    "LEFT JOIN "
                        "profil AS p ON p.user_id = u.id "
                    "LEFT JOIN "
                        "accounts AS ppl ON p.user_id = ppl.userId AND ppl.type = 0 "
                    "LEFT JOIN "
                        "accounts AS pel ON p.user_id = pel.userId AND pel.type = 1 "
                    "LEFT JOIN "
                        "accounts AS lvc ON p.user_id = lvc.userId AND lvc.type = 2 "
                    "WHERE "
                        "u.id = :userId");
    query.bindValue(":userId", userId);
    if (query.exec() && query.next()) {
        // Utilisateur trouve

        // Profil
        m_firstName = query.value("profil_firstname").toString();
        m_lastName = query.value("profil_lastname").toString();

        // User
        m_username = query.value("username").toString();

        // Accounts
        m_balance = query.value("ppl_balance").toDouble();
        m_PELBalance = query.value("pel_balance").toDouble();
        m_LCBalance = query.value("lvc_balance").toDouble();
        m_firstAccountId = query.value("ppl_id").toInt();
        m_PELAccountId = query.value("pel_id").toInt();
        m_LCAccountId = query.value("lvc_id").toInt();

        //m_userId = query.value("id").toInt();
        return;
    } else {
        std::system("cls");
        std::cout << "User not found." << std::endl;
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
QString User::getFirstName() const {
    return m_firstName;
}
QString User::getLastName() const {
    return m_lastName;
}
QString User::getUsername() const {
    return m_username;
}
QString User::getLogin() const  {
    return m_login;
}
int User::getIsLoggedIn() const {
    return m_isLoggedIn;
}
int User::getRole() const  {
    return m_role;
}
int User::getFirstAccountId() const {
    return m_firstAccountId;
}
int User::getPELAccountId() const {
    return m_PELAccountId;
}
int User::getLCAccountId() const {
    return m_LCAccountId;
}


double User::getPELBalance() const {
    return m_PELBalance;
}
double User::getLCBalance() const {
    return m_LCBalance;
}
double User::getBalance() const {
    return m_balance;
}

int User::getUserId() const {
    return m_userId;
}

void User::setCredentials(const QString& username, const QString& password) {
    m_login = username;
    m_password = password;
}
