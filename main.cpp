#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSettings>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <windows.h>
#include "operations.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString configFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("config.ini");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSettings settings(configFilePath, QSettings::IniFormat);
    db.setHostName(settings.value("Database/HostName").toString());
    db.setUserName(settings.value("Database/UserName").toString());
    db.setPassword(settings.value("Database/Password").toString());
    db.setDatabaseName(settings.value("Database/DatabaseName").toString());

    Operations operations;

    if (db.open()) {
        std::cout << "BDD Connecte" << std::endl;

        QTextStream stream(stdin);

        std::cout << "Entrez votre nom d'utilisateur : ";
        QString username = stream.readLine();
        std::cout << "Entrez votre mot de passe : ";
        QString password = stream.readLine();

        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE login = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {

            operations.choices(username);

        } else {
            std::cout << "Identifiants non corrects." << std::endl;
        }

    } else {
        std::cout << "Pas connecte" << db.lastError().text().toStdString() << std::endl;
    }

    return a.exec();
}
