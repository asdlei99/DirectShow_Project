
// Capture_PP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCapture_PPApp: 
// �йش����ʵ�֣������ Capture_PP.cpp
//

class CCapture_PPApp : public CWinApp
{
public:
	CCapture_PPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCapture_PPApp theApp;