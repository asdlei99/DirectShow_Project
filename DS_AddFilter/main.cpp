/*
ʹ��DirecShowʵ����Ƶ�ɼ����浽�����ļ���
���̣�
1:����ָ�����豸Filter,����VideoInput .CLSID_VideoInputDeviceCategory
2:����һ��Filter Graph�����ڹ���Filter.CLSID_FilterGraph
3:����CLSID_CaptureGraphBuilder2.��Graph�����ڱ༭����Ƶ�ɼ�.
4:SetFiltergraph
5:AddFilter���Filter��Graph��.
6:��ȡ���ƶ���pMediaControl
7:������Ҫ���浽�����ļ���������Ҫ����һ��Filter���ڽ������ݱ���SetOutputFileName�����Ϊ��֧��Ԥ������Ҫ��������IVideoWindow
8:Filter ����.RenderStream.
9:��ʼ¼��Run
*/

#include<stdio.h>
#include<dshow.h>
#pragma comment(lib,"Strmiids.lib")

IBaseFilter *CreateFilter(WCHAR *pDevice)
{
	ICreateDevEnum *pCreateDevEnum = NULL;
	
	HRESULT hr = S_OK;
	
	IBaseFilter *pFilter = NULL;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pCreateDevEnum);
	if (FAILED(hr))
	{
		printf("CreateFilter::CLSID_SystemDeviceEnum Failed\n");
	}
	IEnumMoniker *pEnumMoniker = NULL;

	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumMoniker, 0);
	if (FAILED(hr))
	{
		printf("CreateFilter::CreateClassEnumerator Filed\n");
	}

	IMoniker *pMoniker = NULL;
	ULONG ulfetched = 0;
	
	while (pEnumMoniker->Next(1, &pMoniker, &ulfetched) == S_OK)
	{
		IPropertyBag *pPropertyBag = NULL;

		hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void **)&pPropertyBag);
		if (SUCCEEDED(hr))
		{
			VARIANT var;
			VariantInit(&var);

			pPropertyBag->Read(L"friendlyName", &var, NULL);
			if (wcscmp(var.bstrVal, pDevice) == 0)
			{
				printf("wcsmp success.\n");
				
				pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void **)&pFilter);
				
			}
		}
		
		pPropertyBag->Release();
		pMoniker->Release();
	}
	pEnumMoniker->Release();
	pCreateDevEnum->Release();

	return pFilter;
}
int main(int argc, char *argv[])
{
	HRESULT hr = S_OK;

	hr = CoInitialize(NULL);
	if (!SUCCEEDED(hr))
	{
		printf("CoInitialize Failed\n");
	}

	WCHAR *pDevice = L"HD Pro Webcam C920";

	IBaseFilter *pVideoFilter = CreateFilter(pDevice);
	if (pVideoFilter == NULL)
	{
		printf("CreateFilter Failed\n");
	}

	IGraphBuilder *pGrapBuilder = NULL;

	hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGrapBuilder);
	if (FAILED(hr))
	{
		printf("IID_IGraphBuilder ConCreateInstance Failed\n");
	}

	ICaptureGraphBuilder2 *pCaptureGrapBuilder = NULL;
	
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 0, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void **)&pCaptureGrapBuilder);
	if (FAILED(hr))
	{
		printf("ICaptureGraphBuilder2 Filed\n");
	}

	hr = pCaptureGrapBuilder->SetFiltergraph(pGrapBuilder);
	if (FAILED(hr))
	{
		printf("SetFiltergraph Failed\n");
	}

	IMediaControl *pMediaControl = NULL;
	IMediaEvent *pMediaEvent = NULL;
	
	hr = pGrapBuilder->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
	if (FAILED(hr))
	{
		printf("pMediaControl Failed\n");
	}
	hr = pGrapBuilder->QueryInterface(IID_IMediaEvent,(void **)&pMediaEvent);
	if (FAILED(hr))
	{
		printf("pMediaEvent Failed\n");
	}
	
	hr = pGrapBuilder->AddFilter(pVideoFilter, L"Capture Filter");
	
	IBaseFilter *pFilterSave = NULL;

	hr = pCaptureGrapBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi, L"C:\\quanwei\\WMV\\S.avi", &pFilterSave, NULL);

	hr = pCaptureGrapBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, pVideoFilter, NULL, pFilterSave);
	if (FAILED(hr))
	{
		printf("RenderStream Failed\n");
	}
	
	hr = pMediaControl->Run();

	Sleep(2000);
	
	pMediaControl->Stop();

	pFilterSave->Release();
	pMediaControl->Release();
	pMediaEvent->Release();
	pCaptureGrapBuilder->Release();
	pGrapBuilder->Release();

	CoUninitialize();
	
	for (;;);

	return 0;
}
