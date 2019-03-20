
// Capture_PPDlg.h : ͷ�ļ�
//

#pragma once

#include "CaptureManager.h"
#include "afxwin.h"

// CCapture_PPDlg �Ի���
class CCapture_PPDlg : public CDialogEx
{
// ����
public:
	CCapture_PPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAPTURE_PP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CCaptureManager	m_objCaptureManager;

	char **m_pVideoListBuf;
	char **m_pAudioListBuf;

private:
	WCHAR * CHARCONVWCHAR(char *in_chbuf);
	void DestoryData();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CComboBox m_ComboxVideo;
	CComboBox m_ComboxAudio;
	afx_msg void OnClose();
};
