
// Study_MFC_OpenCV.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CStudy_MFC_OpenCVApp:
// �� Ŭ������ ������ ���ؼ��� Study_MFC_OpenCV.cpp�� �����Ͻʽÿ�.
//

class CStudy_MFC_OpenCVApp : public CWinApp
{
public:
	CStudy_MFC_OpenCVApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CStudy_MFC_OpenCVApp theApp;
