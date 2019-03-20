
// Capture_PPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Capture_PP.h"
#include "Capture_PPDlg.h"
#include "afxdialogex.h"
#include "Utill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCapture_PPDlg �Ի���



CCapture_PPDlg::CCapture_PPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAPTURE_PP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCapture_PPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboxVideo);
	DDX_Control(pDX, IDC_COMBO2, m_ComboxAudio);
}

BEGIN_MESSAGE_MAP(CCapture_PPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCapture_PPDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCapture_PPDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCapture_PPDlg ��Ϣ�������

BOOL CCapture_PPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pVideoListBuf = new char *[DEF_BUF_MAX];
	for (int i = 0; i < DEF_BUF_MAX; i++)
	{
		m_pVideoListBuf[i] = new char[DEF_BUF_MAX];
		memset(m_pVideoListBuf[i], 0, DEF_BUF_MAX);
	}
	
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CCapture_PPDlg::DestoryData()
{
	for (int i = 0; i < DEF_BUF_MAX; i++)
	{
		DEF_SAFE_DELETE_BUF(m_pVideoListBuf[i]);
	}
	DEF_SAFE_DELETE_BUF(m_pVideoListBuf);
	TRACE("CCapture_PPDlg::DestoryData().");
}
void CCapture_PPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCapture_PPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCapture_PPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

WCHAR * CCapture_PPDlg::CHARCONVWCHAR(char *in_chbuf)
{
	int iLen = MultiByteToWideChar(0, 0, in_chbuf, -1, NULL, 0);

	TCHAR *tchBuf = new TCHAR[iLen +1];

	MultiByteToWideChar(0, 0, in_chbuf, -1, tchBuf, iLen + 1);

	return tchBuf;
}
//��ȡ�豸�б�
void CCapture_PPDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bre = m_objCaptureManager.InitDevice(GetDlgItem(IDC_STATIC)->m_hWnd);
	if (!bre)
	{
		TRACE("m_objCaptureManager.InitDevice Failed.");
		return;
	}

	bre = m_objCaptureManager.GetDeviceList(m_pVideoListBuf, NULL);
	if (!bre)
	{
		TRACE("m_objCaptureManager.GetDeviceList Failed.");
		return;
	}
	for (int i = 0; i < DEF_BUF_MAX; i++)
	{
		if (*m_pVideoListBuf[i] == '\0')
			break;

		TCHAR *pB = CHARCONVWCHAR(m_pVideoListBuf[i]);

		m_ComboxVideo.InsertString(i,pB);

		DEF_SAFE_DELETE_BUF(pB);
	}
	m_ComboxVideo.SetCurSel(0);
}

//��Ԥ��
void CCapture_PPDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i = m_ComboxVideo.GetCurSel();

	BOOL bre = m_objCaptureManager.OpenDevice(m_pVideoListBuf[i], nullptr);
	if (!bre)
	{
		TRACE("m_objCaptureManager.OpenDevice Failed.");
	}
	
	bre = m_objCaptureManager.StartCapture();
	if (!bre)
	{
		TRACE("m_objCaptureManager.StartCapture Failed.");
	}
}


void CCapture_PPDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_objCaptureManager.CloseDevice();

	DestoryData();

	CDialogEx::OnClose();
}
