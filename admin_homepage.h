#ifndef ADMIN_HOMEPAGE_H
#define ADMIN_HOMEPAGE_H

#include "user.h"
#include <QWidget>

namespace Ui {
class admin_homepage;
}

class admin_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_homepage(QWidget *parent = nullptr);
    ~admin_homepage();
    void setUserInformation(const User& user);

private slots:
    void on_toolButton_22_clicked();

    void on_toolButton_30_clicked();

    void on_toolButton_26_clicked();

    void on_toolButton_33_clicked();

    void on_toolButton_34_clicked();

    void on_toolButton_36_clicked();

    void on_close_clicked();

    void on_fullscreen_2_clicked();

    void on_reduced_clicked();

    void on_toolButton_31_clicked();

    void on_reduced_3_clicked();

private:
    Ui::admin_homepage *ui;
    User *currentUser;
};

#endif // ADMIN_HOMEPAGE_H
