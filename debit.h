#ifndef DEBIT_H
#define DEBIT_H

#include "user.h"
#include "home.h"
#include <QDialog>
#include "informations_client.h"

namespace Ui {
class debit;
}

class debit : public QDialog
{
    Q_OBJECT

public:
    explicit debit(User *user, Home *parentHome, QWidget *parent = nullptr);
    explicit debit(User *user, informations_client *parentInfoClient, QWidget *parent = nullptr);
    ~debit();

private slots:
    void on_reduced_clicked();

    void on_fullscreen_clicked();

    void on_close_clicked();

    void on_send_clicked();

    void on_return2_clicked();

private:
    Ui::debit *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    informations_client *parentInfoClient;
};

#endif // DEBIT_H
