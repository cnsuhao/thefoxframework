#include <net/TcpServer.h>
#include <base/Types.h>

#ifdef WIN32
#include <net/Iocp.h>
#else
#include <net/EpollServer.h>
#endif

using namespace thefox;

TcpServer::TcpServer(const String &nameArg)
{
#ifdef WIN32
    _model = new Iocp(nameArg);
#else
    _model = new EpollServer(nameArg);
#endif
}

TcpServer::~TcpServer()
{
	delete _model;
}

bool TcpServer::start(const InetAddress &listenAddr)
{
    return _model->start(listenAddr);
}

bool TcpServer::started()
{
    return _model->started();
}

void TcpServer::send(const TcpConnectionPtr &conn, const char *data, size_t len)
{
	_model->send(conn, data, len);
}

void TcpServer::setConnectionCallback(const ConnectionCallback &cb)
{
    _model->setConnectionCallback(cb);
}
void TcpServer::setCloseCallback(const CloseCallback &cb)
{
    _model->setCloseCallback(cb);
}

void TcpServer::setMessageCallback(const MessageCallback &cb)
{
    _model->setMessageCallback(cb);
}

void TcpServer::setWriteCompleteCallback(const WriteCompleteCallback &cb)
{
	_model->setWriteCompleteCallback(cb);
}