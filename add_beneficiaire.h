#ifndef ADD_BENEFICIAIRE_H
#define ADD_BENEFICIAIRE_H
#include "user.h"
#include "home.h"
#include <QWidget>

namespace Ui {
class add_beneficiaire;
}

class add_beneficiaire : public QWidget
{
    Q_OBJECT

public:
    explicit add_beneficiaire(User *user,Home *parentHome, QWidget *parent = nullptr);
    ~add_beneficiaire();

private slots:
    void on_return_addb_clicked();

    void on_fullscreen_addb_clicked();

    void on_close_addb_clicked();

    void on_send_addb_clicked();

    void on_reduced_addb_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::add_beneficiaire *ui;
};

#endif // ADD_BENEFICIAIRE_H
