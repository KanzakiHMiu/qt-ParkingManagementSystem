#include "networkmanager.h"
#include <QMessageBox>

NetworkManager::NetworkManager(QWidget *parent)
    : QWidget{parent},
    networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &NetworkManager::onLoginFinished);
    connect(networkManager, &QNetworkAccessManager::authenticationRequired,
            this, [](QNetworkReply *reply, QAuthenticator *authenticator) {
        authenticator->setUser("ubuntu");
        authenticator->setPassword(";62n,#YTV7Bmv");
    });
}

void NetworkManager::loginAdmin(const QString& username, const QString& password) {
    QUrl url("http://43.136.79.145:8081/login/admin");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setTransferTimeout(10000);

    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    networkManager->post(request, data);
}

void NetworkManager::onLoginFinished(QNetworkReply *reply) {
    emit loginFinished(reply);
}
