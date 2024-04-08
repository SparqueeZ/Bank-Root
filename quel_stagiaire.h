#ifndef QUEL_STAGIAIRE_H
#define QUEL_STAGIAIRE_H

#include <QWidget>

namespace Ui {
class quel_stagiaire;
}

class quel_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit quel_stagiaire(QWidget *parent = nullptr);
    ~quel_stagiaire();

private:
    Ui::quel_stagiaire *ui;
};

#endif // QUEL_STAGIAIRE_H
