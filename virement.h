#ifndef VIREMENT_H
#define VIREMENT_H

#include <QDialog>
#include "user.h"

namespace Ui {
class virement;
}

class virement : public QDialog
{
    Q_OBJECT

public:
    explicit virement(User *user, QWidget *parent = nullptr);
    ~virement();

private slots:
    void on_toolButton_3_clicked();

    void on_Envoyer_clicked();

private:
    Ui::virement *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
};

#endif // VIREMENT_H
