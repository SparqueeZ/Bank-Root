#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QString>

class Operations {
public:
    static void transfert(QString username, int role);
    static void ajout(QString amount, QString cible, QString username, int role);
    static void retrait(QString amount, QString username, int role);
    static void choices(QString username, int role);
    static void setvalue(QString username, int role);
    static void defaultChoices(QString username, int role);
};

#endif // OPERATIONS_H
