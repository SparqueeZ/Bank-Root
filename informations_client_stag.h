#ifndef INFORMATIONS_CLIENT_STAG_H
#define INFORMATIONS_CLIENT_STAG_H

#include <QWidget>

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
    void on_reduced_clicked();

    void on_toolButton_3_clicked();

private:
    Ui::informations_client_stag *ui;
};

#endif // INFORMATIONS_CLIENT_STAG_H
