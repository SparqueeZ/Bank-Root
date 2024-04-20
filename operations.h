#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QString>
#include "home.h"
class Operations {
public:
    // Nouveau système de classes
    static bool virement(int accountPropId, int accountDestId, double amount);
    static bool addBalance(double balance, int destinataireId, QString description);
    static bool removeBalance(double balance, int destinataireId, QString description);

    static void transfert();
    static void choices(QString choice);
    static void setvalue();
    static void defaultChoices(QString choice);

    static bool addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description);
};

#endif // OPERATIONS_H
