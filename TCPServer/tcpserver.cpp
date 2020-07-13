#include "tcpserver.h"
#include <QDebug>


TCPServer::TCPServer(QObject *parent) : QObject(parent)
{

}

TCPServer::~TCPServer()
{

}

//初始化TCP服务器
bool TCPServer::initTCPServer(QString ip, quint16 port)
{
    m_server = new QTcpServer(this);
    connect(m_server,&QTcpServer::newConnection,this,&TCPServer::onNewConnection);
    QHostAddress addr(ip);
    if(!m_server->listen(addr,port))
    {
        return false;
    }
    qDebug() << "TCPServer start ...";
}



//新客户端连接
void TCPServer::onNewConnection()
{
    m_client = m_server->nextPendingConnection();//获取socket
    m_clientList.append(m_client);
    connect(m_client,&QTcpSocket::connected,this,&TCPServer::onClientConnected);
    onClientConnected();
    connect(m_client,&QTcpSocket::disconnected,this,&TCPServer::onClientDisconnected);
    connect(m_client,&QTcpSocket::stateChanged,this,&TCPServer::onSocketStateChange);
    onSocketStateChange(m_client->state());
    connect(m_client,&QTcpSocket::readyRead,this,&TCPServer::onSocketReadyRead);
    qDebug() << "newConnection " << "ip:" << m_client->peerAddress().toString()
             << "port:" << m_client->peerPort();
}

//连接状态变化
void TCPServer::onSocketStateChange(QAbstractSocket::SocketState socketstate)
{
    switch (socketstate)
    {
    case QAbstractSocket::UnconnectedState ://The socket is not connected.
        break;
    case QAbstractSocket::HostLookupState ://The socket is performing a host name lookup.
        break;
    case QAbstractSocket::ConnectingState ://The socket has started establishing a connection.
        break;
    case QAbstractSocket::ConnectedState ://A connection is established.
        break;
    case QAbstractSocket::BoundState ://The socket is bound to an address and port.
        break;
    case QAbstractSocket::ClosingState ://The socket is about to close (data may still be waiting to be written).
        break;
    case QAbstractSocket::ListeningState ://For internal use only.
        break;
    }
}

//客户端连接成功
void TCPServer::onClientConnected()
{

}

//客户端断开连接
void TCPServer::onClientDisconnected()
{
    QTcpSocket* m_client = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "client disconnect" << "ip:" << m_client->peerAddress().toString()
             << "port:" << m_client->peerPort();
    m_clientList.removeOne(m_client);
    m_client->deleteLater();

}

//接收客户端信息
void TCPServer::onSocketReadyRead()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    QByteArray arr = client->readAll();
}


