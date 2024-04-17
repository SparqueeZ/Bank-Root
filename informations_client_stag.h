#ifndef INFORMATIONS_CLIENT_STAG_H
#define INFORMATIONS_CLIENT_STAG_H
#include "user.h"
#include <QWidget>
#include "home.h"

namespace Ui {
class informations_client_stag;
}

class informations_client_stag : public QWidget
{
    Q_OBJECT

public:
    explicit informations_client_stag(QWidget *parent = nullptr);
    ~informations_client_stag();

private slots:
    void on_deco_infost_clicked();

    void on_reduced_infost_clicked();

    void on_fullscreen_infost_clicked();

    void on_close_infost_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::informations_client_stag *ui;
};

#endif // INFORMATIONS_CLIENT_STAG_H
