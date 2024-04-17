#ifndef CREER_PROFIL_H
#define CREER_PROFIL_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class creer_profil;
}

class creer_profil : public QWidget
{
    Q_OBJECT

public:
    explicit creer_profil(QWidget *parent = nullptr);
    ~creer_profil();

private slots:
    void on_send_crprofil_clicked();

    void on_reduced_crprofil_clicked();

    void on_fullscreen_crprofil_clicked();

    void on_close_crprofil_clicked();

    void on_return_crprofil_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::creer_profil *ui;
};

#endif // CREER_PROFIL_H
