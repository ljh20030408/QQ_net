
// OpenQQSer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "OpenQQSer.h"
#include "OpenQQSerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenQQSerApp

BEGIN_MESSAGE_MAP(COpenQQSerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COpenQQSerApp ����

COpenQQSerApp::COpenQQSerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

COpenQQSerApp::~COpenQQSerApp()
{
	WSACleanup();
}

// Ψһ��һ�� COpenQQSerApp ����

COpenQQSerApp theApp;


// COpenQQSerApp ��ʼ��

BOOL COpenQQSerApp::InitInstance()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        WSACleanup();
        return 1;
    }



	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	COpenQQSerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

