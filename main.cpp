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
#include "f_admin.h"

class UI {
public:
    virtual void AffLogin()=0;
    virtual void AffMainPage()=0;
    virtual void AffAdminPage()=0;
    virtual void AffCreationCompte()=0;
    virtual void AffVirement()=0;
    virtual void AffAddBeneficiaire()=0;
    virtual void AffRetrait()=0;
    virtual void AffHistory(User& user)=0;
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
        std::cout << "Bienvenue " << user->getActual_firstname().toStdString() << "." << std::endl;
        if(user->getActual_type() == 1) std::cout << "Vous etes connecte en tant que conjoint." << std::endl;
        std::cout << "\nVos comptes bancaires --------------------------------------" << std::endl;
        // Si le compte a un ID, alors on affiche le compte.
        if(user->getPpl_id()) {
            std::cout << "Compte courant : " << user->getPpl_balance() << " euros." << std::endl;
        }
        if(user->getPel_id()) {
            std::cout << "Compte PEL : " << user->getPel_balance() << " euros." << std::endl;
        }
        if(user->getLvc_id()) {
            std::cout << "Compte Livret C : " << user->getLvc_balance() << " euros." << std::endl;
        }
        AffSeparator();
        if (user->getActual_type() == 1) {
            AffMsg("[9] Deconnexion");
        } else {
            if (user->getRole() != 1) {
                AffMsg("[1] Realiser un transfert \n[2] Ajouter un beneficiaire \n[3] Retirer de l'argent \n[4] Deposer de l'argent \n[5] Consulter l'historique \n\n[9] Deconnexion");
            } else {
                AffMsg("[1] Realiser un transfert \n[2] Ajouter un beneficiaire \n[3] Retirer de l'argent \n[4] Deposer de l'argent \n[5] Consulter l'historique \n\n[8] Revenir en arriere\n[9] Deconnexion");
            }
        }

        QString choice = stream.readLine().trimmed();
        //operations.defaultChoices(choice);

        if (choice == "9") {
            user->disconnect();
            AffLogin();
        } else if (choice == "1" && user->getActual_type() != 1) {
            AffVirement();
        } else if (choice == "2" && user->getActual_type() != 1) {
            AffAddBeneficiaire();
        } else if (choice == "3" && user->getActual_type() != 1) {
            AffRetrait();
        } else if (choice == "4" && user->getActual_type() != 1) {
            AffAjout();
        } else if (choice == "5" && user->getActual_type() != 1) {
            AffHistory(*user);
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
        std::cout << "Bienvenue " << user->getActual_firstname().toStdString() << ", que voulez-vous faire ?" << std::endl;
        AffMsg("[1] Acceder au panel admin");
        AffMsg("[2] Acceder votre espace client");
        QString choice =stream.readLine().trimmed();
        if(choice == "1") {
            AffCreationCompte();
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
        getBeneficiaires.prepare("SELECT DISTINCT u_prop.id AS prop_uid, p_prop.firstname AS prop_firstname, "
                                 "a_dest.id AS dest_acc_id , u_dest.username AS dest_firstname, a_dest.type AS dest_acc_type "
                                    "FROM saved_accounts AS sa "
                                    "LEFT JOIN users AS u_prop ON u_prop.id = sa.user_id "
                                    "LEFT JOIN accounts AS a_prop ON a_prop.userId = u_prop.id "
                                    "LEFT JOIN profil AS p_prop ON p_prop.user_id = u_prop.id "
                                    "LEFT JOIN accounts AS a_dest ON a_dest.id = sa.account_id "
                                    "LEFT JOIN users AS u_dest ON u_dest.id = a_dest.userId "
                                    "LEFT JOIN profil AS p_dest ON p_dest.user_id = u_dest.id "
                                    "WHERE u_prop.id =  :userId");
        getBeneficiaires.bindValue(":userId", user->getUserId());

        if (!getBeneficiaires.exec()) {
            qDebug() << "Erreur lors de l'execution de la requête SQL";
            Sleep(3000);
            return;
        }

        // Affichage des informations récupérées
        std::cout << "Liste des comptes beneficiaires ----------------------------" << std::endl;
        QMap<int, QString> accountMap;
        int count2 = 1;
        while (getBeneficiaires.next()) {
            QString accountOwnerId = getBeneficiaires.value("dest_firstname").toString();
            QString accountId = getBeneficiaires.value("dest_acc_id").toString();
            QString accountType = getBeneficiaires.value("dest_acc_type").toString();

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
            qDebug() << "Erreur: Aucune connexion valide a la base de donnees n'a ete trouvee";
            return;
        }

        // Partie propriétaire -------------------
        QString selectedPropId;
        QSqlQuery getAccounts(db);
        getAccounts.prepare("SELECT "
                            "MAX(CASE WHEN a.type = 0 THEN a.id END) AS principalId, "
                            "MAX(CASE WHEN a.type = 2 THEN a.id END) AS LCId "
                            "FROM accounts AS a "
                            "WHERE userId = :userId "
                            "AND a.type IN (0, 1, 2)");
        getAccounts.bindValue(":userId", user->getUserId());
        if (!getAccounts.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requete : " << getAccounts.lastError().text();
            return ;
        }

        // Affichage des résultats
        std::cout << "Liste des comptes proprietaires ----------------------------" << std:: endl;
        if (getAccounts.next()) {
            QMap<int, QString> accountMap;
            int count = 1;
            QString principalId = getAccounts.value("principalId").toString();
            QString LCId = getAccounts.value("LCId").toString();

            if (principalId.toInt() != 0) {
                std::cout << "[" << count << "] Principal : " << principalId.toStdString() << std::endl;
                accountMap.insert(count, principalId);
                count++;
            }
            if (LCId.toInt() != 0) {
                std::cout << "[" << count << "] Livret C : " << LCId.toStdString() << std::endl;
                accountMap.insert(count, LCId);
                count++;
            }

            AffSeparator();
            std::cout << "Selectionnez le compte sur lequel vous allez retirer de l'argent : ";
            int choice = stream.readLine().trimmed().toInt();
            if (!accountMap.contains(choice)) {
                qDebug() << "Choix invalide";
                return;
            }
            selectedPropId = accountMap.value(choice);

            // Demander à l'utilisateur le montant à déposer
            std::cout << "Entrez le montant a retirer : ";
            QString amountStr = stream.readLine().trimmed();
            double amount = amountStr.toDouble();

            operations.removeBalance(amount, selectedPropId.toInt(), "Retrait DAB");
        } else {
            qDebug() << "Aucun compte trouve pour l'utilisateur specifie.";
        }
    }

    int AffUserAccountsChoice(int userId) {

        QTextStream stream(stdin);

        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();
        // Vérification de la connexion
        if (!db.isValid()) {
            qDebug() << "Erreur: Aucune connexion valide à la base de données n'a été trouvée";
            return -1;
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
        getAccounts.bindValue(":userId", userId);
        if (!getAccounts.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
            return -1;
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
                return -1;
            }
            selectedPropId = accountMap.value(choice);
            return selectedPropId.toInt();
        } else {
            qDebug() << "Aucun compte trouvé pour l'utilisateur spécifié.";
            return -1;
        }
        return -1;
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
        getAccounts.prepare("SELECT a.id AS principalId "
                            "FROM accounts AS a "
                            "WHERE userId = :userId AND a.type = 0");
        getAccounts.bindValue(":userId", user->getUserId());
        if (!getAccounts.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête : " << getAccounts.lastError().text();
            return ;
        }

        // Affichage des résultats
        std::cout << "Liste des comptes proprietaires ----------------------------" << std:: endl;
        if (getAccounts.next()) {
            QMap<int, QString> accountMap;
            int count = 1;
            QString principalId = getAccounts.value("principalId").toString();

            std::cout << "Entrez le montant a ajouter : ";
            QString amountStr = stream.readLine().trimmed();
            double amount = amountStr.toDouble();

            operations.addBalance(amount, principalId.toInt(), "description a completer");
        } else {
            qDebug() << "Aucun compte trouvé pour l'utilisateur spécifié.";
            Sleep(3000);
        }
    }

    void AffHistory(User& user) override {
        QTextStream stream(stdin);
        clearScreen();


        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();

        // Vérifier si la connexion à la base de données est valide
        if (db.isValid()) {
            // Exécuter la requête SQL pour récupérer les données de l'historique
            QSqlQuery query(db);
            query.prepare("SELECT * FROM history "
                          "WHERE id_compte_emetteur = :PplId "
                          "OR id_compte_emetteur = :PelId "
                          "OR id_compte_emetteur = :LvcId "
                          "OR id_compte_destinataire = :PplId "
                          "OR id_compte_destinataire = :PelId "
                          "OR id_compte_destinataire = :LvcId "
                          "ORDER BY date ASC");
            query.bindValue(":PplId", user.getPpl_id());
            query.bindValue(":PelId", user.getPel_id());
            query.bindValue(":LvcId", user.getLvc_id());

            if (!query.exec()) {
                std::cout << "Erreur lors de l'execution de la requete : " << query.lastError().text().toStdString() << std::endl;
                Sleep(3000);
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

    void AffHistoryAdmin(User& user) {
        QTextStream stream(stdin);
        clearScreen();


        // Récupération de la connexion existante à la base de données
        QSqlDatabase db = QSqlDatabase::database();

        // Vérifier si la connexion à la base de données est valide
        if (db.isValid()) {
            // Exécuter la requête SQL pour récupérer les données de l'historique
            QSqlQuery query(db);
            query.prepare("SELECT * FROM history_admin "
                          "WHERE user_id = :userId "
                          "ORDER BY date ASC");
            query.bindValue(":userId", user.getUserId());

            if (!query.exec()) {
                std::cout << "Erreur lors de l'execution de la requete : " << query.lastError().text().toStdString() << std::endl;
                Sleep(3000);
                return;
            }

            // Itérer sur les résultats de la requête
            while (query.next()) {
                // Récupérer les valeurs des colonnes
                int id_history = query.value(0).toInt();
                double userId = query.value(1).toInt();
                QDateTime date = query.value(2).toDateTime();
                QString type = query.value(3).toString();
                QString description = query.value(4).toString();
                if (query.value(3) == 0) {
                    type = "Connexion";
                } else if (query.value(3) == 1) {
                    type = "Consultation";
                } else if (query.value(3) == 2) {
                    type = "Operation";
                }

                // Afficher les valeurs récupérées sur la console avec un menu
                std::cout << "ID de l'utilisateur: " << userId << std::endl;
                std::cout << "Date: " << date.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
                std::cout << "Description: " << description.toStdString() << std::endl;
                std::cout << "Type: " << type.toStdString() << std::endl;
                std::cout << "-------------------------" << std::endl;
            }
        } else {
            std::cout << "Erreur : Connexion a la base de donnees invalide" << std::endl;
        }


        std::cout << "Pour retourner a l'accueil, appuyez sur une touche." << std::endl;
        getch();
    }

    void AffCreationCompte() override {
        QTextStream stream(stdin);
        clearScreen();

        // Affichage du menu
        std::cout << "Outil de creation de comptes -------------------------------" << std:: endl;
        std::cout << "[1] Creer un compte utilisateur" << std:: endl;
        std::cout << "[2] Creer un profil" << std:: endl;
        std::cout << "[3] Creer un compte en banque" << std:: endl;
        std::cout << "[4] Consulter compte client" << std:: endl;
        int profilType = user->getActual_type();
        std::cout << "\n[8] Retour" << std:: endl;
        QString choice;
        int newUserId = 0;
        do {
            choice = stream.readLine().trimmed();
            if(choice.toInt() == 8) {
                return;
            }
        } while (choice.toInt() < 1 || choice.toInt() > 4);

        if(choice.toInt() == 1) {
            newUserId = AffCreateUser();
            std::cout << "Continuer sur la creation d'un profil ? o/n" << std:: endl;
            QString continueChoice = stream.readLine().trimmed();
            if (continueChoice == "o" || continueChoice == "oui"){
                AffCreateProfil(newUserId);
            } else {
                return;
            }
            Sleep(2000);
        } else if (choice.toInt() == 2) {
            std::cout << "Veuillez entrer l'id de l'user : ";
            QString userId = stream.readLine().trimmed();
            int profileId = AffCreateProfil(userId.toInt());

            std::cout << "Continuer sur la creation d'un compte bancaire ? o/n" << std:: endl;
            QString continueChoice = stream.readLine().trimmed();
            if (continueChoice == "o" || continueChoice == "oui"){
                AffCreateAccount();
            } else {
                return;
            }
            Sleep(2000);
        } else if (choice.toInt() == 3) {
            AffCreateAccount();
        } else if (choice.toInt() == 4) {
            AffCheckUser(user->getActual_type());
        } else if (choice.toInt() == 5) {
            std::cout << "Choix de l'admin - employe";
            Sleep(3000);
        } else if (choice.toInt() == 6) {
            std::cout << "Choix de l'admin - directeur";
            Sleep(3000);
        }
    }

    int AffCheckUser(int userType) {
        QTextStream stream(stdin);
        clearScreen();
        std::cout << "Entrez le nom de l'utilisateur : ";
        QString username = stream.readLine().trimmed();

        // Afficher la liste
        // Effectuer la requête pour rechercher les utilisateurs par nom

        QMap<int, QString> accountMap;
        QSqlQuery query;
        if (userType == 10 || userType == 11) {
            query.prepare("SELECT p.firstname AS firstname, p.lastname AS lastname, u.id AS id "
                          "FROM users AS u "
                          "LEFT JOIN profil AS p ON (p.user_id = u.id AND (p.type = 1 OR p.type = 0)) "
                          "WHERE p.firstname = :firstname");
        } else if (userType == 12) {
            query.prepare("SELECT p.firstname AS firstname, p.lastname AS lastname, u.id AS id "
                          "FROM users AS u "
                          "LEFT JOIN profil AS p ON (p.user_id = u.id AND (p.type = 1 OR p.type = 0 OR p.type = 10 OR p.type = 11)) "
                          "WHERE p.firstname = :firstname");
        }
        query.bindValue(":firstname", username);

        if (query.exec()) {
            int count = 0;
            // Parcourir les résultats de la requête et afficher dans la liste
            while (query.next()) {
                QString firstname = query.value("firstname").toString();
                QString lastname = query.value("lastname").toString();
                QString id = query.value("id").toString();
                std::cout << "[" << count << "] " << firstname.toStdString() << " " << lastname.toStdString() << " (PID:" << id.toStdString() << ")"<< std::endl;
                accountMap.insert(count, id);
                count++;
            }
        } else {
            qDebug() << "Erreur lors de l'execution de la requete : " << query.lastError().text();
        }
        AffSeparator();
        std::cout << "\nSelectionnez le compte utilisateur a verifier : ";
        int choice = stream.readLine().trimmed().toInt();
        if (!accountMap.contains(choice)) {
            qDebug() << "Choix invalide";
            return -1;
        }
        // Récupération de l'ID sélectionné
        QString selectedUserId = accountMap.value(choice);
        User userToCheck;
        // Charger les informations de l'utilisateur sélectionné
        userToCheck.getInformations(selectedUserId.toInt());
        f_admin admin;
        QString admin_consultation_desc = QString("Consultation du compte de l'utilisateur %1 (UID: %2) par %3.").arg(userToCheck.getUsername()).arg(userToCheck.getUserId()).arg(user->getActual_firstname());
        admin.saveToHistoryAdmin(user->getUserId(), 1, admin_consultation_desc);


        clearScreen();
        std::cout << "Les informations de l'user ---------------------------------" << std::endl;
        std::cout << "Username : " << userToCheck.getUsername().toStdString() << std::endl;
        std::cout << "User ID : " << userToCheck.getUserId() << std::endl;

        std::cout << "\nLes differents profils -------------------------------------" << std::endl;
        if (userToCheck.getRole() == 0) {
            std::cout << "Proprietaire -----------------------------------------------" << std::endl;
            if (userToCheck.getOwner_profilId()) {
                std::cout << "Prenom du proprietaire : " << userToCheck.getOwner_firstname().toStdString() << std::endl;
                std::cout << "Nom de famille du proprietaire : " << userToCheck.getOwner_lastname().toStdString() << std::endl;
                std::cout << "Login du proprietaire : " << userToCheck.getOwner_login().toStdString() << std::endl;
                std::cout << "ID du profil proprietaire : " << userToCheck.getOwner_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil proprietaire." << std::endl;
            }


            std::cout << "Conjoint ---------------------------------------------------" << std::endl;
            if (userToCheck.getCoowner_profilId()) {

                std::cout << "Prenom du conjoint : " << userToCheck.getCoowner_firstname().toStdString() << std::endl;
                std::cout << "Nom de famille du conjoint : " << userToCheck.getCoowner_lastname().toStdString() << std::endl;
                std::cout << "Login du conjoint : " << userToCheck.getCoowner_login().toStdString() << std::endl;
                std::cout << "ID du profil conjoint : " << userToCheck.getCoowner_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil conjoint." << std::endl;
            }
        }

        if (userToCheck.getRole() == 1) {
            std::cout << "Proprietaire -----------------------------------------------" << std::endl;
            if (userToCheck.getOwner_profilId()) {
                std::cout << "Prenom du proprietaire : " << userToCheck.getOwner_firstname().toStdString() << std::endl;
                std::cout << "Nom de famille du proprietaire : " << userToCheck.getOwner_lastname().toStdString() << std::endl;
                std::cout << "Login du proprietaire : " << userToCheck.getOwner_login().toStdString() << std::endl;
                std::cout << "ID du profil proprietaire : " << userToCheck.getOwner_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil proprietaire." << std::endl;
            }


            std::cout << "Conjoint ---------------------------------------------------" << std::endl;
            if (userToCheck.getCoowner_profilId()) {

                std::cout << "Prenom du conjoint : " << userToCheck.getCoowner_firstname().toStdString() << std::endl;
                std::cout << "Nom de famille du conjoint : " << userToCheck.getCoowner_lastname().toStdString() << std::endl;
                std::cout << "Login du conjoint : " << userToCheck.getCoowner_login().toStdString() << std::endl;
                std::cout << "ID du profil conjoint : " << userToCheck.getCoowner_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil conjoint." << std::endl;
            }

            std::cout << "Stagiaire --------------------------------------------------" << std::endl;
            if (userToCheck.getIntern_profilId()) {

                std::cout << "Prenom du stagiaire : " << userToCheck.getIntern_firstname().toStdString() << std::endl;
                std::cout << "Nom de famille du stagiaire : " << userToCheck.getIntern_lastname().toStdString() << std::endl;
                std::cout << "Login du stagiaire : " << userToCheck.getIntern_login().toStdString() << std::endl;
                std::cout << "ID du profil stagiaire : " << userToCheck.getIntern_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil stagiaire." << std::endl;
            }

            std::cout << "Employe ----------------------------------------------------" << std::endl;
            if (userToCheck.getEmployee_profilId()) {

                std::cout << "Prenom de l'employe : " << userToCheck.getEmployee_firstname().toStdString() << std::endl;
                std::cout << "Nom de l'employe : " << userToCheck.getEmployee_lastname().toStdString() << std::endl;
                std::cout << "Login de l'employe : " << userToCheck.getEmployee_login().toStdString() << std::endl;
                std::cout << "ID du profil de l'employe : " << userToCheck.getEmployee_profilId() << std::endl;
            } else {
                std::cout << "Cet utilisateur n'a pas de profil employe." << std::endl;
            }
        }



        std::cout << "\nLes comptes bancaires --------------------------------------" << std::endl;
        if(userToCheck.getPpl_id()) {
            if (user->getActual_type() == 10) {
                std::cout << "Compte courant : censure." << std::endl;
            } else {
                std::cout << "Compte courant : " << userToCheck.getPpl_balance() << " euros." << std::endl;
            }
        } else {
            std::cout << "Cet user n'a pas de compte courant" << std::endl;
        }
        if(userToCheck.getPel_id()) {
            if (user->getActual_type() == 10) {
                std::cout << "Compte courant : censure." << std::endl;
            } else {
                std::cout << "Compte PEL : " << userToCheck.getPel_balance() << " euros." << std::endl;
            }
        } else {
            std::cout << "Cet user n'a pas de compte PEL" << std::endl;
        }
        if(userToCheck.getLvc_id()) {
            if (user->getActual_type() == 10) {
                std::cout << "Compte courant : censure." << std::endl;
            } else {
                std::cout << "Compte Livret C : " << userToCheck.getLvc_balance() << " euros." << std::endl;
            }
        } else {
            std::cout << "Cet user n'a pas de compte Livret C" << std::endl;
        }

        if (user->getActual_type() != 10) {
            std::cout << "\nActions ----------------------------------------------------"<< std::endl;
            if (userToCheck.getPpl_id() || userToCheck.getPel_id() || userToCheck.getLvc_id()) {
                std::cout << "[1] Visualiser historique" << std::endl;
                std::cout << "[2] Crediter des fonds" << std::endl;
                std::cout << "[3] Debiter des fonds" << std::endl;
                std::cout << "Selectionnez ce que vous souhaitez realiser : " ;
                QTextStream stream(stdin);
                QString choice = stream.readLine().trimmed();

                if (choice.toInt() == 1 && (userToCheck.getPpl_id() || userToCheck.getPel_id() || userToCheck.getLvc_id())) {
                    AffHistory(userToCheck);
                } else if (choice.toInt() == 2 && (userToCheck.getPpl_id() || userToCheck.getPel_id() || userToCheck.getLvc_id())) {
                    clearScreen();
                    int userAccountId = AffUserAccountsChoice(userToCheck.getUserId());
                    clearScreen();
                    std::cout << "Entrez le montant a ajouter : " << std::endl;
                    QString amount = stream.readLine().trimmed();
                    operations.addBalance(amount.toDouble(), userAccountId, "Ajout administrateur.");
                    f_admin admin;
                    QString username = user->getActual_firstname();
                    QString admin_his_desc = QString("Ajout de %1€ a l'utilisateur par %2").arg(amount).arg(username);
                    admin.saveToHistoryAdmin(user->getUserId(), 2, admin_his_desc);
                } else if (choice.toInt() == 3 && (userToCheck.getPpl_id() || userToCheck.getPel_id() || userToCheck.getLvc_id())) {
                    clearScreen();
                    int userAccountId = AffUserAccountsChoice(userToCheck.getUserId());
                    clearScreen();
                    std::cout << "Entrez le montant a ajouter : " << std::endl;
                    QString amount = stream.readLine().trimmed();
                    operations.removeBalance(amount.toDouble(), userAccountId, "Retrait administrateur.");
                    f_admin admin;
                    QString username = user->getActual_firstname();
                    QString admin_his_desc = QString("Retrait de %1€ a l'utilisateur par %2").arg(amount).arg(username);
                    admin.saveToHistoryAdmin(user->getUserId(), 2, admin_his_desc);
                } else {
                    return -1;
                }
            } else if (userToCheck.getRole() == 1) {
                std::cout << "[1] Visualiser historique administrateur" << std::endl;
                QTextStream stream(stdin);
                QString choice = stream.readLine().trimmed();
                if(choice.toInt() == 1) {
                    AffHistoryAdmin(userToCheck);
                }
            } else {
                std::cout << "\nPour retourner a l'accueil, appuyez sur une touche." << std::endl;
                getch();
            }
        } else {
            std::cout << "\nPour retourner a l'accueil, appuyez sur une touche." << std::endl;
            getch();
        }
    }

    int AffCreateUser() {
        f_admin admin;
        QTextStream stream(stdin);
        clearScreen();

        std::cout << "Entrez le nom de l'user : ";
        QString username = stream.readLine().trimmed();

        clearScreen();
        std::cout << "Choisissez le role de l'user : " << std:: endl;
        std::cout << "[1] Utilisateur " << std:: endl;
        std::cout << "[2] Administrateur " << std:: endl;
        std::cout << "Votre choix : ";
        QString roleString = stream.readLine().trimmed();
        int role = roleString.toInt() - 1;

        clearScreen();
        int newUserId = admin.createUser(username, role);
        if(newUserId && user->getRole() == 1 ) {
            std::cout << "Compte " << newUserId << " cree avec succes." << std:: endl;
        } else {
            std::cout << "Une erreur est survenue lors de la creation du compte user." << std:: endl;
        }
        Sleep(1500);

        clearScreen();

        if(roleString.toInt() == 1) {
            roleString = "Utilisateur";
        } else if (roleString.toInt() == 2) {
            roleString = "Administrateur";
        }

        std::cout << "----------------------" << std:: endl;
        std::cout << "        RESUME        "<< std:: endl;
        std::cout << "----------------------" << std:: endl;
        std::cout << "Nom : " << username.toStdString() << std:: endl;
        std::cout << "Role : " << roleString.toStdString() << std:: endl;
        std::cout << "Id : " << newUserId << std:: endl;
        std::cout << "----------------------" << std:: endl;

        return newUserId;
    };

    void AffCreateAccount() {
        f_admin admin;
        QTextStream stream(stdin);

        clearScreen();
        std::cout << "Entrez le nom de l'utilisateur : ";
        QString username = stream.readLine().trimmed();

        // Afficher la liste
        // Effectuer la requête pour rechercher les utilisateurs par nom

        QMap<int, QString> accountMap;
        QSqlQuery query;
        query.prepare("SELECT p.firstname AS firstname, p.lastname AS lastname, u.id AS id "
                      "FROM users AS u "
                      "LEFT JOIN profil AS p ON (p.user_id = u.id AND (p.type = 1 OR p.type = 0)) "
                      "WHERE p.firstname = :firstname");
        query.bindValue(":firstname", username);

        if (query.exec()) {
            int count = 0;
            // Parcourir les résultats de la requête et afficher dans la liste
            while (query.next()) {
                QString firstname = query.value("firstname").toString();
                QString lastname = query.value("lastname").toString();
                QString id = query.value("id").toString();
                std::cout << "[" << count << "] " << firstname.toStdString() << " " << lastname.toStdString() << " (PID:" << id.toStdString() << ")"<< std::endl;
                accountMap.insert(count, id);
                count++;
            }
        } else {
            qDebug() << "Erreur lors de l'execution de la requete : " << query.lastError().text();
        }
        AffSeparator();
        std::cout << "\nSelectionnez le compte utilisateur : ";
        int choice = stream.readLine().trimmed().toInt();
        if (!accountMap.contains(choice)) {
            qDebug() << "Choix invalide";
            return;
        }
        // Récupération de l'ID sélectionné
        QString selectedUserId = accountMap.value(choice);
        User userToCheck;
        // Charger les informations de l'utilisateur sélectionné
        userToCheck.getInformations(selectedUserId.toInt());
        int userId = userToCheck.getUserId();

        clearScreen();

        bool userHavePplAcc = admin.checkUserAccountType(userId, 0);
        bool userHavePelAcc = admin.checkUserAccountType(userId, 1);
        bool userHaveLvcAcc = admin.checkUserAccountType(userId, 2);

        if (userHavePplAcc && userHavePelAcc && userHaveLvcAcc) {
            std::cout << "Cet utilisateur possede deja tous les types de comptes. Retour a l'accueil..." << std::endl;
            Sleep(3000);
            return;
        }

        QMap<int, int> accountTypeMap;
        int count = 1;

        if (!userHavePplAcc) {
            std::cout << "[" << count << "] Compte courant" << std::endl;
            int accountType = 0;
            accountTypeMap.insert(count, accountType);
            count++;
        }
        if (!userHavePelAcc) {
            std::cout << "[" << count << "] Compte PEL" << std::endl;
            int accountType = 1;
            accountTypeMap.insert(count, accountType);
            count++;
        }
        if (!userHaveLvcAcc) {
            std::cout << "[" << count << "] Compte Livret C" << std::endl;
            int accountType = 2;
            accountTypeMap.insert(count, accountType);
            count++;
        }
        std::cout << "[" << count << "] Retour" << std::endl;
        accountTypeMap.insert(count, -1);

        AffSeparator();
        std::cout << "Selectionnez le compte a creer : ";
        QString accountChoice = stream.readLine().trimmed();

        if (accountTypeMap.value(accountChoice.toInt()) == -1) {
            return;
        }

        while (!accountTypeMap.contains(accountChoice.toInt())) {
            std::cout << "Choix invalide" << std::endl;
            Sleep(1000);
        }

        int selectedAccountType = accountTypeMap.value(accountChoice.toInt());

        clearScreen();
        QString baseBalance = "-1";
        while (baseBalance.toInt() < 0) {
            std::cout << "Solde de base (0 si aucun) : " << std::endl;
            baseBalance = stream.readLine().trimmed();
        }

        if (admin.createAccount(userId, selectedAccountType, baseBalance.toDouble())) {
            std::cout << "Compte bancaire cree et lie avec succes." << std::endl;
        } else {
            std::cout << "Une erreur est survenue lors de la creation du compte bancaire." << std::endl;
        }
        Sleep(1500);
        clearScreen();

        User newUser;
        newUser.getInformations(userId);

        std::cout << "----------------------" << std::endl;
        std::cout << "        RESUME        " << std::endl;
        std::cout << "----------------------" << std::endl;
        std::cout << "Type : " << selectedAccountType << std::endl;
        std::cout << "Solde : " << baseBalance.toStdString() << std::endl;
        std::cout << "----------------------" << std::endl;
        std::cout << "Nom : " << newUser.getUsername().toStdString() << std::endl;
        std::cout << "Role : " << newUser.getRole() << std::endl;
        std::cout << "Id : " << newUser.getUserId() << std::endl;
        std::cout << "----------------------" << std::endl;
    }

    int AffCreateProfil(int userId) {
        f_admin admin;
        QTextStream stream(stdin);
        clearScreen();

        if (!userId){
            std::cout << "Id user non detecte, veuillez entrer celui-ci : ";
            QString choice =stream.readLine().trimmed();
            clearScreen();
        }

        // Check si le compte a deja un profil proprietaire, si oui, alors creation profil conjoint, sinon creation profil proprietaire
        int profileExists = user->checkIfProfileExists(userId);
        if (profileExists != -1 && profileExists != -2) {
            User newUser;
            if (profileExists == 0) {
                // Creation de profil prop
                std::cout << "Entrez le prenom du profil : ";
                QString firstname =stream.readLine().trimmed();
                clearScreen();
                std::cout << "Entrez le nom de famille du profil : ";
                QString lastname =stream.readLine().trimmed();
                clearScreen();
                std::cout << "Entrez le login du profil : ";
                QString login =stream.readLine().trimmed();
                clearScreen();

                // Generer le password.
                QString password = user->generateRandomPassword();

                QString roleString = 0;
                int role = 0;
                if(newUser.getRole() == 1) {
                    // Si l'user est admin
                    std::cout << "Choisissez le role du profil : " << std:: endl;
                    std::cout << "[1] Stagiaire " << std:: endl;
                    std::cout << "[2] Employe " << std:: endl;
                    std::cout << "[3] Directeur " << std:: endl;
                    std::cout << "Votre choix : ";
                    while (roleString.toInt() != 1 && roleString.toInt() != 2 && roleString.toInt() != 3) {
                        roleString = stream.readLine().trimmed();
                    }
                    role = roleString.toInt() + 9; // +10 -1
                } else {
                    // Si l'user est user
                    std::cout << "Choisissez le role du profil : " << std:: endl;
                    std::cout << "[1] Proprietaire " << std:: endl;
                    std::cout << "[2] Conjoint " << std:: endl;
                    std::cout << "Votre choix : ";
                    while (roleString.toInt() != 1 && roleString.toInt() != 2) {
                        roleString = stream.readLine().trimmed();
                    }
                    role = roleString.toInt() - 1;
                }
                if (role == 0) {
                    roleString = "Proprietaire";
                } else if (role == 1) {
                    roleString = "Conjoint";
                } else if (role == 10) {
                    roleString = "Stagiaire";
                } else if (role == 11) {
                    roleString = "Employe";
                } else if (role == 12) {
                    roleString = "Directeur";
                }

                clearScreen();
                if (admin.createProfil(userId, firstname, lastname, login, password, role)){
                    std::cout << "----------------------" << std:: endl;
                    std::cout << "        RESUME        "<< std:: endl;
                    std::cout << "----------------------" << std:: endl;
                    std::cout << "Firstname : " << firstname.toStdString() << std:: endl;
                    std::cout << "Lastname : " << lastname.toStdString() << std:: endl;
                    std::cout << "Login : " << login.toStdString() << std:: endl;
                    std::cout << "Password : " << password.toStdString() << std:: endl;
                    std::cout << "Role : " << roleString.toStdString() << std:: endl;
                    std::cout << "----------------------" << std:: endl;
                    Sleep(5000);
                } else {
                    std::cout << "Un erreur est survenue lors de la création du profil.";
                    Sleep(2000);
                }
            } else if(profileExists == 1) {
                // Profil prop trouve.
                // Creation de profil con
                std::cout << "Entrez le prenom du profil : ";
                QString firstname =stream.readLine().trimmed();
                clearScreen();
                std::cout << "Entrez le nom de famille du profil : ";
                QString lastname =stream.readLine().trimmed();
                clearScreen();
                std::cout << "Entrez le login du profil : ";
                QString login =stream.readLine().trimmed();
                clearScreen();

                // Generer le password.
                QString password = user->generateRandomPassword();

                // Si l'user est de type = 1, alors Stagiaire..., sinon : type = 0
                std::cout << "Choisissez le role du profil : " << std:: endl;
                std::cout << "[1] Proprietaire " << std:: endl;
                std::cout << "[2] Conjoint " << std:: endl;
                std::cout << "Votre choix : ";

                QString roleString = 0;
                int role = 1;
                if (role == 0) {
                    roleString = "Proprietaire";
                } else if (role == 1) {
                    roleString = "Conjoint";
                } else if (role == 10) {
                    roleString = "Stagiaire";
                } else if (role == 11) {
                    roleString = "Employe";
                } else if (role == 12) {
                    roleString = "Directeur";
                }

                clearScreen();
                if (user->createProfil(userId, firstname, lastname, login, password, role)){
                    std::cout << "----------------------" << std:: endl;
                    std::cout << "        RESUME        "<< std:: endl;
                    std::cout << "----------------------" << std:: endl;
                    std::cout << "Firstname : " << firstname.toStdString() << std:: endl;
                    std::cout << "Lastname : " << lastname.toStdString() << std:: endl;
                    std::cout << "Login : " << login.toStdString() << std:: endl;
                    std::cout << "Password : " << password.toStdString() << std:: endl;
                    std::cout << "Role : " << role << std:: endl;
                    std::cout << "----------------------" << std:: endl;
                    Sleep(5000);
                } else {
                    std::cout << "Un erreur est survenue lors de la création du profil.";
                    Sleep(2000);
                }
            } else if (profileExists == 2) {
                // Profil con trouve.
                // Check si l'user a un profil prop
                if(user->checkIfProfileExists(userId) == 1) {
                    // Si oui : bloquer
                    std::cout << "Des profils sont deja existants sur cet user." ;
                    Sleep(3000);
                    return -1;
                } else {
                    // Profil prop trouve.
                    // Creation de profil con
                    std::cout << "Entrez le prenom du profil du conjoint : ";
                    QString firstname =stream.readLine().trimmed();
                    clearScreen();
                    std::cout << "Entrez le nom de famille du profil : ";
                    QString lastname =stream.readLine().trimmed();
                    clearScreen();
                    std::cout << "Entrez le login du profil : ";
                    QString login =stream.readLine().trimmed();
                    clearScreen();

                    // Generer le password.
                    QString password = user->generateRandomPassword();

                    QString roleString = 0;
                    int role = 0;

                    if(user->checkIfUserIsAdmin(userId)) {
                        std::cout << "Choisissez le role du profil : " << std:: endl;
                        std::cout << "[1] Stagiaire " << std:: endl;
                        std::cout << "[2] Employe " << std:: endl;
                        std::cout << "[3] Directeur " << std:: endl;
                        std::cout << "Votre choix : ";

                        while (roleString.toInt() != 1 && roleString.toInt() != 2 && roleString.toInt() != 3) {
                            roleString = stream.readLine().trimmed();
                        }
                        role = roleString.toInt() - 1;
                        if (role == 0) {
                            roleString = "Stagiaire";
                        } else if (role == 1) {
                            roleString = "Employe";
                        } else if (role == 2) {
                            roleString = "Directeur";
                        }
                    } else {
                        std::cout << "Choisissez le role du profil : " << std:: endl;
                        std::cout << "[1] Proprietaire " << std:: endl;
                        std::cout << "[2] Conjoint " << std:: endl;
                        std::cout << "Votre choix : ";

                        while (roleString.toInt() != 1 && roleString.toInt() != 2) {
                            roleString = stream.readLine().trimmed();
                        }
                        role = roleString.toInt() - 1;
                        if (role == 0) {
                            roleString = "Proprietaire";
                        } else if (role == 1) {
                            roleString = "Conjoint";
                        }
                    }

                    clearScreen();
                    if (user->createProfil(userId, firstname, lastname, login, password, role)){
                        std::cout << "----------------------" << std:: endl;
                        std::cout << "        RESUME        "<< std:: endl;
                        std::cout << "----------------------" << std:: endl;
                        std::cout << "Firstname : " << firstname.toStdString() << std:: endl;
                        std::cout << "Lastname : " << lastname.toStdString() << std:: endl;
                        std::cout << "Login : " << login.toStdString() << std:: endl;
                        std::cout << "Password : " << password.toStdString() << std:: endl;
                        std::cout << "Role : " << roleString.toStdString() << std:: endl;
                        std::cout << "----------------------" << std:: endl;
                        Sleep(5000);
                    } else {
                        std::cout << "Un erreur est survenue lors de la creation du profil.";
                        Sleep(2000);
                    }
                }
                // Si non : Creation de profil prop
            }
        } else if(profileExists == -1) {
            std::cout << "L'utilisateur a deja plusieurs profils";
            Sleep(2000);
        } else {
            std::cout << "Un erreur est survenue.";
            Sleep(2000);
        }
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

    void AffCreationCompte() override {}

    void AffVirement() override{}

    void AffAddBeneficiaire() override{}

    void AffRetrait() override {}

    void AffHistory(User& user) override {}

    void AffAjout() override {}
};


//--------------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char *argv[]) {
    User user;
    UI* interfaceUtilisateur = nullptr;
    QApplication app(argc, argv);

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
            user.checkPELIncome(user.getPpl_id(), user.getPel_id(), user.getUserId());
            user.updateLastConnexion(user.getUserId());
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


