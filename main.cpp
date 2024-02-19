#include <QCoreApplication>
#include <iostream>
#include <windows.h>
#include "operations.h"
#include "user.h"
#include <cstdlib> // Pour la fonction system()

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // Création d'un utilisateur
    User user;
    Operations operations;

    // Connexion de l'utilisateur
    if (user.logIn()) {
        operations.choices(username);
        std::system("cls");
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "DEBUG : Connexion reussie !" << std::endl;

        // Utiliser user pour accéder aux informations de l'utilisateur

        std::cout << "DEBUG : login : " << user.getLogin().toStdString() << std::endl;
        std::cout << "Prenom : " << user.getFirstName().toStdString() << std::endl;
        std::cout << "Nom : " << user.getLastName().toStdString() << std::endl;
        std::cout << "Solde : " << user.getBalance() << std::endl;

        std::cout << "----------------------------------------------" << std::endl;

        if (user.isAdmin(user.getLogin())) {
            // temp
            std::cout << "DEBUG : Vous etes connecte en tant qu'administrateur." << std::endl;

            // Afficher les options disponibles pour l'administrateur
            std::cout << "Que souhaitez-vous faire ?" << std::endl;
            std::cout << "1. Creer un compte client" << std::endl;
            std::cout << "2. Effectuer un virement" << std::endl;

            int option;
            std::cin >> option;

            switch (option) {
            case 1:
                std::system("cls");
                user.createAccount();
                break;
            case 2:
                // TODO : Ajouter d'autres options.
                break;
            default:
                std::cout << "Option invalide." << std::endl;
                break;
            }
        } else {
            // temp
            std::cout << "DEBUG : Vous etes connecte en tant que client." << std::endl;
        }
    } else {
        std::cout << "La connexion a echoue. Veuillez verifier vos identifiants." << std::endl;
    }

    return a.exec();
}
