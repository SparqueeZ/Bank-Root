#ifndef HISTORIQUE_STAGIAIRE_H
#define HISTORIQUE_STAGIAIRE_H

#include <QWidget>

namespace Ui {
class historique_stagiaire;
}

class historique_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit historique_stagiaire(QWidget *parent = nullptr);
    ~historique_stagiaire();

private:
    Ui::historique_stagiaire *ui;

    void on_reduced_3_clicked();

    void on_toolButton_31_clicked();
};

#endif // HISTORIQUE_STAGIAIRE_H
