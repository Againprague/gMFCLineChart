
// gMFCLine.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CgMFCLineApp:
// �� Ŭ������ ������ ���ؼ��� gMFCLine.cpp�� �����Ͻʽÿ�.
//

class CgMFCLineApp : public CWinApp
{
public:
	CgMFCLineApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CgMFCLineApp theApp;