#pragma once

#include"AudioCapture.h"
#include"VideoCapture.h"

class CCaptureManager
{
public:
	CCaptureManager();
	~CCaptureManager();

private:
	CAudioCapture	*m_pAudioCapture;
	CVideoCapture	*m_pVideoCapture;

public:
	/*
	˵�����豸��ʼ��
	������in_hwnd���ھ��
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL	InitDevice(HWND in_hwnd);
	
	/*
	˵�������豸.
	������in_chVName��Ƶ�豸����,in_chAName��Ƶ�豸����
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/	
	BOOL	OpenDevice(char *in_chVName,char *in_chAName);

	/*
	˵������ȡ�豸�б�
	������out_chVList��Ƶ�豸�б�out_chAList��Ƶ�豸�б�
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL	GetDeviceList(char *out_chVList[], char *out_chAList[]);

	/*
	˵������ʼ�ɼ�
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL	StartCapture();

	/*
	˵����ֹͣ�ɼ�
	����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE.
	*/
	BOOL	StopCapture();

	/*
	˵�����رմ򿪵��豸
	����ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE.
	*/
	BOOL	CloseDevice();
};

