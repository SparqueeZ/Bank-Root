#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include "login.h"
#include <iostream>
#include "qsqlquery.h"
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
        AffMsg("[1] Creer un compte client");
        AffMsg("[2] Acceder votre espace client");
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

        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database(); // Utilise la connexion par défaut

        // Vérification de la connexion
        if (!db.isValid()) {
            qDebug() << "Erreur: Aucune connexion valide à la base de données n'a été trouvée";
            return;
        }

        // ID de l'utilisateur que vous souhaitez récupérer
        int userId = 1; // Remplacez 1 par l'ID de l'utilisateur que vous voulez récupérer

        // Préparation de la requête SQL pour récupérer l'utilisateur avec l'ID spécifié et ses comptes associés
        QSqlQuery query(db); // Utilisation de la connexion existante
        query.prepare("SELECT u.firstname AS user_firstname, sa.account_id, a.type, u2.firstname AS account_owner_firstname "
                      "FROM saved_accounts AS sa "
                      "JOIN users AS u ON u.id = sa.user_id "
                      "JOIN accounts AS a ON sa.account_id = a.id "
                      "JOIN users AS u2 ON u2.id = a.userId "
                      "WHERE u.id = :userId");
        query.bindValue(":userId", userId);

        // Exécution de la requête SQL
        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête SQL";
            return;
        }

        // Affichage des informations récupérées
        std::cout << "Liste des comptes --------------------------------------" << std:: endl;
        QMap<int, QString> accountMap; // Pour stocker les correspondances ID de compte - choix de l'utilisateur
        int count = 1;
        while (query.next()) {
            QString userFirstName = query.value("user_firstname").toString();
            QString accountOwnerId = query.value("account_owner_firstname").toString();
            QString accountId = query.value("account_id").toString();
            QString accountType = query.value("type").toString();

            if(accountType == '0') {
                accountType = "Courant";
            } else if (accountType == "1") {
                accountType = "Livret C";
            } else if (accountType == "2") {
                accountType = "PEL";
            }

            // Affichage des informations récupérées
            std::cout << "[" << count << "] " << accountOwnerId.toStdString() << " (" << accountType.toStdString() << ") : " << accountId.toInt() << std::endl;

            // Stockage de la correspondance entre le choix de l'utilisateur et l'ID du compte
            accountMap.insert(count, accountId);
            count++;
        }

        int choice = stream.readLine().trimmed().toInt();
        if (!accountMap.contains(choice)) {
            qDebug() << "Choix invalide";
            return;
        }

        QString selectedAccountId = accountMap.value(choice);

        clearScreen();

        std::cout << "Entrez le montant à envoyer : ";
        QString amount = stream.readLine().trimmed();

        operations.virement(user->getFirstAccountId(), selectedAccountId.toInt(), amount.toDouble());
        // Recharger les données de l'utilisateur si nécessaire
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


