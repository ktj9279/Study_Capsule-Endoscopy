
// Study_MFC_Socket_Chatting.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "ServerSock.h"
#include "ClientSock.h"


// CStudy_MFC_Socket_ChattingApp:
// �� Ŭ������ ������ ���ؼ��� Study_MFC_Socket_Chatting.cpp�� �����Ͻʽÿ�.
//

class CStudy_MFC_Socket_ChattingApp : public CWinApp
{
public:
	CStudy_MFC_Socket_ChattingApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	CServerSock* m_pServer;
	CClientSock* m_pClient;
	void InitServer();
	void Accept();
	void CleanUp();
	void Connect(CString strIP);
	void ReceiveData();
	void SendData(CString strData);
	void CloseChild();
};

extern CStudy_MFC_Socket_ChattingApp theApp;
