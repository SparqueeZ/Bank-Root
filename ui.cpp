#include "ui.h";
#include "user.h";
#include "operations.h";
#include <iostream>


class Console : public UI {
public :

    User user;
    Operations operations;

    void AffMsg(QString Msg) {
        std::cout << Msg.toStdString() << std::endl;
    }

    void AffLogin() override {
        QTextStream stream(stdin);
        AffMsg("Login :");
        QString login = stream.readLine().trimmed();
        AffMsg("Mot de Passe :");
        QString password = stream.readLine().trimmed();
        user.logIn(login, password);
    }

    void AffMainPage() override {
        QTextStream stream(stdin);
        std::cout << "Bienvenue " << user.getFirstName().toStdString() << ", Votre solde est de : " << user.getBalance().toStdString() << "euros" << std::endl;
        AffMsg("[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[9] Quitter");
        QString choice = stream.readLine().trimmed();
        //operations.defaultChoices(choice);
        //operations.selectHomeChoices(choice); <--- C'est ça que je veux
    };

    void AffAccount(QString accType) {
        User user;
    };

};


class GUI : public UI {
    void AffLogin(){


    }
    void AffMainPage() {

    }
};
