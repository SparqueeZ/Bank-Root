#ifndef EMPLOYE_HOMEPAGE_H
#define EMPLOYE_HOMEPAGE_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class employe_homepage;
}

class employe_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit employe_homepage(QWidget *parent = nullptr);
    ~employe_homepage();

private slots:
    void on_reduced_em_clicked();

    void on_close_em_clicked();

    void on_fullscreen_em_clicked();

    void on_crprofil_em_clicked();

    void on_cruser_em_clicked();

    void on_associer_em_clicked();

    void on_logcl_em_clicked();

    void on_crcompte_em_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::employe_homepage *ui;
};

#endif // EMPLOYE_HOMEPAGE_H
