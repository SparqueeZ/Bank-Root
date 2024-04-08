#ifndef QUEL_CLIENT_H
#define QUEL_CLIENT_H

#include <QWidget>

namespace Ui {
class quel_client;
}

class quel_client : public QWidget
{
    Q_OBJECT

public:
    explicit quel_client(QWidget *parent = nullptr);
    ~quel_client();

private:
    Ui::quel_client *ui;
};

#endif // QUEL_CLIENT_H
