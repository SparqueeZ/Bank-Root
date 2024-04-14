#ifndef CREER_COMPTE_H
#define CREER_COMPTE_H

#include <QWidget>

namespace Ui {
class creer_compte;
}

class creer_compte : public QWidget
{
    Q_OBJECT

public:
    explicit creer_compte(QWidget *parent = nullptr);
    ~creer_compte();

private slots:
    void on_send_crcompte_clicked();

    void on_reduced_crcompte_clicked();

    void on_fullscreen_crcompte_clicked();

    void on_close_crcompte_clicked();

    void on_return_crcompte_clicked();

private:
    Ui::creer_compte *ui;
};

#endif // CREER_COMPTE_H
