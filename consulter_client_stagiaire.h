#ifndef CONSULTER_CLIENT_STAGIAIRE_H
#define CONSULTER_CLIENT_STAGIAIRE_H

#include <QWidget>

namespace Ui {
class consulter_client_stagiaire;
}

class consulter_client_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit consulter_client_stagiaire(QWidget *parent = nullptr);
    ~consulter_client_stagiaire();

private:
    Ui::consulter_client_stagiaire *ui;
};

#endif // CONSULTER_CLIENT_STAGIAIRE_H
