#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObjectCleanupHandler>
#include "DefineType.h"


class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    ~TCPServer();
    bool initTCPServer(QString ip,quint16 port);
    void BroadMSg(CLogMsg& msg);

signals:

public slots:
    void onNewConnection();
    void onSocketStateChange(QAbstractSocket::SocketState socketstate);
    void onClientConnected();
    void onClientDisconnected();
    void onSocketReadyRead();
private:
    QTcpServer* m_server;
    QTcpSocket* m_client;
    QList<QTcpSocket*> m_clientList;

};

#endif // TCPSERVER_H
