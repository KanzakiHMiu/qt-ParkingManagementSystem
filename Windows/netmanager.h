#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class netManager : public QObject
{
    Q_OBJECT

public:
    explicit netManager(QObject *parent = nullptr);

    void postRequest(const QUrl&, const QByteArray&);

signals:
    void loginReply(QNetworkReply*);
    void networkError(const QString&);

private slots:
    void onFinished(QNetworkReply*);

private:
    QNetworkAccessManager *networkManager;
};

#endif // NETMANAGER_H
