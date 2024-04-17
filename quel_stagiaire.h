#ifndef QUEL_STAGIAIRE_H
#define QUEL_STAGIAIRE_H
#include "home.h"
#include <QWidget>
#include "user.h"

namespace Ui {
class quel_stagiaire;
}

class quel_stagiaire : public QWidget
{
    Q_OBJECT

public:
    explicit quel_stagiaire(QWidget *parent = nullptr);
    ~quel_stagiaire();

private slots:
    void on_return_kist_clicked();

    void on_send_kist_clicked();

    void on_reduced_kist_clicked();

    void on_fullscreen_kist_clicked();

    void on_close_kist_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    Home *parentHome;
    Ui::quel_stagiaire *ui;
};

#endif // QUEL_STAGIAIRE_H
