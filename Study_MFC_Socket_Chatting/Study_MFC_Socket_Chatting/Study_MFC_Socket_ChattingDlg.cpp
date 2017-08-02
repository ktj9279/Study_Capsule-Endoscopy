
// Study_MFC_Socket_ChattingDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Study_MFC_Socket_Chatting.h"
#include "Study_MFC_Socket_ChattingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudy_MFC_Socket_ChattingDlg ��ȭ ����



CStudy_MFC_Socket_ChattingDlg::CStudy_MFC_Socket_ChattingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDY_MFC_SOCKET_CHATTING_DIALOG, pParent)
	, m_nChatMode(0)
	, m_strMyIP(_T(""))
	, m_strOtherIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_radio = 0;
}

void CStudy_MFC_Socket_ChattingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAddress);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Radio(pDX, IDC_RADIO_SERVER, m_nChatMode);
}

BEGIN_MESSAGE_MAP(CStudy_MFC_Socket_ChattingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CStudy_MFC_Socket_ChattingDlg::OnClickedRadioServer)
	ON_COMMAND(IDC_RADIO_CLIENT, &CStudy_MFC_Socket_ChattingDlg::OnRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CStudy_MFC_Socket_ChattingDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CStudy_MFC_Socket_ChattingDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// CStudy_MFC_Socket_ChattingDlg �޽��� ó����

BOOL CStudy_MFC_Socket_ChattingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// IP �ּ� ��������
	char name[255];
	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {
		if ((hostinfo = gethostbyname(name)) != NULL) {
			m_strMyIP = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
		}
	}

	// ��Ʈ�� �ʱ�ȭ
	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Open"));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CStudy_MFC_Socket_ChattingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CStudy_MFC_Socket_ChattingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CStudy_MFC_Socket_ChattingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Message handlers
void CStudy_MFC_Socket_ChattingDlg::OnClickedRadioServer()
{
	// TODO: Add your control notification handler code here

	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Open"));
}


void CStudy_MFC_Socket_ChattingDlg::OnRadioClient()
{
	// TODO: Add your command handler code here

	m_IPAddress.SetWindowText(_T(""));
	m_IPAddress.EnableWindow(TRUE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
}


void CStudy_MFC_Socket_ChattingDlg::OnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	if (!m_nChatMode) {
		((CStudy_MFC_Socket_ChattingApp*)AfxGetApp())->InitServer();
		GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	}
	else {
		CString strIP;
		GetDlgItemText(IDC_IPADDRESS_SERVER, strIP);
		if (strIP != _T("0.0.0.0")) {
			GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
			((CStudy_MFC_Socket_ChattingApp*)AfxGetApp())->Connect(strIP);
			m_strOtherIP = strIP;
		}
		else {
			AfxMessageBox(_T("������ ������ IP�ּҸ� �Է��ϼ���"));
		}
	}
}


void CStudy_MFC_Socket_ChattingDlg::OnClickedButtonSend()
{
	// TODO: Add your control notification handler code here

	CString strSend, strInsert;
	GetDlgItemText(IDC_EDIT_SEND, strSend);
	strInsert.Format(_T("[%s]:%s"), m_strMyIP, strSend);
	theApp.SendData(strSend);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
	SetDlgItemText(IDC_EDIT_SEND, _T(""));
}


// ���ŵ� �����͸� list box�� ���
void CStudy_MFC_Socket_ChattingDlg::ReceiveData(CString strReceive)
{
	CString strInsert;
	strInsert.Format(_T("[%s]:%s"), m_strOtherIP, strReceive);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
}


void CStudy_MFC_Socket_ChattingDlg::Accept(CString strSock)
{
	m_strOtherIP = strSock;
}