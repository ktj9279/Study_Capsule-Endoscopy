
// Study_MFC_Socket_Chatting.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "Study_MFC_Socket_Chatting.h"
#include "Study_MFC_Socket_ChattingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudy_MFC_Socket_ChattingApp

BEGIN_MESSAGE_MAP(CStudy_MFC_Socket_ChattingApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CStudy_MFC_Socket_ChattingApp ����

CStudy_MFC_Socket_ChattingApp::CStudy_MFC_Socket_ChattingApp()
	: m_pServer(NULL)
	, m_pClient(NULL)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CStudy_MFC_Socket_ChattingApp ��ü�Դϴ�.

CStudy_MFC_Socket_ChattingApp theApp;


// CStudy_MFC_Socket_ChattingApp �ʱ�ȭ

BOOL CStudy_MFC_Socket_ChattingApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CStudy_MFC_Socket_ChattingDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}


// ���� �ʱ�ȭ
void CStudy_MFC_Socket_ChattingApp::InitServer()
{
	m_pServer = new CServerSock;
	m_pServer->Create(7777);    // Create() : ����� ������ �������ְ� ����� ���Ͽ� IP �ּҿ� ��Ʈ�� �������ִ� ����
	m_pServer->Listen();    // Listen() : ������ Ŭ���̾�Ʈ�� ���� ��û�� ���� ������ ����ϵ��� �����.
}


// Ŭ���̾�Ʈ ����
// Ŭ���̾�Ʈ���� ������ ���� ���� ��û�� �޾Ƶ��̱� ���� ������ �δ� �Լ�
void CStudy_MFC_Socket_ChattingApp::Accept()
{
	if (m_pClient == NULL) {
		m_pClient = new CClientSock;
		m_pServer->Accept(*m_pClient);
		CString strSock;
		UINT nPort;
		m_pClient->GetPeerName(strSock, nPort);
		((CStudy_MFC_Socket_ChattingDlg*)m_pMainWnd)->Accept(strSock);
	}
}


// ���� �� Ŭ���̾�Ʈ�� ����
void CStudy_MFC_Socket_ChattingApp::CleanUp()
{
	if (m_pServer)
		delete m_pServer;

	if (m_pClient)
		delete m_pClient;
}


// ������ ����
// Ŭ���̾�Ʈ�� ������ ����� �Ϸ��� ���� ������ ����Ǿ�� �ϴµ� �̸� ���Ͽ� Ŭ���̾�Ʈ�� ȣ���ϴ� �Լ�
void CStudy_MFC_Socket_ChattingApp::Connect(CString strIP)
{
	m_pClient = new CClientSock;
	m_pClient->Create();
	m_pClient->Connect(strIP, 7777);
}


// ���� �����͸� ó��
// Send()�� ������ �����͸� �����ϴ� �Լ�
void CStudy_MFC_Socket_ChattingApp::ReceiveData()
{
	wchar_t temp[MAX_PATH];
	m_pClient->Receive(temp, sizeof(temp));
	((CStudy_MFC_Socket_ChattingDlg*)m_pMainWnd)->ReceiveData(temp);
}


// �����͸� ����
void CStudy_MFC_Socket_ChattingApp::SendData(CString strData)
{
	m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
}


// Ŭ���̾�Ʈ ����
void CStudy_MFC_Socket_ChattingApp::CloseChild()
{
	AfxMessageBox(_T("���� ���� ����"));
	delete m_pClient;
	m_pClient = NULL;
}
