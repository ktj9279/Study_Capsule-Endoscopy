#include "stdafx.h"
#include "ClientSock.h"
#include "Study_MFC_Socket_Chatting.h"


CClientSock::CClientSock()
{
}


CClientSock::~CClientSock()
{
}


void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	((CStudy_MFC_Socket_ChattingApp*)AfxGetApp())->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSock::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	((CStudy_MFC_Socket_ChattingApp*)AfxGetApp())->CloseChild();

	CAsyncSocket::OnClose(nErrorCode);
}
