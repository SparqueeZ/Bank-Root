#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QString>

class Operations {
public:
    static void transfert(QString username);
    static void ajout(QString amount, QString cible, QString username);
    static void retrait(QString amount, QString username);
    static void choices(QString username);
    static void setvalue(QString username);
};

#endif // OPERATIONS_H
