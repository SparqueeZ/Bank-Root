#include "operations.h"
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#include <windows.h>

void Operations::transfert(QString username) {
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
        std::cout << "Votre nouveau balance sera de :" << balanceProp << std::endl;
        std::cout << "Confirmez-vous le virement de " << amount.toDouble() << " euros ?" << std::endl;
        std::cout << "[1] Oui" << std::endl;
        std::cout << "[2] Non" << std::endl;

        QString confirmation = stream.readLine();

        if(confirmation == "1") {
            Operations operations;
            operations.retrait(amount, username);
            operations.ajout(amount, destinataire, username);

        } else if (confirmation == "2") {
            system("CLS");
            std::cout << "Virement annule" << std::endl;
        }
    }
}

void Operations::ajout(QString amount, QString cible, QString username){
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
        operations.choices(username);
    } else {
        system("CLS");
        std::cout << "L'ajout n'a pas ete effectue." << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username);
    }
}

void Operations::retrait(QString amount, QString username){
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
        system("CLS");
        operations.choices(username);
    } else {
        system("CLS");
        std::cout << "Le retrait n'a pas ete effectue." << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username);
    }
}

void Operations::setvalue(QString username){
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
        operations.choices(username);
    } else {
        system("CLS");
        std::cout << "L'operation n'a pas ete effectuee." << std::endl;
        Sleep(3000);
        system("CLS");
        operations.choices(username);
    }

}

void Operations::choices(QString username){
    QTextStream stream(stdin);
    Operations operations;


    QSqlQuery query2;
    query2.prepare("SELECT * FROM accounts where accounts.id = (SELECT users.id FROM users WHERE users.login = :username)");
    query2.bindValue(":username", username);

    if(query2.exec() && query2.next()) {
        double balance = query2.value("balance").toDouble();

        system("CLS");
        std::cout << "Bienvenue " << username.toStdString() << ", Votre balance est de : " << balance << " euros" <<std::endl;

        std::cout << "[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[9] Quitter" << std::endl;
        QString action = stream.readLine();

        if (action == "1") {
            operations.transfert(username);
        } else if (action == "2") {
            operations.setvalue(username);
        } else if (action == "3") {
            system("CLS");
            std::cout << "Combien ?" << std::endl;
            QString value = stream.readLine();
            operations.ajout(value, username, username);
        } else if (action == "4") {
            system("CLS");
            std::cout << "Combien ?" << std::endl;
            QString value2 = stream.readLine();
            operations.retrait(value2, username);
        } else if (action == "9"){
            system("CLS");
            exit(0);
        } else {
            std::cout << "User ou compte propriétaire non trouve." << std::endl;
        }
    } else {
        std::cout << "Balance non trouve" << std::endl;
    }
}

