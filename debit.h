#ifndef DEBIT_H
#define DEBIT_H

#include "user.h"
#include "home.h"
#include <QDialog>

namespace Ui {
class debit;
}

class debit : public QDialog
{
    Q_OBJECT

public:
    explicit debit(User *user, Home *parentHome, QWidget *parent = nullptr);
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
};

#endif // DEBIT_H
