#ifndef CREER_UTILISATEUR_H
#define CREER_UTILISATEUR_H

#include <QWidget>

namespace Ui {
class creer_utilisateur;
}

class creer_utilisateur : public QWidget
{
    Q_OBJECT

public:
    explicit creer_utilisateur(QWidget *parent = nullptr);
    ~creer_utilisateur();

private:
    Ui::creer_utilisateur *ui;
};

#endif // CREER_UTILISATEUR_H
