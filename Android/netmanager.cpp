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

void netManager::putRequest(const QUrl &url, const QByteArray &data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager->put(request, data);
}

void netManager::getRequest(const QUrl& url)
{
    QNetworkRequest request(url);
    networkManager->get(request);
}

void netManager::onFinished(QNetworkReply *reply)
{
    QString replyUrl = reply->url().toString();
    if (replyUrl.contains("/user/login")){
        if (reply->error() == QNetworkReply::NoError ||
            reply->error() == QNetworkReply::AuthenticationRequiredError) {
            emit loginReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/user/register")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit registerReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/user/info")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit loadUserDataReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    }  else if (replyUrl.contains("/user/update")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit updateUserInfoReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/parking/spots")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit loadSpotsDataReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/user/bookspot")) {
        if (reply->error() == QNetworkReply::NetworkSessionFailedError) {
            emit networkError(reply->errorString());
        } else {
            emit bookSpotReply(reply);
        }
    } else if (replyUrl.contains("/user/billing_history")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit loadBillingHistoryReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/user/wallet")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit loadWalletReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    } else if (replyUrl.contains("/user/recharge")) {
        if (reply->error() == QNetworkReply::NoError) {
            emit rechargeReply(reply);
        } else {
            emit networkError(reply->errorString());
        }
    }
    reply->deleteLater();
}
