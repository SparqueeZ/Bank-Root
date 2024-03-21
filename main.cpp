#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include "login.h"
#include <iostream>
#include "user.h"
#include "operations.h"
#include <cstdlib>



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Affichage de la boÃ®te de dialogue demandant le mode d'ouverture
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous ouvrir le logiciel en mode console ou en mode graphique ?");
    msgBox.addButton("Mode Console", QMessageBox::AcceptRole);
    msgBox.addButton("Mode Graphique", QMessageBox::AcceptRole);
    msgBox.setDefaultButton(QMessageBox::NoButton);
    int choice = msgBox.exec();

    if (choice == 0) {
        // Mode Console
        QCoreApplication a(argc, argv);
        // CrÃ©ation d'un utilisateur
        User user;
        Operations operations;

        // Connexion de l'utilisateur
        if (user.logIn()) {
            std::system("cls");
            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "DEBUG : Connexion reussie !" << std::endl;

            // Utiliser user pour accÃ©der aux informations de l'utilisateur

            std::cout << "DEBUG : login : " << user.getLogin().toStdString() << std::endl;
            std::cout << "Prenom : " << user.getFirstName().toStdString() << std::endl;
            std::cout << "Nom : " << user.getLastName().toStdString() << std::endl;
            std::cout << "Solde : " << user.getBalance() << std::endl;

            std::cout << "----------------------------------------------" << std::endl;

            operations.choices(user.getLogin(), user.getRole());

            /*if (user.isAdmin(user.getLogin())) {
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
            }*/
        } else {
            std::cout << "La connexion a echoue. Veuillez verifier vos identifiants." << std::endl;
        }

        return a.exec();
    } else {
        QApplication a(argc, argv);
        Login w;
        w.show();
        return a.exec();
    }

    return app.exec();
}
