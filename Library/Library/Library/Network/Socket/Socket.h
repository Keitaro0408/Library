/**
 * @file   Socket.h
 * @brief  Socketクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SOCKET_H
#define SOCKET_H

#ifdef _MSC_VER
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#endif

/**
 * ソケットのラッパークラス
 */
class Socket
{
public:
	Socket();
	~Socket();

	SOCKET m_Socket;
};


#endif
