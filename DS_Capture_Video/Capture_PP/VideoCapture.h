#pragma once

#include<vector>
#include"SampleCallBack.h"

class CVideoCapture
{
public:
	CVideoCapture();
	~CVideoCapture();
	
private:
	ICreateDevEnum	*m_pDevEnum;
	IEnumMoniker	*m_pEnumMoniker;

	IBaseFilter		*m_pCaptureFilter;
	IBaseFilter		*m_pNullRenderFilter;
	IBaseFilter		*m_pGrabberFilter;
	IBaseFilter		*m_pSmartTeeFilter;

	ISampleGrabber	*m_pSampleGrabber;
	IGraphBuilder	*m_pGraphBuilder;
	ICaptureGraphBuilder2	*m_pCaptureGraph;
	IMediaControl	*m_pMediaControl;
	IVideoWindow	*m_pVideoWindow;

	IAMStreamConfig *m_pConfig;
	CSampleCallBack *m_pSampleCallBack;

	std::vector<char *>m_vecDevList;

	int	m_iHeigh;
	int m_iWidth;
	int m_iBitRate;
	int m_iFPS;
private:
	char *WCharConvChar(WCHAR *in_wchStr);
	
	IBaseFilter	*GetSpecifiedCaptureFilter(char *in_chFilterName);
	
	IPin *FindPin(IBaseFilter *in_pFilter, PIN_DIRECTION in_dir);

	BOOL ConnectPins();

	HRESULT SetWindowDisplay();

	HRESULT GetVideoParams();

	HWND m_hwnd;

	void _FreeMediaType(AM_MEDIA_TYPE& mt);

	void _DeleteMediaType(AM_MEDIA_TYPE *pmt);
public:

	/*
	˵������ʼ����Ƶ�豸
	������in_hwnd���ڴ�����ʾ�ľ��
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/	
	BOOL InitVideoDevice(HWND in_hwnd);

	/*
	˵������ȡ��Ƶ�豸�б�
	������out_chDevList�豸�б���Ϣ
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL GetDeviceList(char *out_chDevList[]);

	/*
	˵�������豸
	������in_chDevName�豸����
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL OpenDevice(char *in_chDevName);

	/*
	˵������ʼ�ɼ�
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL Start();

	/*
	˵�����ر��豸
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL CloseDevice();
};

