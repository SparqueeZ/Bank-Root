#ifndef CREDIT_H
#define CREDIT_H

#include "user.h"
#include "home.h"
#include <QDialog>

namespace Ui {
class credit;
}

class credit : public QDialog
{
    Q_OBJECT

public:
    explicit credit(User *user, Home *parentHome, QWidget *parent = nullptr);
    ~credit();

private slots:
    void on_reduced_clicked();

    void on_fullscreen_clicked();

    void on_close_clicked();

    void on_send_clicked();

    void on_return2_clicked();

private:
    Ui::credit *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
};

#endif // CREDIT_H
