#include "stdafx.h"
#include "ServerSock.h"
#include "Study_MFC_Socket_Chatting.h"


CServerSock::CServerSock()
{
}


CServerSock::~CServerSock()
{
}


void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	((CStudy_MFC_Socket_ChattingApp*)AfxGetApp())->Accept();

	CAsyncSocket::OnAccept(nErrorCode);
}
