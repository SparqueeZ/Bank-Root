#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include "login.h"
#include <iostream>
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "user.h"
#include "operations.h"
#include <cstdlib>
#include <synchapi.h>
#include <conio.h>

class UI {
public:
    virtual void AffLogin()=0;
    virtual void AffMainPage()=0;
    virtual void AffAdminPage()=0;
    virtual void CreationCompte()=0;
    virtual void AffVirement()=0;
    virtual void AffAddBeneficiaire()=0;
    virtual void AffRetrait()=0;
    virtual void AffHistory()=0;
    virtual void AffAjout()=0;
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
        user->refreshUserData();
        QTextStream stream(stdin);
        std::system("cls");
        std::cout << "Bienvenue " << user->getFirstName().toStdString() << "." << std::endl;
        std::cout << "\nVos comptes bancaires --------------------------------------" << std::endl;
        // Si le compte a un ID, alors on affiche le compte.
        if(user->getFirstAccountId()) {
            std::cout << "Compte courant : " << user->getBalance() << " euros." << std::endl;
        }
        if(user->getPELAccountId()) {
            std::cout << "Compte PEL : " << user->getPELBalance() << " euros." << std::endl;
        }
        if(user->getLCAccountId()) {
            std::cout << "Compte Livret C : " << user->getLCBalance() << " euros." << std::endl;
        }
        AffSeparator();
        if (user->getRole() != 1) {
            AffMsg("[1] Realiser un transfert \n[2] Ajouter un beneficiaire \n[3] Retirer de l'argent \n[4] Deposer de l'argent \n[5] Consulter l'historique \n\n[9] Deconnexion");
        } else {
            AffMsg("[1] Realiser un transfert \n[2] Ajouter un beneficiaire \n[3] Retirer de l'argent \n[4] Deposer de l'argent \n[5] Consulter l'historique \n\n[8] Revenir en arriere\n[9] Deconnexion");
        }

        QString choice = stream.readLine().trimmed();
        //operations.defaultChoices(choice);

        if (choice == "9") {
            user->disconnect();
            AffLogin();
        } else if (choice == "1") {
            AffVirement();
        } else if (choice == "2") {
            AffAddBeneficiaire();
        } else if (choice == "3") {
            AffRetrait();
        } else if (choice == "4") {
            AffAjout();
        } else if (choice == "5") {
            AffHistory();
        } else if (choice == "8" && user->getRole() == 1) {
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
        QSqlDatabase db = QSqlDatabase::database();
        // Vérification de la connexion
        if (!db.isValid()) {
            qDebug() << "Erreur: Aucune connexion valide à la base de données n'a été trouvée";
            return;
        }


        // Partie proprietaire -------------------
        QString selectedPropId;
        QSqlQuery getAccounts(db);
        getAccounts.prepare("SELECT "
                            "MAX(CASE WHEN a.type = 0 THEN a.id END) AS principalId, "
                            "MAX(CASE WHEN a.type = 1 THEN a.id END) AS PELId, "
                            "MAX(CASE WHEN a.type = 2 THEN a.id END) AS LCId "
                            "FROM accounts AS a "
                            "WHERE userId = :userId "
                            "AND a.type IN (0, 1, 2)");
        getAccounts.bindValue(":userId", user->getUserId());
        if (!getAccounts.exec()) {
            //qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
            return;
        }

        // Affichage des résultats
        std::cout << "Liste des comptes proprietaires ----------------------------" << std:: endl;
        if (getAccounts.next()) {
            QMap<int, QString> accountMap;
            int count = 1;
            QString principalId = getAccounts.value("principalId").toString();
            QString PELId = getAccounts.value("PELId").toString();
            QString LCId = getAccounts.value("LCId").toString();

            if (principalId.toInt() != 0) {
                std::cout << "[" << count << "] Principal : " << principalId.toStdString() << std::endl;
                accountMap.insert(count, principalId);
                count++;
            }
            if (PELId.toInt() != 0) {
                std::cout << "[" << count << "] PEL : " << PELId.toStdString() << std::endl;
                accountMap.insert(count, PELId);
                count++;
            }
            if (LCId.toInt() != 0) {
                std::cout << "[" << count << "] Livret C : " << LCId.toStdString() << std::endl;
                accountMap.insert(count, LCId);
                count++;
            }

            AffSeparator();
            std::cout << "Selectionnez le compte a debiter." << std:: endl;
            int choice = stream.readLine().trimmed().toInt();
            if (!accountMap.contains(choice)) {
                qDebug() << "Choix invalide";
                return;
            }
            selectedPropId = accountMap.value(choice);
        } else {
            qDebug() << "Aucun compte trouve pour l'utilisateur specifie.";
        }


        // Partie beneficiaire -------------------
        std::system("cls");
        QSqlQuery getBeneficiaires(db);
        getBeneficiaires.prepare("SELECT "
                                 "u.firstname AS prop_firstname, "
                                 "ab.beneficiaire_id, "
                                 "a.type, "
                                 "u_beneficiary.firstname AS beneficiary_firstname, "
                                 "a_beneficiary.userId AS beneficiary_user_id "
                                 "FROM added_beneficiaires AS ab "
                                 "JOIN accounts AS a ON ab.beneficiaire_id = a.id "
                                 "JOIN users AS u ON u.id = ab.prop_id "
                                 "JOIN accounts AS a_beneficiary ON ab.beneficiaire_id = a_beneficiary.id "
                                 "JOIN users AS u_beneficiary ON a_beneficiary.userId = u_beneficiary.id "
                                 "WHERE u.id = :userId");
        getBeneficiaires.bindValue(":userId", user->getUserId());

        if (!getBeneficiaires.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête SQL";
            Sleep(3000);
            return;
        }

        // Affichage des informations récupérées
        std::cout << "Liste des comptes beneficiaires ----------------------------" << std::endl;
        QMap<int, QString> accountMap;
        int count2 = 1;
        while (getBeneficiaires.next()) {
            QString accountOwnerId = getBeneficiaires.value("beneficiary_firstname").toString();
            QString accountId = getBeneficiaires.value("beneficiaire_id").toString();
            QString accountType = getBeneficiaires.value("type").toString();

            if(accountType == "0") {
                accountType = "Courant";
            } else if (accountType == "1") {
                accountType = "PEL";
            } else if (accountType == "2") {
                accountType = "Livret C";
            }

            // Enlever le compte qui correspond au compte prop choisi.
            if(selectedPropId == accountId) {
                //continue;
            }

            std::cout << "[" << count2 << "] " << accountOwnerId.toStdString() << " (" << accountType.toStdString() << ") : " << accountId.toInt() << std::endl;
            accountMap.insert(count2, accountId);
            count2++;
        }


        AffSeparator();
        std::cout << "Selectionnez le compte a crediter." << std:: endl;
        int choice2 = stream.readLine().trimmed().toInt();
        if (!accountMap.contains(choice2)) {
            qDebug() << "Choix invalide";
            Sleep(3000);
            return;
        }

        QString selectedDestId = accountMap.value(choice2);

        // Partie du montant ---------------------
        clearScreen();
        std::cout << "Entrez le montant a envoyer : ";
        QString amount = stream.readLine().trimmed();

        operations.virement(selectedPropId.toInt(), selectedDestId.toInt(), amount.toDouble());
        user->refreshUserData();
    }

    void AffAddBeneficiaire() override {
        QTextStream stream(stdin);
        std::system("cls");
        std::cout << "Entrez l'identifiant bancaire de la personne a qui vous voulez envoyer de l'argent." << std::endl;

        QString beneficiaireId = stream.readLine().trimmed();
        user->addBeneficiaire(beneficiaireId.toInt(), user->getUserId());
    }

    void AffRetrait() override {
        QTextStream stream(stdin);
        clearScreen();

        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();
        // Vérification de la connexion
        if (!db.isValid()) {
            qDebug() << "Erreur: Aucune connexion valide à la base de données n'a été trouvée";
            return;
        }

        // Partie propriétaire -------------------
        QString selectedPropId;
        QSqlQuery getAccounts(db);
        getAccounts.prepare("SELECT "
                            "MAX(CASE WHEN a.type = 0 THEN a.id END) AS principalId, "
                            "MAX(CASE WHEN a.type = 1 THEN a.id END) AS PELId, "
                            "MAX(CASE WHEN a.type = 2 THEN a.id END) AS LCId "
                            "FROM accounts AS a "
                            "WHERE userId = :userId "
                            "AND a.type IN (0, 1, 2)");
        getAccounts.bindValue(":userId", user->getUserId());
        if (!getAccounts.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
            return ;
        }

        // Affichage des résultats
        std::cout << "Liste des comptes propriétaires ----------------------------" << std:: endl;
        if (getAccounts.next()) {
            QMap<int, QString> accountMap;
            int count = 1;
            QString principalId = getAccounts.value("principalId").toString();
            QString PELId = getAccounts.value("PELId").toString();
            QString LCId = getAccounts.value("LCId").toString();

            if (principalId.toInt() != 0) {
                std::cout << "[" << count << "] Principal : " << principalId.toStdString() << std::endl;
                accountMap.insert(count, principalId);
                count++;
            }
            if (PELId.toInt() != 0) {
                std::cout << "[" << count << "] PEL : " << PELId.toStdString() << std::endl;
                accountMap.insert(count, PELId);
                count++;
            }
            if (LCId.toInt() != 0) {
                std::cout << "[" << count << "] Livret C : " << LCId.toStdString() << std::endl;
                accountMap.insert(count, LCId);
                count++;
            }

            AffSeparator();
            std::cout << "Sélectionnez le compte sur lequel vous allez ajouter de l'argent : ";
            int choice = stream.readLine().trimmed().toInt();
            if (!accountMap.contains(choice)) {
                qDebug() << "Choix invalide";
                return;
            }
            selectedPropId = accountMap.value(choice);

            // Demander à l'utilisateur le montant à déposer
            std::cout << "Entrez le montant à déposer : ";
            QString amountStr = stream.readLine().trimmed();
            double amount = amountStr.toDouble(); // Convertir en double

            operations.removeBalance(amount, selectedPropId.toInt()); // Appel de la méthode addBalance() avec le montant spécifié
        } else {
            qDebug() << "Aucun compte trouvé pour l'utilisateur spécifié.";
        }
    }

    void AffAjout() override {
        QTextStream stream(stdin);
        clearScreen();

        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();
        // Vérification de la connexion
        if (!db.isValid()) {
            qDebug() << "Erreur: Aucune connexion valide à la base de données n'a été trouvée";
            return;
        }

        // Partie propriétaire -------------------
        QString selectedPropId;
        QSqlQuery getAccounts(db);
        getAccounts.prepare("SELECT "
                            "MAX(CASE WHEN a.type = 0 THEN a.id END) AS principalId, "
                            "MAX(CASE WHEN a.type = 1 THEN a.id END) AS PELId, "
                            "MAX(CASE WHEN a.type = 2 THEN a.id END) AS LCId "
                            "FROM accounts AS a "
                            "WHERE userId = :userId "
                            "AND a.type IN (0, 1, 2)");
        getAccounts.bindValue(":userId", user->getUserId());
        if (!getAccounts.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
            return ;
        }

        // Affichage des résultats
        std::cout << "Liste des comptes propriétaires ----------------------------" << std:: endl;
        if (getAccounts.next()) {
            QMap<int, QString> accountMap;
            int count = 1;
            QString principalId = getAccounts.value("principalId").toString();
            QString PELId = getAccounts.value("PELId").toString();
            QString LCId = getAccounts.value("LCId").toString();

            if (principalId.toInt() != 0) {
                std::cout << "[" << count << "] Principal : " << principalId.toStdString() << std::endl;
                accountMap.insert(count, principalId);
                count++;
            }
            if (PELId.toInt() != 0) {
                std::cout << "[" << count << "] PEL : " << PELId.toStdString() << std::endl;
                accountMap.insert(count, PELId);
                count++;
            }
            if (LCId.toInt() != 0) {
                std::cout << "[" << count << "] Livret C : " << LCId.toStdString() << std::endl;
                accountMap.insert(count, LCId);
                count++;
            }

            AffSeparator();
            std::cout << "Sélectionnez le compte sur lequel vous allez ajouter de l'argent : ";
            int choice = stream.readLine().trimmed().toInt();
            if (!accountMap.contains(choice)) {
                qDebug() << "Choix invalide";
                return;
            }
            selectedPropId = accountMap.value(choice);

            // Demander à l'utilisateur le montant à déposer
            std::cout << "Entrez le montant à ajouter : ";
            QString amountStr = stream.readLine().trimmed();
            double amount = amountStr.toDouble(); // Convertir en double

            operations.addBalance(amount, selectedPropId.toInt()); // Appel de la méthode addBalance() avec le montant spécifié
        } else {
            qDebug() << "Aucun compte trouvé pour l'utilisateur spécifié.";
        }
    }


    void AffHistory() override {
        QTextStream stream(stdin);
        clearScreen();


        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();

        // Vérifier si la connexion à la base de données est valide
        if (db.isValid()) {
            // Exécuter la requête SQL pour récupérer les données de l'historique
            QSqlQuery query(db);
            query.prepare("SELECT * FROM history WHERE id_compte_emetteur = :id ORDER BY date DESC");
            query.bindValue(":id", user->getUserId());

            if (!query.exec()) {
                std::cout << "Erreur lors de l'execution de la requete : " << query.lastError().text().toStdString() << std::endl;
                return;
            }

            // Itérer sur les résultats de la requête
            while (query.next()) {
                // Récupérer les valeurs des colonnes
                int id_history = query.value(0).toInt();
                double montant = query.value(1).toDouble();
                QDateTime date = query.value(2).toDateTime();
                int id_compte_emetteur = query.value(3).toInt();
                int id_compte_destinataire = query.value(4).toInt();
                QString type = query.value(5).toString();
                if (query.value(5) == 0) {
                    type = "Virement";
                } else if (query.value(5) == 1) {
                    type = "Credit";
                } else if (query.value(5) == 2) {
                    type = "Debit";
                }
                QString title = query.value(6).toString();
                QString description = query.value(7).toString();

                // Afficher les valeurs récupérées sur la console avec un menu
                std::cout << "Titre: " << title.toStdString() << std::endl;
                std::cout << "Description: " << description.toStdString() << std::endl;
                std::cout << "Montant: " << montant << " euros" << std::endl;
                std::cout << "Date: " << date.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
                std::cout << "Type: " << type.toStdString() << std::endl;
                if(type == "Virement") {
                    std::cout << "Compte emetteur: " << id_compte_emetteur << std::endl;
                    std::cout << "Compte destinataire: " << id_compte_destinataire << std::endl;
                }
                std::cout << "-------------------------" << std::endl;
            }
        } else {
            std::cout << "Erreur : Connexion a la base de donnees invalide" << std::endl;
        }


        std::cout << "Pour retourner a l'accueil, appuyez sur une touche." << std::endl;
        getch();
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

    void AffMainPage() override {}

    void AffAdminPage() override {}

    void CreationCompte() override {}

    void AffVirement() override{}

    void AffAddBeneficiaire() override{}

    void AffRetrait() override {}

    void AffHistory() override {}

    void AffAjout() override {}
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


