#include <QCoreApplication>

#include<QSqlDatabase>
#include <QSettings>
#include <iostream>
#include <ostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSettings settings("config.ini", QSettings::IniFormat);
    db.setHostName(settings.value("Database/HostName").toString());
    db.setUserName(settings.value("Database/UserName").toString());
    db.setPassword(settings.value("Database/Password").toString());
    db.setDatabaseName(settings.value("Database/DatabaseName").toString());


    if(db.open()) {
        std::cout << "Db Connecte" << std::endl;
    } else {
        std::cout << "Db Pas connecte" << std::endl;
    }
    return a.exec();
}
