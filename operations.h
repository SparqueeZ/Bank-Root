#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QString>

class Operations {
public:
    // Nouveau système de classes
    static void mainchoice(int choice);
    static void adminChoice(int choice);
    static void virement(int accountPropId, int accountDestId, double amount);
    static void addBalance(double balance, int destinataireId);
    static void removeBalance(double balance, int destinataireId);

    static void transfert();
    static void ajout(QString amount, QString cible);
    static void retrait(QString amount);
    static void choices(QString choice);
    static void setvalue();
    static void defaultChoices(QString choice);
};

#endif // OPERATIONS_H
