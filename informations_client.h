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
    void on_deco_infoc_clicked();

    void on_reduced_infoc_clicked();

    void on_fullscreen_infoc_clicked();

    void on_close_infoc_clicked();
private:
    Ui::informations_client *ui;
};

#endif // INFORMATIONS_CLIENT_H
