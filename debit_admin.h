#ifndef DEBIT_ADMIN_H
#define DEBIT_ADMIN_H

#include <QWidget>
#include "informations_client.h"
#include "user.h"

namespace Ui {
class debit_admin;
}

class debit_admin : public QWidget
{
    Q_OBJECT

public:
    explicit debit_admin(User *user, informations_client *parentHome, QWidget *parent = nullptr);
    ~debit_admin();

private slots:
    void on_reduced_clicked();

    void on_fullscreen_clicked();

    void on_close_clicked();

    void on_send_clicked();

    void on_return2_clicked();

private:
    Ui::debit_admin *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    informations_client *parentHome;
};

#endif // DEBIT_ADMIN_H
