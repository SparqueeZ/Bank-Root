#ifndef HISTORIQUE_EMPLOYE_H
#define HISTORIQUE_EMPLOYE_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class historique_employe;
}

class historique_employe : public QWidget
{
    Q_OBJECT

public:
    explicit historique_employe(QWidget *parent = nullptr);
    ~historique_employe();
    void setUserId(const QString &userId);
private slots:
    void on_lastconnect_em_clicked();

    void on_lastcons_em_clicked();

    void on_lastop_em_clicked();

    void on_reduced_em_clicked();

    void on_fullscreen_em_clicked();

    void on_close_em_clicked();

private:
    Ui::historique_employe *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
};

#endif // HISTORIQUE_EMPLOYE_H
