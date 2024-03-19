#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>

class User {
public:
    User();
    User(const QString& login, const QString& lastName, const QString& firstName, const QDate& dateOfBirth, double balance);

    bool logIn(const QString& username = "", const QString& password = "");
    void createAccount();
    QString generateAccountNumber() const;
    QString generateRandomPassword() const;
    bool isAdmin(const QString& username) const;

    // Nouvelle méthode pour récupérer les informations de l'utilisateur connecté
    User getLoggedInUser() const;
    // Nouvelle méthode pour récupérer le nom d'utilisateur
    QString getFirstName() const;
    QString getLastName() const;
    QString getLogin() const;
    double getBalance() const;
    int getRole() const;
    void setCredentials(const QString& username, const QString& password);
private:
    int m_role;
    QString m_login;
    QString m_lastName;
    QString m_firstName;
    QDate m_dateOfBirth;
    double m_balance;
    QSqlDatabase m_database;
    QString m_password;
};

#endif // USER_H
