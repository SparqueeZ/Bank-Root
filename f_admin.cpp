#include "f_admin.h"
#include "qdatetime.h"
#include "qrandom.h"
#include "qsqlerror.h"
#include "QSqlQuery"
#include <iostream>
#include <ostream>

int generateAccountNumber() {
    QRandomGenerator generator(QDateTime::currentMSecsSinceEpoch());
    int randomNumber = generator.bounded(10000);
    QString accountNumber = QString::number(randomNumber).rightJustified(4, '0');
    return accountNumber.toInt();
}

f_admin::f_admin() {

}

int f_admin::test () {
    // Fonction de test. Appel : Definir instance -> admin.test();
}

// Migrer les fonctions de creation de compte ici.

int f_admin::createUser(QString username, int role){
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

int f_admin::createAccount(int userId, int type, double balance){
    int accountId = generateAccountNumber();

    // Créer le compte bancaire
    QSqlQuery insertAccountQuery;
    insertAccountQuery.prepare("INSERT INTO accounts (id, userId, type, balance) "
                               "VALUES (:id, :userId, :type, :balance)");
    insertAccountQuery.bindValue(":id", accountId);
    insertAccountQuery.bindValue(":userId", userId);
    insertAccountQuery.bindValue(":type", type);
    insertAccountQuery.bindValue(":balance", balance);

    if(insertAccountQuery.exec()){
        return true;
    } else {
        return false;
    }
};

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

//void f_admin::saveToHistoryAdmin(int type, int userId);


