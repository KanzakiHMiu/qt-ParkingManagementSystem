#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QWidget>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class NetworkManager : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkManager(QWidget *parent = nullptr);
    void loginAdmin(const QString&, const QString&);

signals:
    void loginFinished(QNetworkReply *);
    void requestTimeout();

private slots:
    void onLoginFinished(QNetworkReply *);

private:
    QNetworkAccessManager *networkManager;
};

#endif // NETWORKMANAGER_H
