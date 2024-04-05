#include "operations.h"
#include "qsqlerror.h"
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
    queryAdd.prepare("SELECT balance, type FROM accounts WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    if (!queryAdd.exec() || !queryAdd.next()) {
        std::cerr << "Error retrieving account balance." << std::endl;
        return;
    }
    int type = queryAdd.value("type").toInt();
    double currentBalance = queryAdd.value("balance").toDouble();

    if(type==2){
    // Check if adding the amount will exceed the maximum balance limit
        if (currentBalance + amount > 10000) {
            std::cerr << "L'ajout n'a pas ete effectue, le Livret C ne peut pas depasser 10 000€" << std::endl;
            Sleep(3000);
            return;

        }
        else{
            queryAdd.prepare("UPDATE accounts SET balance = balance + :amount WHERE id = :destinataireId");
            queryAdd.bindValue(":destinataireId", destinataireId);
            queryAdd.bindValue(":amount", amount);

            if (queryAdd.exec()) {
                std::cout << "Ajout effectue" << std::endl;
                addToHistory(0, destinataireId, 1, amount, "Credit", "Description (a completer)");
                Sleep(3000);
            } else {
                std::cerr << "L'ajout n'a pas ete effectue." << std::endl;
                Sleep(3000);
            }
        }
    }else{
    // Add the amount to the balance
    queryAdd.prepare("UPDATE accounts SET balance = balance + :amount WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    queryAdd.bindValue(":amount", amount);

    if (queryAdd.exec()) {
        std::cout << "Ajout effectue" << std::endl;
        addToHistory(0, destinataireId, 1, amount, "Credit", "Description (a completer)");
        //Sleep(3000);
    } else {
        std::cerr << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(3000);
    }
    }
}

void Operations::removeBalance(double amount, int destinataireId) {
    QSqlQuery queryType;
    queryType.prepare("SELECT type FROM accounts WHERE id = :destinataireId");
    queryType.bindValue(":destinataireId", destinataireId);
    if (!queryType.exec() || !queryType.next()) {
        std::cerr << "Error retrieving account type." << std::endl;
        return;
    }
    int type = queryType.value("type").toInt();

    if (type == 1) { // Si c'est un PEL
        std::cerr << "Retrait bloqué : Impossible de retirer de l'argent d'un Plan d'Epargne Logement (PEL)." << std::endl;
        Sleep(2000);
        return;
    }

    // Si ce n'est pas un PEL, procéder au retrait
    QSqlQuery queryRemove;
    queryRemove.prepare("SELECT balance FROM accounts WHERE id = :destinataireId");
    queryRemove.bindValue(":destinataireId", destinataireId);
    if (!queryRemove.exec() || !queryRemove.next()) {
        std::cerr << "Error retrieving account balance." << std::endl;
        return;
    }
    double currentBalance = queryRemove.value("balance").toDouble();

    // Vérifier si le retrait rendra le solde négatif
    if (currentBalance - amount < 0) {
        std::cerr << "Removing " << amount << "€ would result in a negative balance." << std::endl;
        return;
    }

    // Effectuer le retrait
    queryRemove.prepare("UPDATE accounts SET balance = balance - :amount WHERE id = :destinataireId");
    queryRemove.bindValue(":destinataireId", destinataireId);
    queryRemove.bindValue(":amount", amount);

    if (queryRemove.exec()) {
        std::cout << "Retrait effectue" << std::endl;
        addToHistory(destinataireId, 0, 2, amount, "Debit", "Description (a completer)");
        //Sleep(3000);
    } else {
        std::cerr << "Le retrait n'a pas ete effectue." << std::endl;
        Sleep(3000);
    }
}

//Operations::addToHistory(int )
void Operations::addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description){

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
        //Sleep(3000);
    } else {
        // Gestion de l"erreur.
        std::cerr << "Erreur lors de l'ajout a l'historique : " << addToHistory.lastError().text().toStdString() << std::endl;
        Sleep(3000);
    }
}


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

