#include "operations.h"
#include "user.h"
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#include <windows.h>

void Operations::mainchoice(int choice) {
    QTextStream stream(stdin);
    Operations operations;
    User user;
    if (choice == 1) {
        operations.transfert();
    } else if (choice == 2) {
        operations.setvalue();
    } else if (choice == 3) {
        system("CLS");
        std::cout << "Combien ?" << std::endl;
        QString value = stream.readLine();
        operations.ajout(value, user.getLogin());
    } else if (choice == 4) {
        system("CLS");
        std::cout << "Combien ?" << std::endl;
        QString value2 = stream.readLine();
        operations.retrait(value2);
    } else {
        std::cout << "User ou compte proprietaire non trouve." << std::endl;
    }
}

void Operations::adminChoice(int choice) {
    Operations operations;
    User user;

    if (choice == 1) {
        std::system("cls");
        //user.createAccount();
    }
    else if (choice == 2){
        std::system("cls");
        //operations.defaultChoices();
    }   else {
        std::cout << "Option invalide." << std::endl;
    }
}

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
    Operations operations;
    // ajoute l'argent au compte cible
    queryAdd.prepare("UPDATE accounts SET balance = balance + :amount WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    queryAdd.bindValue(":amount", amount);

    if (queryAdd.exec()) {
        system("CLS");
        std::cout << "Ajout effectue" << std::endl;
        Sleep(500);
        system("CLS");
        //operations.choices();
    } else {
        system("CLS");
        std::cout << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(500);
        system("CLS");
        //operations.choices();
    }
}

void Operations::removeBalance(double amount, int destinataireId) {
    QSqlQuery queryAdd;
    Operations operations;
    // ajoute l'argent au compte cible
    queryAdd.prepare("UPDATE accounts SET balance = balance - :amount WHERE id = :destinataireId");
    queryAdd.bindValue(":destinataireId", destinataireId);
    queryAdd.bindValue(":amount", amount);

    if (queryAdd.exec()) {
        system("CLS");
        std::cout << "Retrait effectue" << std::endl;
        Sleep(500);
        system("CLS");
        //operations.choices();
    } else {
        system("CLS");
        std::cout << "Le retrait n'a pas ete effectue." << std::endl;
        Sleep(500);
        system("CLS");
        //operations.choices();
    }
}

//Operations::addToHistory(int )



// A supprimer
void Operations::transfert() {
    QTextStream stream(stdin);
    User user;

    system("CLS");
    std::cout << "A qui ?"<< std::endl;
    QString destinataire = stream.readLine();

    system("CLS");
    std::cout << "Combien ?"<< std::endl;
    QString amount = stream.readLine();

    // Credit du client - amount
    QSqlQuery queryProp;
    queryProp.prepare("SELECT * FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.login = :username");
    queryProp.bindValue(":username", user.getLogin());

    if(queryProp.exec() && queryProp.next()) {
        double balanceProp = queryProp.value("balance").toDouble();
        balanceProp -= amount.toDouble();

        system("CLS");
        std::cout << "Votre nouveau solde sera de :" << balanceProp << std::endl;
        std::cout << "Confirmez-vous le virement de " << amount.toDouble() << " euros ?" << std::endl;
        std::cout << "[1] Oui" << std::endl;
        std::cout << "[2] Non" << std::endl;

        QString confirmation = stream.readLine();

        if(confirmation == "1") {
            Operations operations;
            operations.retrait(amount);
            operations.ajout(amount, destinataire);

        } else if (confirmation == "2") {
            system("CLS");
            std::cout << "Virement annule" << std::endl;
        }
    }
}

void Operations::ajout(QString amount, QString cible){
    QSqlQuery queryAdd;
    Operations operations;
    // ajoute l'argent au compte cible
    queryAdd.prepare("UPDATE accounts SET balance = balance + :amount WHERE accounts.id = (SELECT users.accountId FROM users WHERE users.login = :destinataire)");
    queryAdd.bindValue(":destinataire", cible);
    queryAdd.bindValue(":amount", amount.toDouble());

    if (queryAdd.exec()) {
        system("CLS");
        std::cout << "Ajout effectue" << std::endl;
        Sleep(3000);
        system("CLS");
        //operations.choices();
    } else {
        system("CLS");
        std::cout << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(3000);
        system("CLS");
        //operations.choices();
    }
}

void Operations::retrait(QString amount){
    QSqlQuery queryMinus;
    Operations operations;
    User user;

    // retire l'argent du compte de dÃ©part
    queryMinus.prepare("UPDATE accounts SET balance = balance - :amount WHERE accounts.id = (SELECT users.accountId FROM users WHERE users.login = :username)");
    queryMinus.bindValue(":username", user.getLogin());
    queryMinus.bindValue(":amount", amount.toDouble());

    if (queryMinus.exec()) {
        system("CLS");
        std::cout << "retrait effectue" << std::endl;
        Sleep(3000);
        //system("CLS");
        //operations.choices(username, role);
    } else {
        system("CLS");
        std::cout << "Le retrait n'a pas ete effectue." << std::endl;
        Sleep(3000);
        system("CLS");
        //operations.choices();
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

void Operations::defaultChoices(QString choice){
    QTextStream stream(stdin);
    Operations operations;
    User user;

    if (choice == "1") {
        operations.transfert();
    } else if (choice == "2") {
        operations.setvalue();
    } else if (choice == "3") {
        system("CLS");
        std::cout << "Combien ?" << std::endl;
        QString value = stream.readLine();
        operations.ajout(value, user.getLogin());
    } else if (choice == "4") {
        system("CLS");
        std::cout << "Combien ?" << std::endl;
        QString value2 = stream.readLine();
        operations.retrait(value2);
    } else if (choice == "9"){
        system("CLS");
        exit(0);
    } else {
        std::cout << "User ou compte proprietaire non trouve." << std::endl;
    }

}

void Operations::choices(QString choice){
    QTextStream stream(stdin);
    Operations operations;
    User user;
    system("CLS");

    if (choice == "1") {
        std::system("cls");
        user.createAccount();
    }
    else if (choice == "2"){
        std::system("cls");
        //operations.defaultChoices();
    }   else {
        std::cout << "Option invalide." << std::endl;
    }
}
