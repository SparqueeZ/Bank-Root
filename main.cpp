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
    virtual void AffAccountChoices()=0;
    virtual void CreationCompte()=0;
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

    void AffLogin() override {
        QTextStream stream(stdin);
        bool loggedIn = false;

        while (!loggedIn) {
            system("CLS");
            std::cout << "Login : ";
            QString login = stream.readLine().trimmed();
            std::cout << "Mot de Passe : ";
            QString password = stream.readLine().trimmed();
            loggedIn = user->signin(login, password); // Modifiez votre méthode signin pour qu'elle retourne un booléen

            if (!loggedIn) {
                //AffMsg("Identifiants incorrects. Voulez-vous reessayer ? (O/N)");
                //QString retryChoice = stream.readLine().trimmed().toUpper();
                //if (retryChoice != "O")
                    //break;
            }
        }
    }

    void AffMainPage() override {
        QTextStream stream(stdin);
        system("CLS");
        std::cout << "Bienvenue " << user->getFirstName().toStdString() << ", Votre solde est de : " << user->getBalance().toStdString() << " euros" << std::endl;
        AffMsg("[1] Envoyer de l'argent \n[2] Definir sa quantite d'argent \n[3] Deposer de l'argent \n[4] Retirer de l'argent \n\n[9] Quitter");
        QString choice = stream.readLine().trimmed();
        //operations.defaultChoices(choice);

        if (choice == "9") {
            user->disconnect(); // Déconnecter l'utilisateur
            AffLogin(); // Rediriger vers la page de connexion
        } else {
            operations.mainchoice(choice.toInt());
        }
    };

    void AffAdminPage() override {
        QTextStream stream(stdin);
        AffMsg("Que souhaitez-vous faire ?");
        AffMsg("1. Creer un compte client");
        AffMsg("2. Acceder a son compte client");
        QString choice =stream.readLine().trimmed();
        operations.choices(choice);
    }

    void AffAccountChoices() override {

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

    void AffAccountChoices() override {

    }

    void CreationCompte() override {

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
        interfaceUtilisateur->AffMainPage();
        while (user.getIsLoggedIn() == 1) {
            interfaceUtilisateur->AffMainPage();
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


