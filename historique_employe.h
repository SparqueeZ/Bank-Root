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

private:
    Ui::historique_employe *ui;

    void on_reduced_3_clicked();

    void on_toolButton_31_clicked();
};

#endif // HISTORIQUE_EMPLOYE_H
