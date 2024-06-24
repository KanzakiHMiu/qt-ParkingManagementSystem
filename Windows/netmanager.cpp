#include "netmanager.h"

netManager::netManager(QObject *parent)
    : QObject{parent}
    , networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &netManager::onFinished);
}

void netManager::postRequest(const QUrl &url, const QByteArray &data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager->post(request, data);
}

void netManager::onFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError ||
        reply->error() == QNetworkReply::AuthenticationRequiredError) {
        emit loginReply(reply);
    }
    else {
        emit networkError(reply->errorString());
    }
    reply->deleteLater();
}
