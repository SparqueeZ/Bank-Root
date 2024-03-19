#include "user.h"
#include "operations.h"
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include <synchapi.h>

User::User() {}

User::User(const QString& login, const QString& lastName, const QString& firstName, const QDate& dateOfBirth, double balance)
    : m_login(login), m_lastName(lastName), m_firstName(firstName), m_dateOfBirth(dateOfBirth), m_balance(balance) {
}

bool User::logIn(const QString& username, const QString& password) {
    QString login = username;
    QString pass = password;

    // Si les valeurs des paramètres ne sont pas fournies, demander les identifiants dans la console
    if (username.isEmpty() && password.isEmpty()) {
        QTextStream stream(stdin);
        std::cout << "Entrez votre identifiant : ";
        login = stream.readLine().trimmed();
        std::cout << "Entrez votre mot de passe : ";
        pass = stream.readLine().trimmed();
    }

    // Connexion à la base de données MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("90.26.217.25");
    db.setUserName("test");
    db.setPassword("I-B*!O0vGqyFkMed");
    db.setDatabaseName("bank_root");
    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données :" << db.lastError().text();
        return false;
    };

    // Requête pour récupérer les informations de l'utilisateur
    QSqlQuery query;
    query.prepare("SELECT * FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.login = :login and users.password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", pass);
    if (query.exec() && query.next()) {
        // Utilisateur trouvé
        m_firstName = query.value("firstname").toString();
        m_lastName = query.value("lastname").toString();
        m_balance = query.value("balance").toDouble();
        m_login = query.value("login").toString();
        return true;
    } else {
        qDebug() << "Identifiants incorrects :" << query.lastError().text();
        return false;
    }
}

void User::createAccount() {
    QTextStream stream(stdin);
    Operations operations;

    // Demander les informations nécessaires pour créer un compte
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

    std::cout << "Le compte utilisateur a ete cree avec succès. Numero de compte utilisateur : " << accountNumber.toStdString() << std::endl;
    std::cout << "Mot de passe provisoire : " << randomPassword.toStdString() << std::endl;

    Sleep(3000);
    operations.choices("Baptiste", 1);
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
double User::getBalance() const  {
    return m_balance;
}
QString User::getLogin() const  {
    return m_login;
}
int User::getRole() const  {
    return m_role;
}

void User::setCredentials(const QString& username, const QString& password) {
    m_login = username;
    m_password = password;
}
