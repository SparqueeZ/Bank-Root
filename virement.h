#ifndef VIREMENT_H
#define VIREMENT_H

#include <QDialog>
#include "user.h"
#include "home.h"

namespace Ui {
class virement;
}

class virement : public QDialog
{
    Q_OBJECT

public:
    explicit virement(User *user, Home *parentHome, QWidget *parent = nullptr);
    ~virement();

private slots:
    void on_return_2_clicked();

    void on_send_clicked();

    void on_reduced_clicked();

    void on_close_clicked();


private:
    Ui::virement *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
};

#endif // VIREMENT_H
