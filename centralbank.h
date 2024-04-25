#ifndef CENTRALBANK_H
#define CENTRALBANK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CentralBank : public QObject
{
    Q_OBJECT
public:
    explicit CentralBank(QObject *parent = nullptr);

    // Méthode pour effectuer la requête POST
    void sendPostRequest();

signals:
    void responseReceived(const QJsonObject &response);

public slots:
    // Slot pour traiter la réponse lorsque la requête est terminée
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
};

#endif // CENTRALBANK_H
