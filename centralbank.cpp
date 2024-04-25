#include "centralbank.h"
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QNetworkRequest>
#include <QDebug>

CentralBank::CentralBank(QObject *parent) : QObject(parent)
{
    // Initialisation du gestionnaire de réseau
    m_networkManager = new QNetworkAccessManager(this);
}

void CentralBank::sendPostRequest()
{
    // Création de l'URL de la requête
    QUrl url("https://formation.anjousoft.fr/programmationC/API_banque.php");

    // Création de l'objet JSON pour les données de la requête
    QJsonObject requestData;
    requestData["action"] = "IS_ALIVE";
    requestData["details"] = QJsonObject();

    // Création du document JSON à partir des données
    QJsonDocument jsonDoc(requestData);

    qDebug() << "postData: " << jsonDoc;

    // Création de la requête
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Ajout de l'en-tête d'autorisation basique
    QByteArray usernamePassword = "esaip:esaip";
    QByteArray encoded = usernamePassword.toBase64();
    QString authHeader = "Basic " + QString(encoded);
    request.setRawHeader("Authorization", authHeader.toUtf8());



    // Envoi de la requête POST avec les données JSON
    QNetworkReply *reply = m_networkManager->post(request, jsonDoc.toJson());

    // Vérification des erreurs
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Erreur lors de l'envoi de la requête :" << reply->errorString();
        // Ne pas oublier de gérer les erreurs plus précisément selon votre besoin
    } else {
        qDebug() << "Request sended.";
    }
}

void CentralBank::onReplyFinished(QNetworkReply *reply)
{
    qDebug() << "Traitement de la reponse";
    // Vérification de la validité de la réponse
    if (reply->error() == QNetworkReply::NoError) {
        // Lecture de la réponse JSON
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonResponse = jsonDoc.object();

        // Affichage de la réponse dans la console
        qDebug() << "Reponse de l'API :" << jsonResponse;
    } else {
        // Affichage de l'erreur dans la console
        qDebug() << "Erreur lors de la réception de la réponse :" << reply->errorString();
    }

    // Nettoyage de la mémoire
    reply->deleteLater();
}
