#ifndef ADMIN_HOMEPAGE_H
#define ADMIN_HOMEPAGE_H
#include "home.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class admin_homepage;
}

class admin_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_homepage(QWidget *parent = nullptr);
    ~admin_homepage();
    void setUserInformation(const User& user);

private slots:
    void on_logcl_adm_clicked();

    void on_associer_adm_clicked();

    void on_crprofil_adm_clicked();

    void on_logst_adm_clicked();

    void on_logem_adm_clicked();

    void on_cruser_adm_clicked();

    void on_close_adm_clicked();

    void on_fullscreen_adm_clicked();

    void on_reduced_adm_clicked();

    void on_logoff_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    Ui::admin_homepage *ui;
    User *currentUser;
};

#endif // ADMIN_HOMEPAGE_H
