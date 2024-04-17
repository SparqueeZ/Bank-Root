#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QString>
#include "home.h"
class Operations {
public:
    // Nouveau système de classes
    static void virement(int accountPropId, int accountDestId, double amount);
    static void addBalance(double balance, int destinataireId);
    static void removeBalance(double balance, int destinataireId);

    static void transfert();
    static void choices(QString choice);
    static void setvalue();
    static void defaultChoices(QString choice);

    static void addToHistory(int idCompteEmetteur, int idCompteRecepteur, int type, double montant, QString title, QString description);
};

#endif // OPERATIONS_H
