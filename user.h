 #ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>

class User {
public:
    User();
    User(const QString& login, const QString& lastName, const QString& firstName, const QDate& dateOfBirth, double balance, int isLoggedIn, int role, double PELBalance, double LCBalance, int firstAccountId, int PELAccountId, int LCAccountId, int userId);

    bool signin(QString login , QString password);

    bool logIn(QString login, QString password);
    void createAccount();
    QString generateAccountNumber() const;
    QString generateRandomPassword() const;
    bool isAdmin(const QString& username) const;

    // Nouvelle méthode pour récupérer les informations de l'utilisateur connecté
    User getLoggedInUser() const;
    int getIsLoggedIn() const;

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
    int getRole() const;
    void setCredentials(const QString& username, const QString& password);

    int getUserId() const;

    void refreshUserData();
    void addBeneficiaire(int beneficiaireId, int propId);
    void addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description);
    void getInformations(int userId);

private:
    int m_role;
    QString m_login;
    QString m_lastName;
    QString m_firstName;
    QDate m_dateOfBirth;
    double m_balance;
    double m_PELBalance;
    double m_LCBalance;
    QSqlDatabase m_database;
    QString m_password;
    int m_isLoggedIn;

    // Accounts
    int m_firstAccountId;
    int m_PELAccountId;
    int m_LCAccountId;

    int m_userId;
};

#endif // USER_H

