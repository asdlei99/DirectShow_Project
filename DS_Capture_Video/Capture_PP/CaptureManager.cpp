#include "stdafx.h"
#include "Utill.h"
#include "CaptureManager.h"


CCaptureManager::CCaptureManager()
{
	m_pVideoCapture = nullptr;
	m_pAudioCapture = nullptr;

}


CCaptureManager::~CCaptureManager()
{
}

//��ʼ���豸��Ϣ
BOOL CCaptureManager::InitDevice(HWND in_hwnd)
{
	m_pVideoCapture = new CVideoCapture();	

	if (m_pVideoCapture)
	{
		BOOL bre = m_pVideoCapture->InitVideoDevice(in_hwnd);

		if (!bre)
		{
			TRACE("CCaptureManager::InitDevice Failed.");
			DEF_SAFE_DELETE_OBJECT(m_pVideoCapture);
			return FALSE;
		}
	}

	m_pAudioCapture = new CAudioCapture();

	if (m_pAudioCapture)
	{
		
	}

	return  TRUE;
}
//���豸
BOOL CCaptureManager::OpenDevice(char *in_chVName, char *in_chAName)
{	
	if (!m_pVideoCapture)
		return FALSE;

	BOOL bre = m_pVideoCapture->OpenDevice(in_chVName);	
	if (!bre)
	{
		return FALSE;
	}

	return  TRUE;
}
//��ȡ�豸�б�
BOOL CCaptureManager::GetDeviceList(char *out_chVList[], char *out_chAList[])
{
	BOOL bre = FALSE;

	if (!m_pVideoCapture)
		return FALSE;

	bre = m_pVideoCapture->GetDeviceList(out_chVList);

	return  bre;
}
//��ʼ�ɼ�
BOOL CCaptureManager::StartCapture()
{
	BOOL bre = FALSE;
	
	if(m_pVideoCapture)
		bre = m_pVideoCapture->Start();

	return  bre;
}
//ֹͣ�ɼ�
BOOL CCaptureManager::StopCapture()
{
	BOOL bre = FALSE;

	return  bre;
}
//�ر��豸
BOOL CCaptureManager::CloseDevice()
{
	BOOL bre = FALSE;

	if (m_pVideoCapture)
		m_pVideoCapture->CloseDevice();

	return  bre;
}