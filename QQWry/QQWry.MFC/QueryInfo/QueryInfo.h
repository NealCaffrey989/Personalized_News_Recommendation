
// QueryInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQueryInfoApp:
// �йش����ʵ�֣������ QueryInfo.cpp
//

class CQueryInfoApp : public CWinApp
{
public:
	CQueryInfoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQueryInfoApp theApp;