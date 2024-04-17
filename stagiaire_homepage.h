#ifndef STAGIAIRE_HOMEPAGE_H
#define STAGIAIRE_HOMEPAGE_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class stagiaire_homepage;
}

class stagiaire_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit stagiaire_homepage(QWidget *parent = nullptr);
    ~stagiaire_homepage();

private slots:
    void on_consulter_st_clicked();

    void on_reduced_st_clicked();

    void on_fullscreen_st_clicked();

    void on_close_st_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::stagiaire_homepage *ui;
};

#endif // STAGIAIRE_HOMEPAGE_H
