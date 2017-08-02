
// Study_MFC_OpenCVDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "opencv_set_3.2.0.h"

using namespace cv;

// CStudy_MFC_OpenCVDlg ��ȭ ����
class CStudy_MFC_OpenCVDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CStudy_MFC_OpenCVDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY_MFC_OPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	VideoCapture *vid;
	Mat frame;
	CImage cImg;
};
