#ifndef CREDIT_ADMIN_H
#define CREDIT_ADMIN_H

#include "home.h"
#include "informations_client.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class credit_admin;
}

class credit_admin : public QWidget
{
    Q_OBJECT

public:
    explicit credit_admin(User *user, informations_client *parentHome, QWidget *parent = nullptr);
    ~credit_admin();

private slots:
    void on_reduced_clicked();

    void on_fullscreen_clicked();

    void on_close_clicked();

    void on_send_clicked();

    void on_return2_clicked();

private:
    Ui::credit_admin *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    informations_client *parentHome;
};

#endif // CREDIT_ADMIN_H
