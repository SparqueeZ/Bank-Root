#include "operations.h"
#include "user.h"
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#include <windows.h>

void Operations::virement(int accountPropId, int accountDestId, double amount) {

    // Récupère la balance actuelle de l'user qui vas etre debite.
    QSqlQuery queryProp;
    // Ancienne version pour le niveau 1 : queryProp.prepare("SELECT balance FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.login = :login");
    queryProp.prepare("SELECT balance FROM accounts WHERE id = :id");
    queryProp.bindValue(":id", accountPropId);

    if(queryProp.exec() && queryProp.next()) {
        double balanceProp = queryProp.value("balance").toDouble();

        // Vérification si l'user a assez d'argent.
        if(balanceProp >= amount) {
            // Récupère la balance actuelle de l'user qui vas etre credite.
            QSqlQuery queryDest;
            queryDest.prepare("SELECT balance FROM accounts WHERE id = :id");
            queryDest.bindValue(":id", accountDestId);

            if(queryDest.exec() && queryDest.next()) {
                //double balanceDest = queryDest.value("balance").toDouble();

                addBalance(amount, accountDestId);
                removeBalance(amount, accountPropId);
            }

        } else {
            return;
        }


    }



    // Fait le calcul

    // Envoi en bdd

    // Retourne le nouveau solde ??



}

void Operations::addBalance(double amount, int destinataireId) {
    QSqlQuery queryAdd;
    // Get the current balance of the account
    queryAdd.prepare("SELECT balance FROM accounts WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    if (!queryAdd.exec() || !queryAdd.next()) {
        std::cerr << "Error retrieving account balance." << std::endl;
        return;
    }
    double currentBalance = queryAdd.value("balance").toDouble();

    // Check if adding the amount will exceed the maximum balance limit
    if (currentBalance + amount > 10000) {
        std::cerr << "L'ajout n'a pas ete effectue, le Livret C ne peut pas depasser 10 000€" << std::endl;
        Sleep(3000);
        return;
    }

    // Add the amount to the balance
    queryAdd.prepare("UPDATE accounts SET balance = balance + :amount WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    queryAdd.bindValue(":amount", amount);

    if (queryAdd.exec()) {
        std::cout << "Ajout effectue" << std::endl;
        Sleep(3000);
    } else {
        std::cerr << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(3000);
    }
}

void Operations::removeBalance(double amount, int destinataireId) {
    QSqlQuery queryRemove;
    // Get the current balance of the account
    queryRemove.prepare("SELECT balance FROM accounts WHERE id = :destinataireId");
    queryRemove.bindValue(":destinataireId", destinataireId);
    if (!queryRemove.exec() || !queryRemove.next()) {
        std::cerr << "Error retrieving account balance." << std::endl;
        return;
    }
    double currentBalance = queryRemove.value("balance").toDouble();

    // Check if removing the amount will make the balance negative
    if (currentBalance - amount < 0) {
        std::cerr << "Removing " << amount << "€ would result in a negative balance." << std::endl;
        return;
    }

    // Remove the amount from the balance
    queryRemove.prepare("UPDATE accounts SET balance = balance - :amount WHERE id = :destinataireId");
    queryRemove.bindValue(":destinataireId", destinataireId);
    queryRemove.bindValue(":amount", amount);

    if (queryRemove.exec()) {
        std::cout << "Retrait effectue" << std::endl;
        Sleep(3000);
    } else {
        std::cerr << "Le retrait n'a pas ete effectue." << std::endl;
        Sleep(3000);
    }
}

//Operations::addToHistory(int )



void Operations::setvalue(){
    User user;
    QTextStream stream(stdin);
    Operations operations;
    system("CLS");
    std::cout << "Combien ?" << std::endl;
    QString value = stream.readLine();
    QSqlQuery querySet;
    querySet.prepare("UPDATE accounts SET balance = :value WHERE accounts.id = (SELECT users.accountId FROM users WHERE users.login = :username)");
    querySet.bindValue(":value", value);
    querySet.bindValue(":username", user.getLogin());

    if (querySet.exec()) {
        system("CLS");
        std::cout << "opperation effectuee" << std::endl;
        Sleep(3000);
        system("CLS");
        //operations.choices();
    } else {
        system("CLS");
        std::cout << "L'operation n'a pas ete effectuee." << std::endl;
        Sleep(3000);
        system("CLS");
        //operations.choices();
    }

}

