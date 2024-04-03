#ifndef INFORMATIONS_CLIENT_STAGIAIRE_H
#define INFORMATIONS_CLIENT_STAGIAIRE_H

#include <QWidget>

namespace Ui {
class informations_client_stagiaire;
}

class informations_client_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit informations_client_stagiaire(QWidget *parent = nullptr);
    ~informations_client_stagiaire();

private:
    Ui::informations_client_stagiaire *ui;
};

#endif // INFORMATIONS_CLIENT_STAGIAIRE_H
