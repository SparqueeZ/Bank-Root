 #ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>

class User {
public:
    User();
    User(
        int isLoggedIn,
        // User
        int userId,
        QString username,
        int role,
        QDate creationDate,
        // Profils
        int actual_profilId,
        int actual_type,
        QString actual_firstname,
        QString actual_lastname,
        QString actual_login,
        QString actual_password,
        QDate actual_dateOfBirth,
            // Proprietaire
        int owner_profilId,
        int owner_type,
        QString owner_firstname,
        QString owner_lastname,
        QString owner_login,
        QString owner_password,
        QDate owner_dateOfBirth,
            // Conjoint
        int coowner_profilId,
        int coowner_type,
        QString coowner_firstname,
        QString coowner_lastname,
        QString coowner_login,
        QString coowner_password,
        QDate coowner_dateOfBirth,
        // Accounts
            // Principal
        double ppl_balance,
        int ppl_id,
        double pel_balance,
        int pel_id,
        double lvc_balance,
        int lvc_id);

    //int getprofil(QString login, QString password);
    bool signin(QString login , QString password);

    bool logIn(QString login, QString password);
    //void createAccount(); <- Ancien sys de creation de compte
    QString generateAccountNumber() const;
    QString generateRandomPassword() const;
    bool isAdmin(const QString& username) const;

    // Nouvelle méthode pour récupérer les informations de l'utilisateur connecté
    User getLoggedInUser() const;

    int getFirstAccountId() const;
    int getPELAccountId() const;
    int getLCAccountId() const;

    double getPELBalance() const;
    double getLCBalance() const;
    double getBalance() const;

    void disconnect(); // Nouvelle méthode pour déconnecter l'utilisateur
    // Nouvelle méthode pour récupérer le nom d'utilisateur
    QString getFirstName() const;
    QString getLastName() const;
    QString getLogin() const;

    void setCredentials(const QString& username, const QString& password);

    int getProfilType() const;

    void refreshUserData();
    void addBeneficiaire(int beneficiaireId, int propId);
    void addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description);

    // Création de comptes User
    int createUser(QString username, int role);

    // Création de commptes Profils
    bool createProfil(int userId, QString firstname, QString lastname, QString login, QString password, int type);

    // Création de comptes Bancaires
    bool createAccount(int userId, int type, double balance);

    void getInformations(int userId);

    int checkIfProfileExists(int userId);
    bool checkIfUserIsAdmin(int userId);

    // Getters
    int getIsLoggedIn() const;
    // User
    int getUserId() const;
    QString getUsername() const;
    int getRole() const;
    QDate getCreationDate() const;
    // Profils
        int getActual_profilId() const;
        int getActual_type() const;
        QString getActual_firstname() const;
        QString getActual_lastname() const;
        QString getActual_login() const;
        QDate getActual_dateOfBirth() const;
        // Proprietaire
        int getOwner_profilId() const;
        int getOwner_type() const;
        QString getOwner_firstname() const;
        QString getOwner_lastname() const;
        QString getOwner_login() const;
        QDate getOwner_dateOfBirth() const;
        // Conjoint
        int getCoowner_profilId() const;
        int getCoowner_type() const;
        QString getCoowner_firstname() const;
        QString getCoowner_lastname() const;
        QString getCoowner_login() const;
        QDate getCoowner_dateOfBirth() const;
    // Accounts
        // Principal
        double getPpl_balance() const;
        int getPpl_id() const;
        // PEL
        double getPel_balance() const;
        int getPel_id() const;
        // LVC
        double getLvc_balance() const;
        int getLvc_id() const;

private:
    int isLoggedIn;
    // User
    int m_userId;
    QString m_username;
    int m_role;
    QDate m_creationDate;
    // Profils
        int m_actual_profilId;
        int m_actual_type;
        QString m_actual_firstname;
        QString m_actual_lastname;
        QString m_actual_login;
        QString m_actual_password;
        QDate m_actual_dateOfBirth;
        // Proprietaire
        int m_owner_profilId;
        int m_owner_type;
        QString m_owner_firstname;
        QString m_owner_lastname;
        QString m_owner_login;
        QString m_owner_password;
        QDate m_owner_dateOfBirth;
        // Conjoint
        int m_coowner_profilId;
        int m_coowner_type;
        QString m_coowner_firstname;
        QString m_coowner_lastname;
        QString m_coowner_login;
        QString m_coowner_password;
        QDate m_coowner_dateOfBirth;
    // Accounts
        // Principal
        double m_ppl_balance;
        int m_ppl_id;
        // PEL
        double m_pel_balance;
        int m_pel_id;
        // LVC
        double m_lvc_balance;
        int m_lvc_id;
};

#endif // USER_H

