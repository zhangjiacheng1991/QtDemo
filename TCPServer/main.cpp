#include <QCoreApplication>
#include "tcpserver.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TCPServer s;
    if(!s.initTCPServer(SERVER_IP,SERVER_PORT))
    {
        qWarning() << "tcpServer init Err";
        return 0;
    }
    return a.exec();
}
