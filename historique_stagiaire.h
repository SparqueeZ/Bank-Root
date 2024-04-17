#ifndef HISTORIQUE_STAGIAIRE_H
#define HISTORIQUE_STAGIAIRE_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class historique_stagiaire;
}

class historique_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit historique_stagiaire(QWidget *parent = nullptr);
    ~historique_stagiaire();

private slots:
    void on_lastconnect_st_clicked();

    void on_lastcons_st_clicked();

    void on_reduced_st_clicked();

    void on_fullscreen_st_clicked();

    void on_close_st_clicked();

private:
    Ui::historique_stagiaire *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
};

#endif // HISTORIQUE_STAGIAIRE_H
