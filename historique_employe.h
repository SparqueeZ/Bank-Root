#ifndef HISTORIQUE_EMPLOYE_H
#define HISTORIQUE_EMPLOYE_H

#include <QWidget>

namespace Ui {
class historique_employe;
}

class historique_employe : public QWidget
{
    Q_OBJECT

public:
    explicit historique_employe(QWidget *parent = nullptr);
    ~historique_employe();

private slots:
    void on_toolButton_33_clicked();

    void on_toolButton_34_clicked();

    void on_toolButton_35_triggered(QAction *arg1);

    void on_toolButton_35_clicked();

    void on_reduced_3_clicked();

    void on_fullscreen_3_clicked();

    void on_reduced_3_triggered(QAction *arg1);

    void on_toolButton_31_clicked();

private:
    Ui::historique_employe *ui;
};

#endif // HISTORIQUE_EMPLOYE_H
