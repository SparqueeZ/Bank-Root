#ifndef CHOIX_PRINCIPAL_H
#define CHOIX_PRINCIPAL_H

#include "user.h"
#include <QWidget>

namespace Ui {
class choix_principal;
}

class choix_principal : public QWidget
{
    Q_OBJECT

public slots:
    void setUserInformation(const User& user);

public:
    explicit choix_principal(QWidget *parent = nullptr);
    ~choix_principal();

private slots:
    void on_personnel_clicked();

    void on_admin_clicked();

    void on_reduced_2_clicked();

    void on_close_clicked();

private:
    Ui::choix_principal *ui;

    User currentUser;

};

#endif // CHOIX_PRINCIPAL_H
