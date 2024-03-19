#include "operations.h"
#include "user.h"
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#include <windows.h>

void Operations::transfert(QString username, int role) {
    QTextStream stream(stdin);

    system("CLS");
    std::cout << "A qui ?"<< std::endl;
    QString destinataire = stream.readLine();

    system("CLS");
    std::cout << "Combien ?"<< std::endl;
    QString amount = stream.readLine();

    // Credit du client - amount
    QSqlQuery queryProp;
    queryProp.prepare("SELECT * FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.login = :username");
    queryProp.bindValue(":username", username);

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
            operations.retrait(amount, username, role);
            operations.ajout(amount, destinataire, username, role);

        } else if (confirmation == "2") {
            system("CLS");
            std::cout << "Virement annule" << std::endl;
        }
    }
}

void Operations::ajout(QString amount, QString cible, QString username, int role){
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
        operations.choices(username, role);
    } else {
        system("CLS");
        std::cout << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username, role);
    }
}

void Operations::retrait(QString amount, QString username, int role){
    QSqlQuery queryMinus;
    Operations operations;

    // retire l'argent du compte de départ
    queryMinus.prepare("UPDATE accounts SET balance = balance - :amount WHERE accounts.id = (SELECT users.accountId FROM users WHERE users.login = :username)");
    queryMinus.bindValue(":username", username);
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
        operations.choices(username, role);
    }
}

void Operations::setvalue(QString username, int role){
    QTextStream stream(stdin);
    Operations operations;
    system("CLS");
    std::cout << "Combien ?" << std::endl;
    QString value = stream.readLine();
    QSqlQuery querySet;
    querySet.prepare("UPDATE accounts SET balance = :value WHERE accounts.id = (SELECT users.accountId FROM users WHERE users.login = :username)");
    querySet.bindValue(":value", value);
    querySet.bindValue(":username", username);

    if (querySet.exec()) {
        system("CLS");
        std::cout << "opperation effectuee" << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username, role);
    } else {
        system("CLS");
        std::cout << "L'operation n'a pas ete effectuee." << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username, role);
    }

}

void Operations::defaultChoices(QString username, int role){
    QTextStream stream(stdin);
    Operations operations;

    QSqlQuery query2;
    query2.prepare("SELECT * FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.firstname = :username");
    query2.bindValue(":username", username);

    if(query2.exec() && query2.next()) {
        double balance = query2.value("balance").toDouble();
        std::cout << "Bienvenue " << username.toStdString() << ", Votre solde est de : " << balance << " euros" <<std::endl;

        std::cout << "[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[9] Quitter" << std::endl;
        QString action = stream.readLine();

        if (action == "1") {
            operations.transfert(username, role);
        } else if (action == "2") {
            operations.setvalue(username, role);
        } else if (action == "3") {
            system("CLS");
            std::cout << "Combien ?" << std::endl;
            QString value = stream.readLine();
            operations.ajout(value, username, username, role);
        } else if (action == "4") {
            system("CLS");
            std::cout << "Combien ?" << std::endl;
            QString value2 = stream.readLine();
            operations.retrait(value2, username, role);
        } else if (action == "9"){
            system("CLS");
            exit(0);
        } else {
            std::cout << "User ou compte proprietaire non trouve." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'execution de la requete SQL";
    }
}

void Operations::choices(QString username, int role){
    QTextStream stream(stdin);
    Operations operations;

    User user;


    QSqlQuery query2;
    query2.prepare("SELECT * FROM accounts JOIN users ON users.accountId = accounts.id WHERE users.firstname = :username");
    query2.bindValue(":username", username);

    if(query2.exec() && query2.next()) {
        double balance = query2.value("balance").toDouble();
        double rolerecup = query2.value("role").toDouble();




        int choice = 0;

        system("CLS");
        std::cout << "DEBUG : Role : " << rolerecup << std::endl;
        Sleep(1000);
        system("CLS");

        if (rolerecup == 1) {
            // temp
            std::cout << "DEBUG : Vous etes connecte en tant qu'administrateur." << std::endl;

            // Afficher les options disponibles pour l'administrateur
            std::cout << "Que souhaitez-vous faire ?" << std::endl;
            std::cout << "1. Creer un compte client" << std::endl;
            std::cout << "2. Acceder a son compte client" << std::endl;

            int option;
            std::cin >> option;

            switch (option) {
            case 1:
                std::system("cls");
                user.createAccount();
                break;
            case 2:
                // TODO : Ajouter d'autres options.
                std::system("cls");
                operations.defaultChoices(username, role);
                break;
            default:
                std::cout << "Option invalide." << std::endl;
                break;
            }
        } else {
            // temp
            std::cout << "DEBUG : Vous etes connecte en tant que client." << std::endl;
            Sleep(1000);
            operations.defaultChoices(username, role);
        }
    } else {
        std::cout << "Compte non trouve" << std::endl;
    }
}

