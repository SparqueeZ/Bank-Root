#ifndef CHOIX_PRINCIPAL_H
#define CHOIX_PRINCIPAL_H

#include <QWidget>

namespace Ui {
class choix_principal;
}

class choix_principal : public QWidget
{
    Q_OBJECT

public:
    explicit choix_principal(QWidget *parent = nullptr);
    ~choix_principal();

private:
    Ui::choix_principal *ui;
};

#endif // CHOIX_PRINCIPAL_H
