#ifndef EMPLOYE_HOMEPAGE_H
#define EMPLOYE_HOMEPAGE_H

#include <QWidget>

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
    Ui::employe_homepage *ui;
};

#endif // EMPLOYE_HOMEPAGE_H
