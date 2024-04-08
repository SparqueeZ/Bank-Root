#ifndef INFORMATIONS_CLIENT_H
#define INFORMATIONS_CLIENT_H

#include <QWidget>

namespace Ui {
class informations_client;
}

class informations_client : public QWidget
{
    Q_OBJECT

public:
    explicit informations_client(QWidget *parent = nullptr);
    ~informations_client();

private slots:
    void on_reduced_5_clicked();

    void on_toolButton_19_clicked();

private:
    Ui::informations_client *ui;
};

#endif // INFORMATIONS_CLIENT_H
