#ifndef CREER_UTILISATEUR_H
#define CREER_UTILISATEUR_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class creer_utilisateur;
}

class creer_utilisateur : public QWidget
{
    Q_OBJECT

public:
    explicit creer_utilisateur(QWidget *parent = nullptr);
    ~creer_utilisateur();

private slots:
    void on_send_cruser_clicked();

    void on_reduced_cruser_clicked();

    void on_fullscreen_cruser_clicked();

    void on_close_cruser_clicked();

    void on_return_cruser_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::creer_utilisateur *ui;
};

#endif // CREER_UTILISATEUR_H
