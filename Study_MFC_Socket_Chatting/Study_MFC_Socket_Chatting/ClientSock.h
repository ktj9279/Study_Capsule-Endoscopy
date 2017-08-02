#pragma once
#include "afxsock.h"
class CClientSock :
	public CAsyncSocket
{
public:
	CClientSock();
	~CClientSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

