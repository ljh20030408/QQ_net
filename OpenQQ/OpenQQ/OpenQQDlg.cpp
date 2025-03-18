
// OpenQQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenQQ.h"
#include "OpenQQDlg.h"
#include "afxdialogex.h"

#include "RegDlg.h"

#include "CgHeadDlg.h"

#include "ChatDlg.h"

#include "UserInfo.h"

#include "FriDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenQQDlg �Ի���




COpenQQDlg::COpenQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenQQDlg::IDD, pParent)
	, m_profileAppnameCnt(0)
{
	m_largeRect.bottom=0;
	m_largeRect.left = 0;
	m_largeRect.top = 0;
	m_largeRect.right = 0;

	m_smallRect.bottom=0;;
	m_smallRect.left = 0;
	m_smallRect.top = 0;
	m_smallRect.right = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
COpenQQDlg::~COpenQQDlg()
{
}

void COpenQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNLOGIN, &COpenQQDlg::OnBnClickedBtnlogin)
	ON_BN_CLICKED(IDC_BTN_SET, &COpenQQDlg::OnBnClickedBtnSet)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BTN_CLOSE, &COpenQQDlg::OnBnClickedBtnClose)
ON_BN_CLICKED(IDC_BTN_MIN, &COpenQQDlg::OnBnClickedBtnMin)
ON_NOTIFY(NM_CLICK, IDC_REG, &COpenQQDlg::OnNMClickReg)
ON_NOTIFY(NM_CLICK, IDC_RETURN, &COpenQQDlg::OnNMClickReturn)
ON_BN_CLICKED(IDC_AUTOLOGIN, &COpenQQDlg::OnBnClickedAutologin)
ON_BN_CLICKED(IDC_REMPASSWD, &COpenQQDlg::OnBnClickedRempasswd)
ON_CBN_SELCHANGE(IDC_USERNAME, &COpenQQDlg::OnCbnSelchangeUsername)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_ABOUT, &COpenQQDlg::OnBnClickedBtnAbout)
//ON_BN_CLICKED(IDC_BTNHEAD, &COpenQQDlg::OnBnClickedBtnhead)
END_MESSAGE_MAP()


// COpenQQDlg ��Ϣ�������

BOOL COpenQQDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitWindowSize();
	//����ť���ͷ��ͼƬ
	
	HBITMAP   hBitmap; 
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDB_BTHEAD)); // IDB_BITMAP_TESTΪ��ԴͼƬID

	((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap); 

	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTCLOSEBTN));
	((CButton *)GetDlgItem(IDC_BTN_CLOSE))->SetBitmap(hBitmap);

	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTMINBTN));
	((CButton *)GetDlgItem(IDC_BTN_MIN))->SetBitmap(hBitmap);

	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTABOUT));
	((CButton *)GetDlgItem(IDC_BTN_ABOUT))->SetBitmap(hBitmap);

	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS))->SetAddress(127, 0, 0, 1);
	SetDlgItemInt(IDC_PORT, 6600);

	LoadProfiles();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COpenQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COpenQQDlg::OnPaint()
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
		//CDialogEx::OnPaint();

		CPaintDC dc(this);
        CRect rc;
        GetClientRect(&rc);
        CDC dcMem;
        dcMem.CreateCompatibleDC(&dc);
        CBitmap bmpBackground;
        bmpBackground.LoadBitmap(IDB_BTBK);

        BITMAP bitmap;
        bmpBackground.GetBitmap(&bitmap);
        CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
        dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COpenQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenQQDlg::OnClickedReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRegDlg regDlg;
	regDlg.DoModal();
}

void COpenQQDlg::OnBnClickedBtnlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��½
	if (FALSE == InitSocket())
	{
		return ;
	}

	//����һ���û��ṹ
	UserInfo user;
	user.bOnLine = FALSE;
	user.accFlag = FALSE;
	user.isRegister = FALSE;
	//��ȡ�û���Ϣ
	GetDlgItemText(IDC_USERNAME, user.userName, 20);
	GetDlgItemText(IDC_PASSWD, user.passWord, 20);

	//�ж��û��������벻��Ϊ��
	if (_tcscmp(user.userName, _T("")) 
		&&	_tcscmp(user.passWord, _T("")))
	{
		send(m_sockCli, (char *)&user, sizeof(user), 0);
		
		char chVerify[20];
		recv(m_sockCli, chVerify, 20, 0);

		if (!strcmp(chVerify, "failure"))
		{
			MessageBox(_T("��½ʧ�ܣ���������û���������!"), _T("��ʾ"), MB_ICONWARNING);
			return ;
		}
		else if (!strcmp(chVerify, "repeat login"))
		{
			MessageBox(_T("���˺��Ѿ���½�������ظ���½!"), _T("��ʾ"), MB_ICONWARNING);
			return ;
		}

		//��½�ɹ����Ͱ�ͷ�񷵻���
		//һ������
		/*UINT headNum;
		recv(m_sockCli, (char *)&headNum, sizeof(headNum), 0);
		HICON hIcon;
		hIcon = GetHICONByHeadNum(headNum);*/
		ShowWindow(SW_HIDE);

		CFriDlg friDlg;
		//((CButton *)friDlg.GetDlgItem(IDC_BTN_HEAD))->SetIcon(hIcon);
		//����һ����Ϣ���������ͼ��ľ��
		//WM_TRANSICON WM_USER+10
		//SendMessage(WM_TRANSICON, (WPARAM)&hIcon);
		friDlg.DoModal();
		closesocket(m_sockCli);
		//WSACleanup();

		ShowWindow(SW_SHOW);
		//::DestroyWindow(AfxGetMainWnd()->m_hWnd);
		
	}
	else
	{
		MessageBox(_T("�û��������벻��Ϊ�գ�"), _T("����"), MB_ICONWARNING);
	}
}

BOOL COpenQQDlg::InitSocket(void)
{
	DWORD dwIP;
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS))->GetAddress(dwIP);

	m_sockCli = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(dwIP);//inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(GetDlgItemInt(IDC_PORT));//6600

	if (connect(m_sockCli, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR))!=0)
	{
		MessageBox(_T("���ӷ�����ʧ��!"), _T("��ʾ"), MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

SOCKET COpenQQDlg::GetSockCli(void)
{
	return m_sockCli;
}


void COpenQQDlg::OnBnClickedBtnSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szSetStr;
	if (GetDlgItemText(IDC_BTN_SET, szSetStr), szSetStr==_T("���á���"))
	{
		SetDlgItemText(IDC_BTN_SET,_T("�������á���"));
	}
	else
	{
		SetDlgItemText(IDC_BTN_SET,_T("���á���"));
	}

	if (szSetStr == _T("�������á���"))
	{
		SetWindowPos(NULL, 0, 0, 
			m_smallRect.Width(), m_smallRect.Height(), 
			SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL, 0, 0,
			m_largeRect.Width(), m_largeRect.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
}


//��ʼ��ΪС����
void COpenQQDlg::InitWindowSize(void)
{
	if (m_largeRect.IsRectNull())
	{
		CRect sepRect;
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&sepRect);
		GetWindowRect(&m_largeRect);
		m_smallRect.left = m_largeRect.left;
		m_smallRect.top = m_largeRect.top;
		m_smallRect.right = m_largeRect.right;
		m_smallRect.bottom = sepRect.bottom;
	}

	SetWindowPos(NULL, 0, 0, 
			m_smallRect.Width(), m_smallRect.Height(), 
			SWP_NOMOVE | SWP_NOZORDER);
}

void COpenQQDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void COpenQQDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DestroyWindow();
}


void COpenQQDlg::OnBnClickedBtnMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_MINIMIZE);
}


void COpenQQDlg::OnNMClickReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegDlg regDlg;
	regDlg.DoModal();

	*pResult = 0;
}


void COpenQQDlg::OnNMClickReturn(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("Ц�����Ҿ�ûд�һ�����ĳ���"));

	*pResult = 0;
}


void COpenQQDlg::OnBnClickedAutologin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�Զ���½ѡ�У���keyд��ini�ļ�
	if (BST_CHECKED == IsDlgButtonChecked(IDC_AUTOLOGIN))
	{
		::WritePrivateProfileString(_T("�Զ���½"), _T("bAutoLogin"), 
				_T("TRUE"), _T(".\\AutoLogin.ini"));
	}
	else
	{
		::WritePrivateProfileString(_T("�Զ���½"), _T("bAutoLogin"), 
				_T("FALSE"), _T(".\\AutoLogin.ini"));
	}
}


void COpenQQDlg::OnBnClickedRempasswd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString lpPath = _T(".\\RememberPassword.ini");

	CString userName;
	GetDlgItemText(IDC_USERNAME, userName);

	CString passWord;
	GetDlgItemText(IDC_PASSWD, passWord);

	CString szClientCnt;
	szClientCnt.Format(_T("%d"), m_profileAppnameCnt);

	CString szHeadNum;
	szHeadNum.Format(_T("%d"), WhichHeadPic());

	//((CButton *)GetDlgItem(IDC_BTNHEAD))->GetBitmap();

	if (BST_CHECKED == IsDlgButtonChecked(IDC_REMPASSWD))
	{
		::WritePrivateProfileString(szClientCnt, _T("UserName"), userName, lpPath);
		::WritePrivateProfileString(userName, _T("Password"), passWord, lpPath);
		::WritePrivateProfileString(userName, _T("HeadNum"), szHeadNum, lpPath);
		m_profileAppnameCnt++;
	}
	else 
	{

	}

	//���������Ҳд��һ�������ļ�
	lpPath = _T(".\\RemPassCnt.ini");
	szClientCnt.Format(_T("%d"), m_profileAppnameCnt);
	::WritePrivateProfileString(_T("�����û����ĸ���"), _T("profileAppnameCnt"), 
		szClientCnt, lpPath);
}


void COpenQQDlg::LoadProfiles(void)
{
	//�������뱣��  ���ٸ��û�
	CString lpPath = _T(".\\RemPassCnt.ini");
	TCHAR szClientCnt[3];
	char chClientCnt[3];

	::GetPrivateProfileString(_T("�����û����ĸ���"), _T("profileAppnameCnt"),
				NULL, szClientCnt, 3, lpPath);
	WideCharToMultiByte(CP_OEMCP, 0, szClientCnt, -1, chClientCnt, 3, 0, FALSE);
	m_profileAppnameCnt = atoi(chClientCnt);

	//���ر�������������ļ�
	lpPath = _T(".\\RememberPassword.ini");
	CFileFind finder;
	BOOL ifFind = finder.FindFile(lpPath);

	if (ifFind)
	{
		//MessageBox(_T("�ļ����ڡ�"));
		//�Զ���ini�ļ����뱣����û���������
		TCHAR userName[20];
		TCHAR passWord[20];
		UINT headNum;
		for (int i=0; i<m_profileAppnameCnt; i++)
		{
			CString szCnt;
			szCnt.Format(_T("%d"), i);
			::GetPrivateProfileString(szCnt, _T("UserName"), NULL,  userName, 
					20, lpPath);
			::GetPrivateProfileString(userName, _T("Password"), NULL,  passWord, 
					20, lpPath);
			headNum = ::GetPrivateProfileInt(userName, _T("HeadNum"), 0, lpPath);
			//MessageBox(passWord, userName);
			int j;
			CString repeatStr;
			for (j=0; j<((CComboBox *)GetDlgItem(IDC_USERNAME))->GetCount(); j++)
			{
				((CComboBox *)GetDlgItem(IDC_USERNAME))->GetLBText(j, repeatStr);
				if (!_tcscmp(userName, repeatStr))
				{
					break;
				}
			}

			if (j == ((CComboBox *)GetDlgItem(IDC_USERNAME))->GetCount())
			{
				((CComboBox *)GetDlgItem(IDC_USERNAME))->InsertString(-1, userName);
				LoadHeadPic(headNum);
				SetDlgItemText(IDC_USERNAME, userName);
				SetDlgItemText(IDC_PASSWD, passWord);
			}
		}

		//��checkbox���Ϊ��ѡ
		((CButton *)GetDlgItem(IDC_REMPASSWD))->SetCheck(1);
	}

	//�����Զ���½�������ļ�
	lpPath = _T(".\\AutoLogin.ini");
	ifFind = finder.FindFile(lpPath);
	TCHAR bAutoLogin[6];
	::GetPrivateProfileString(_T("�Զ���½"), _T("bAutoLogin"), 
			_T("FALSE"), bAutoLogin, 
				6, _T(".\\AutoLogin.ini"));
	if (ifFind)
	{
		if (!_tcscmp(bAutoLogin, _T("TRUE")))
		{
			((CButton *)GetDlgItem(IDC_AUTOLOGIN))->SetCheck(1);
			OnBnClickedBtnlogin();
		}
	}

	return ;
}


void COpenQQDlg::OnCbnSelchangeUsername()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csUser;
	CString lpPath = _T(".\\RememberPassword.ini");
	CString szCnt;
	CString tUser;
	TCHAR userName[20];
	TCHAR passWord[20];
	int nSel = ((CComboBox*)GetDlgItem(IDC_USERNAME))->GetCurSel();
	if (-1 != nSel)
	{
		 ((CComboBox*)GetDlgItem(IDC_USERNAME))->GetLBText(nSel, csUser);
		 for (int i=0; i<m_profileAppnameCnt; i++)
		 {
			szCnt.Format(_T("%d"), i);
			::GetPrivateProfileString(szCnt, _T("UserName"), NULL,  userName, 
					20, lpPath);
			tUser = userName;

			if (tUser == csUser)
			{
				::GetPrivateProfileString(userName, _T("Password"), NULL,  passWord, 
					20, lpPath);
				SetDlgItemText(IDC_USERNAME, userName);
				SetDlgItemText(IDC_PASSWD, passWord);
				break;
			}
		 }
	} 

}

HBRUSH COpenQQDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
	if(   CTLCOLOR_STATIC   ==   nCtlColor   )  
	//if (pWnd->GetDlgCtrlID() == IDC_HEHE)
	{ 
		//pDC->SetBkColor(RGB(255,0,0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0,   0,   0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}  
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void COpenQQDlg::OnBnClickedBtnAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



void COpenQQDlg::LoadHeadPic(UINT headNum)
{
	HBITMAP   hBitmap; 
	switch (headNum)
	{
	case 0:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 1:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD1));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 2:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD2));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 3:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD3));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 4:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD4));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 5:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD5));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;

	case 6:
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD6));	
		((CButton *)GetDlgItem(IDC_BTNHEAD))->SetBitmap(hBitmap);
		break;
	}
	return ;
}


UINT COpenQQDlg::WhichHeadPic(void)
{
	HBITMAP   hBitmap;
	hBitmap =((CButton *)GetDlgItem(IDC_BTNHEAD))->GetBitmap();

	if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD1)))
			return 1;
	else if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD2)))
			return 2;
	else if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD3)))
			return 3;
	else if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD4)))
			return 4;
	else if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD5)))
			return 5;
	else if (hBitmap ==  LoadBitmap(AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(IDB_BTHEAD6)))
			return 6;
	else
		return 0;
}


HICON COpenQQDlg::GetHICONByHeadNum(UINT headNum)
{
	HICON hIcon;
	switch (headNum)
	{
	case 0:
		hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		break;

	case 1:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD1);
		break;

	case 2:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD2);
		break;

	case 3:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD3);
		break;

	case 4:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD4);
		break;

	case 5:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD5);
		break;

	case 6:
		hIcon = AfxGetApp()->LoadIcon(IDI_HEAD6);
		break;
	}
	return hIcon;
}
