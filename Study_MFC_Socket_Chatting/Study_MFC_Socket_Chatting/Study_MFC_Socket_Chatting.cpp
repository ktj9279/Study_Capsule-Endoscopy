
// Study_MFC_Socket_Chatting.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CStudy_MFC_Socket_ChattingApp 생성

CStudy_MFC_Socket_ChattingApp::CStudy_MFC_Socket_ChattingApp()
	: m_pServer(NULL)
	, m_pClient(NULL)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CStudy_MFC_Socket_ChattingApp 개체입니다.

CStudy_MFC_Socket_ChattingApp theApp;


// CStudy_MFC_Socket_ChattingApp 초기화

BOOL CStudy_MFC_Socket_ChattingApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CStudy_MFC_Socket_ChattingDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


// 서버 초기화
void CStudy_MFC_Socket_ChattingApp::InitServer()
{
	m_pServer = new CServerSock;
	m_pServer->Create(7777);    // Create() : 통신할 소켓을 생성해주고 사용할 소켓에 IP 주소와 포트를 연결해주는 역할
	m_pServer->Listen();    // Listen() : 서버가 클라이언트의 접속 요청이 있을 때까지 대기하도록 만든다.
}


// 클라이언트 접속
// 클라이언트에서 서버로 보낸 접속 요청을 받아들이기 위해 서버가 두는 함수
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


// 서버 및 클라이언트의 종료
void CStudy_MFC_Socket_ChattingApp::CleanUp()
{
	if (m_pServer)
		delete m_pServer;

	if (m_pClient)
		delete m_pClient;
}


// 서버에 접속
// 클라이언트가 서버와 통신을 하려면 먼저 서버와 연결되어야 하는데 이를 위하여 클라이언트가 호출하는 함수
void CStudy_MFC_Socket_ChattingApp::Connect(CString strIP)
{
	m_pClient = new CClientSock;
	m_pClient->Create();
	m_pClient->Connect(strIP, 7777);
}


// 수신 데이터를 처리
// Send()로 전송한 데이터를 수신하는 함수
void CStudy_MFC_Socket_ChattingApp::ReceiveData()
{
	wchar_t temp[MAX_PATH];
	m_pClient->Receive(temp, sizeof(temp));
	((CStudy_MFC_Socket_ChattingDlg*)m_pMainWnd)->ReceiveData(temp);
}


// 데이터를 전송
void CStudy_MFC_Socket_ChattingApp::SendData(CString strData)
{
	m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
}


// 클라이언트 종료
void CStudy_MFC_Socket_ChattingApp::CloseChild()
{
	AfxMessageBox(_T("상대방 연결 끊김"));
	delete m_pClient;
	m_pClient = NULL;
}
