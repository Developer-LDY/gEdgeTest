
// gEdgeTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CgEdgeTestApp:
// �� Ŭ������ ������ ���ؼ��� gEdgeTest.cpp�� �����Ͻʽÿ�.
//

class CgEdgeTestApp : public CWinApp
{
public:
	CgEdgeTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CgEdgeTestApp theApp;