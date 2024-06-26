#include "f_admin.h"
#include "qdatetime.h"
#include "qrandom.h"
#include "qsqlerror.h"
#include "QSqlQuery"
#include "user.h"
#include <iostream>
#include <ostream>
#include <synchapi.h>

int generateAccountNumber() {
    QRandomGenerator generator(QDateTime::currentMSecsSinceEpoch());
    int randomNumber = generator.bounded(10000);
    QString accountNumber = QString::number(randomNumber).rightJustified(4, '0');
    return accountNumber.toInt();
}

f_admin::f_admin() {

}

// Créer l'utilisateur
int f_admin::createUser(QString username, int role){
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

// Créer un compte bancaire
int f_admin::createAccount(int userId, int type, double balance){
    int accountId = generateAccountNumber();
    int newAccountId = -1;

    if (type == -1) return -1;



    // Créer le compte bancaire
    QSqlQuery insertAccountQuery;
    insertAccountQuery.prepare("INSERT INTO accounts (id, userId, type, balance) "
                               "VALUES (:id, :userId, :type, :balance)");
    insertAccountQuery.bindValue(":id", accountId);
    insertAccountQuery.bindValue(":userId", userId);
    insertAccountQuery.bindValue(":type", type);
    insertAccountQuery.bindValue(":balance", balance);

    if(insertAccountQuery.exec()){
        newAccountId = insertAccountQuery.lastInsertId().toInt();
    } else {
        return -1;
    }

    if (type == 1 || type == 2) {
        User user;
        user.addBeneficiaire(accountId, userId);
    }

    return newAccountId;
};

// Créer un profil utilisateur
bool f_admin::createProfil(int userId, QString firstname, QString lastname, QString login, QString password, int type){
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

// Obtenir la balance d'un compte en banque avec son id.
double f_admin::checkBalance(int accountId) {
    QSqlQuery query;
    query.prepare("SELECT balance FROM accounts WHERE id = :accountId");
    query.bindValue(":accountId", accountId);
    double balance = query.value("balance").toDouble();
    std::cout << balance << std::endl;

    if (query.exec()){
        return balance;
    } else {
        qDebug() << "Erreur lors de la recuperation de la balance :" << query.lastError().text();
        return -1;
    }
}

// Retourne true si un User possède un type de compte en banque (Principal / PEL / Livret C).
bool f_admin::checkUserAccountType(int userId, int accountType) {
    QSqlQuery query;
    query.prepare("SELECT type FROM accounts WHERE userId = :userId and type = :accountType");
    query.bindValue(":userId", userId);
    query.bindValue(":accountType", accountType);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

// Sauvegarde d'une action admin en historique.
void f_admin::saveToHistoryAdmin(int userId, int type, QString description) {
    QSqlQuery query;
    query.prepare("INSERT INTO history_admin (user_id, type, description) VALUES (:userId, :type, :description)");
    query.bindValue(":userId", userId);
    query.bindValue(":type", type);
    query.bindValue(":description", description);

    if (!query.exec()) {
        std::cout << "Erreur lors de l'insertion dans l'historique admin : " << query.lastError().text().toStdString() << std::endl;
        Sleep(3000);
        return ;
    }
};


