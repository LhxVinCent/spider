#ifndef _SOCKET_H_
#define _SOCKET_H_
#include<socket.h>
#include "url.h"
class Socket
{
	public://公共接口
		Socket();
		~Socket();
		int request(URL* url);//发送请求
		int response();//接受反馈
		int setSocket();//设置socket
		int connect();//链接操作
		int disconnect();//断开连接操作
		void* getData();
     private:

	 private:
		int m_socketHandle;//socket句柄
		char* buf;
};
#endif
