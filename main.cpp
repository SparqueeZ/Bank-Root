#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include "login.h"
#include <iostream>
#include "user.h"
#include "operations.h"
#include <cstdlib>
#include <synchapi.h>

class UI {
public:
    virtual void AffLogin()=0;
    virtual void AffMainPage()=0;
    virtual void AffAdminPage()=0;
    virtual void CreationCompte()=0;
    virtual void AffVirement()=0;
};


class Console : public UI {
private:
    User* user;

public:
    Console(User* u) : user(u) {}
    Operations operations;

    void AffMsg(QString Msg) {
        std::cout << Msg.toStdString() << std::endl;
    }

    void clearScreen() {
        std::system("cls");
    }

    void AffSeparator() {
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    void AffLogin() override {
        QTextStream stream(stdin);
        bool loggedIn = false;

        while (!loggedIn) {
            system("CLS");
            std::cout << "Login : ";
            QString login = stream.readLine().trimmed();
            std::cout << "Mot de Passe : ";
            QString password = stream.readLine().trimmed();
            loggedIn = user->signin(login, password);
        }
    }

    void AffMainPage() override {
        QTextStream stream(stdin);
        system("CLS");
        std::cout << "Bienvenue " << user->getFirstName().toStdString() << "." << std::endl;

        std::cout << "\nVos comptes bancaires --------------------------------------" << std::endl;

        if(user->getBalance()) {
            std::cout << "Compte courant : " << user->getBalance() << " euros." << std::endl;
        }

        if(user->getPELBalance()) {
            std::cout << "Compte PEL : " << user->getPELBalance() << " euros." << std::endl;
        }

        if(user->getLCBalance()) {
            std::cout << "Compte Livret C : " << user->getLCBalance() << " euros." << std::endl;
        }

        AffSeparator();

        if (user->getRole() != 1) {
            AffMsg("[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[9] Deconnexion");
        } else {
            AffMsg("[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[8] Revenir en arriere\n[9] Deconnexion");
        }


        QString choice = stream.readLine().trimmed();
        //operations.defaultChoices(choice);

        if (choice == "9") {
            user->disconnect();
            AffLogin();
        } else if (choice == "1") {
            AffVirement();
        }
        else if (choice == "8" && user->getRole() == 1) {
            AffAdminPage();
        }
        else {
            //operations.mainchoice(choice.toInt());
        }
    };

    void AffAdminPage() override {
        clearScreen();
        QTextStream stream(stdin);
        std::cout << "Bienvenue " << user->getFirstName().toStdString() << ", que voulez-vous faire ?" << std::endl;
        AffMsg("1. Creer un compte client");
        AffMsg("2. Acceder a mon compte client");
        QString choice =stream.readLine().trimmed();
        if(choice == "1") {
            user->createAccount();
        } else if (choice == "2") {
            AffMainPage();
        } else if (choice == "9") {
            user->disconnect();
            AffLogin();
        }
    }

    void AffVirement() override {
        QTextStream stream(stdin);
        clearScreen();

        std::cout << "Entrez l'identifiant du compte qui vas recevoir votre argent : ";
        QString destId = stream.readLine().trimmed();

        clearScreen();

        std::cout << "Entrez le montant a envoye : ";
        QString amount = stream.readLine().trimmed();

        operations.virement(user->getFirstAccountId(), destId.toInt(), amount.toDouble());
        // Recharger les données de l'user
    }

    void CreationCompte() override {

    }

};


class GUI : public UI {
private:
    int argc;
    char **argv;
    User* user;

public:
    GUI(int argc, char **argv, User* u) : argc(argc), argv(argv), user(u){}

    void AffLogin() override {
        QApplication a(argc, argv);
        Login w;
        w.show();
        a.exec();
    }

    void AffMainPage() override {

    }

    void AffAdminPage() override {

    }

    void CreationCompte() override {

    }

    void AffVirement() override{

    }
};


//--------------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char *argv[]) {
    User user;
    UI* interfaceUtilisateur = nullptr;
    QApplication app(argc, argv);

    // Affichage de la boîte de dialogue demandant le mode d'ouverture
    QMessageBox msgBox;
    msgBox.setText("Voulez-vous ouvrir le logiciel en mode console ou en mode graphique ?");
    msgBox.addButton("Mode Console", QMessageBox::AcceptRole);
    msgBox.addButton("Mode Graphique", QMessageBox::AcceptRole);
    msgBox.setDefaultButton(QMessageBox::NoButton);
    int choice = msgBox.exec();

    if (choice == 0){
        interfaceUtilisateur = new Console(&user);
    }
    else {
        interfaceUtilisateur = new GUI(argc, argv, &user);
    }

    interfaceUtilisateur->AffLogin();

    if (user.getIsLoggedIn() == 1) {
        while (user.getIsLoggedIn() == 1) {
            if(user.getRole() == 1){
                interfaceUtilisateur->AffAdminPage();
            } else {
                interfaceUtilisateur->AffMainPage();
            }
        }
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    } else {
        std::cout << "User not found." << std::endl;
    }

    return app.exec();
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------
class Choice {
protected:
    int choice;

public:
    Choice(int choice) : choice(choice) {}
};


