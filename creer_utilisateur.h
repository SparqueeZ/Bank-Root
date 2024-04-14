#ifndef CREER_UTILISATEUR_H
#define CREER_UTILISATEUR_H

#include <QWidget>

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
    Ui::creer_utilisateur *ui;
};

#endif // CREER_UTILISATEUR_H
