#ifndef F_ADMIN_H
#define F_ADMIN_H

#include <QString>

class f_admin
{
public:
    f_admin();
    int test();

    int createUser(QString username, int role);
    int createAccount(int userId, int type, double balance);
    bool createProfil(int userId, QString firstname, QString lastname, QString login, QString password, int type);
};

#endif // F_ADMIN_H
