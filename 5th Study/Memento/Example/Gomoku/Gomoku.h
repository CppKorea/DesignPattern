
// Gomoku.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGomokuApp:
// �� Ŭ������ ������ ���ؼ��� Gomoku.cpp�� �����Ͻʽÿ�.
//

class CGomokuApp : public CWinApp
{
public:
	CGomokuApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGomokuApp theApp;