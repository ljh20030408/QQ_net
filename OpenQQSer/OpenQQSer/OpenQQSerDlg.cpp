
// OpenQQSerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenQQSer.h"
#include "OpenQQSerDlg.h"
#include "afxdialogex.h"

#include "UserInfo.h"

#include "SendMsg.h"

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


// COpenQQSerDlg �Ի���




COpenQQSerDlg::COpenQQSerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenQQSerDlg::IDD, pParent)
	, m_clientCnt(0)
	, m_firstRecvFile(TRUE)
	, m_recvFilePath(_T(""))
	, m_registerUserCnt(0)
	, m_tHeadNum(0)
{
	for (int i=0; i<255; i++)
	{
		m_user[i].bOnLine = FALSE;
		m_user[i].accFlag = FALSE;
	}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenQQSerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_userList);
}

BEGIN_MESSAGE_MAP(COpenQQSerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNBG, &COpenQQSerDlg::OnBnClickedBtnbg)
	ON_MESSAGE(WM_SOCK, OnSock)
	ON_BN_CLICKED(IDC_BTNED, &COpenQQSerDlg::OnBnClickedBtned)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &COpenQQSerDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_MIN, &COpenQQSerDlg::OnBnClickedBtnMin)
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COpenQQSerDlg ��Ϣ�������

BOOL COpenQQSerDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ���б��
	InitListCtr();
	//�����¼�û���Ŀ
	LoadClientCnt();

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COpenQQSerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COpenQQSerDlg::OnPaint()
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
HCURSOR COpenQQSerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenQQSerDlg::OnBnClickedBtnbg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ����֮��
	
	InitSocket();
	//MessageBox(_T("�����ѿ���"));
	((CButton *)GetDlgItem(IDC_BTNBG))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_BTNED))->EnableWindow(TRUE);
}


BOOL COpenQQSerDlg::InitSocket(void)
{
	m_sockSrv = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6600);
	
	bind(m_sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));

	WSAAsyncSelect(m_sockSrv, m_hWnd, WM_SOCK, FD_READ | FD_WRITE | FD_ACCEPT | FD_CLOSE);

	listen(m_sockSrv, 5);

	return TRUE;
}

LRESULT COpenQQSerDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	SOCKET s = wParam;

	char chRecvMsg[512];
	memset(chRecvMsg, 0, 512);
	CString logInfo;
	CString logTempInfo;
	//char tempName[30];
	CString fromatMsg;
	char sendMsg[256];
	BOOL isOnce = TRUE;
	CTime currTime = CTime::GetCurrentTime();
	logTempInfo = currTime.Format("%H:%M:%S ");
	int i, j, k;
	switch (LOWORD(lParam))
	{
	case FD_READ:
		//���ж��Ƿ��һ������
		//m_clientCnt Ϊ���еĿͻ����������ߺ����ߵ��û���
		for (int i=0; i<m_clientCnt; i++)
		{
			if (m_user[i].userSocket == s)
			{
				//�������socket˵�����ǵ�һ��  
				//Ҫô������  Ҫô�ǽ����״̬����Ϊ����

				isOnce = FALSE;
				break;
			}
		}

		//����ǵ�һ�Σ���ô�͸�������Ϣ����Ӧ��listctrl
		if (isOnce) 
		{
			//��һ�����ӵ�ʱ����ȡ�û���������Ϣ
			if (/*m_user[m_clientCnt].bOnLine == FALSE && */m_user[m_clientCnt].accFlag == TRUE)
			{
				recv(s, (char *)&m_user[m_clientCnt], sizeof(m_user[m_clientCnt]), 0);

				//�ж��ǲ���ע����Ϣ
				if (m_user[m_clientCnt].isRegister == TRUE)
				{
					//д�뵽�����ļ�
					if (WriteRegInfoToProfile(m_user[m_clientCnt].userName, 
						m_user[m_clientCnt].passWord, m_user[m_clientCnt].headNum) == TRUE)
					{
						send(s, "Register success!", strlen("Register success!")+1, 0);
					}
					else
					{
						send(s, "Register failure!", strlen("Register failure!")+1, 0);
					}
					closesocket(s);
					return 0;
				}


				//��֤�û���������
				if (VerifyUser(m_user[m_clientCnt].userName, 
					m_user[m_clientCnt].passWord) == FALSE)
				{
					send(s, "failure", strlen("failure")+1, 0);
					closesocket(s);
					return 0;
				}
				else if (VerifyRepeatLogin(m_user[m_clientCnt].userName) == TRUE)
				{
					send(s, "repeat login", strlen("repeat login")+1, 0);
					closesocket(s);
					return 0;
				}
				else 
				{
					send(s, "success", strlen("success")+1, 0);
					//send(s, (char *)&m_tHeadNum, sizeof(m_tHeadNum), 0);

					SendMsg setPicMsg;
					setPicMsg.isHeadPic = TRUE;
					setPicMsg.headNum = m_tHeadNum;
					m_user[m_clientCnt].headNum = m_tHeadNum;
					send(s, (char *)&setPicMsg, sizeof(setPicMsg), 0);

				}

				//����������֮�����ж��ǲ����Ͽͻ������Ͽͻ�ֱ���滻�׽���
				int x;
				for (x=0; x<m_clientCnt; x++)
				{
					if (!_tcscmp(m_user[x].userName, m_user[m_clientCnt].userName))
					{
						//�Ͽͻ�
						if (m_user[x].bOnLine == TRUE)
						{
							//MessageBox(_T("�Ѿ���½!"));
							//��õ�½���淢����Ϣ��

							//send(s, "the same", strlen("the same")+1, 0); 
							return 0;
						}
						else
						{
							//send(s, "no the same", strlen("no the same")+1, 0); 
							m_user[x].userSocket = s;
						}
						break;
					}
				}

				//�¿ͻ�
				if (x == m_clientCnt)
				{
					m_user[m_clientCnt].userSocket = s;
					m_user[m_clientCnt].bOnLine = TRUE;
					//m_user[m_clientCnt].headNum = m_tHeadNum;
				
					logInfo.Format(_T("%s �����ˣ�"), m_user[m_clientCnt].userName);
					logTempInfo += logInfo;

					m_userList.InsertItem(m_userList.GetItemCount(), m_user[m_clientCnt].userName);//����
					m_userList.SetItemText(m_userList.GetItemCount()-1, 1, _T("����"));//����


					////���ÿͻ���ͼƬID��ֵ
					/*VerifyUser(m_user[m_clientCnt].userName, m_user[m_clientCnt].passWord);
					m_recvMsg.headNum = this->m_tHeadNum;*/

					//��ʱ�ȼ�һ��ѭ�����������͵���Ϣ������Ϊ���Ѹ��µ���Ϣ
					m_recvMsg.isFriendInfo = TRUE;
					m_recvMsg.isOnLine = TRUE;
					m_recvMsg.isHeadPic = FALSE;
					m_recvMsg.headNum = m_user[m_clientCnt].headNum;
					
					_tcscpy(m_recvMsg.userName,m_user[m_clientCnt].userName);

					//����ǰ���ߵ��Ͽͻ����͸����ߵ��¿ͻ�����Ϣ
					for (int i=0; i<m_clientCnt; i++)
					{
						if (m_user[i].bOnLine == TRUE)
						{
							send(m_user[i].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
						}
					}

					//�����ߵ��¿ͻ������Ͽͻ�����Ϣ
					for (int i=0; i<m_clientCnt; i++)
					{
						if (m_user[i].bOnLine == TRUE)
						{
							m_recvMsg.headNum = m_user[i].headNum;
							_tcscpy(m_recvMsg.userName,m_user[i].userName);
							send(m_user[m_clientCnt].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
						}
					}

					m_clientCnt++;
					((CListBox *)GetDlgItem(IDC_LIST_LOG))->InsertString(-1, logTempInfo);
				}
				else
				{
					//�Ͽͻ�
					//�����Ͽͻ� ����Ϊ����
					m_user[x].bOnLine = TRUE;

					//���Ͽͻ��ı�־����Ϊ����
					for (int n=0; n<m_userList.GetItemCount(); n++)
					{
						if (!_tcscmp(m_user[x].userName, m_userList.GetItemText(n,0)))
						{
							m_userList.SetItemText(n, 1, _T("����"));

							logInfo.Format(_T("%s �����ˣ�"), m_user[m_clientCnt].userName);
							logTempInfo += logInfo;
							((CListBox *)GetDlgItem(IDC_LIST_LOG))->InsertString(-1, logTempInfo);
							break;
						}
					}

					m_recvMsg.isFriendInfo = TRUE;
					m_recvMsg.isOnLine = TRUE;
					m_recvMsg.isHeadPic = FALSE;
					_tcscpy(m_recvMsg.userName,m_user[m_clientCnt].userName);
					m_recvMsg.headNum = m_user[m_clientCnt].headNum;
					for (int i=0; i<m_clientCnt; i++)
					{
						if (!_tcscmp(m_user[i].userName, m_recvMsg.userName))
						{
							m_recvMsg.headNum = m_user[i].headNum;
							break;
						}
					}


					//����ǰ���ߵ��Ͽͻ����͸����ߵ��¿ͻ�����Ϣ
					for (int i=0; i<m_clientCnt; i++)
					{
						if (m_user[i].bOnLine == TRUE)
							send(m_user[i].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
					}

					//�����ߵ��¿ͻ������Ͽͻ�����Ϣ
					for (int i=0; i<m_clientCnt; i++)
					{
						if (m_user[i].bOnLine == TRUE)
						{
							m_recvMsg.headNum = m_user[i].headNum;
							_tcscpy(m_recvMsg.userName,m_user[i].userName);
							send(m_user[x].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
						}
					}
				}
			}
		}
		else
		{
			//�������Ͽͻ��ٴ����ߣ�Ҳ�п���������

			//����  �������û��ı�־λ����ΪFALSE
			//�ж���Ⱥ�Ļ���˽��			
			int rtval =recv(s, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
			//CString recvSize;
			if (SOCKET_ERROR == rtval)
			{
				MessageBox(_T("recv ʧ��"));
			}
			/*else
			{
				recvSize.Format(_T("recv %d"), rtval);
				MessageBox(recvSize);
			}*/

			m_recvMsg.isFriendInfo = FALSE;

			//ͷ�����
			if (m_recvMsg.isHeadPic == TRUE)
			{
				UpdateHeadPic(m_recvMsg.userName, m_recvMsg.headNum);
				return 0;
			}


			//ȡ����Ϣ��ת��Ϊchar*�ַ���
			WideCharToMultiByte(CP_OEMCP, 0, m_recvMsg.sendMsg, -1, sendMsg, 256, 0, FALSE);

			//˽��
			fromatMsg = m_recvMsg.sendUser;
			fromatMsg += _T("   ");
			fromatMsg += currTime.Format("%H:%M:%S ");
			fromatMsg += m_recvMsg.sendMsg;

			////�ж��ǲ��Ǵ��ڶ��� �����ļ�����
			//if ()
			if (m_recvMsg.isWindowShake == TRUE 
				|| m_recvMsg.isFile == TRUE)
			{
				fromatMsg = m_recvMsg.sendMsg;
			}

			_tcscpy(m_recvMsg.sendMsg, fromatMsg.GetBuffer());

			//
			SendMsg tempSendMsg;
			_tcscpy(tempSendMsg.sendUser,m_recvMsg.recvUser);
			_tcscpy(tempSendMsg.recvUser,m_recvMsg.sendUser);
			_tcscpy(tempSendMsg.sendMsg, m_recvMsg.sendMsg);
			tempSendMsg.isFriendInfo = FALSE;
			tempSendMsg.isSingleSend = TRUE;
			tempSendMsg.isFile = m_recvMsg.isFile;
			tempSendMsg.isWindowShake = m_recvMsg.isWindowShake;

			if (m_recvMsg.isSingleSend == TRUE)
			{
				//�ж��ǲ����ļ�����
				if (m_recvMsg.isFile == FALSE)
				{
					send(s, (char *)&tempSendMsg, sizeof(tempSendMsg), 0);
				}

				for (int i=0; i<m_clientCnt; i++)
				{
					if (!_tcscmp(m_recvMsg.recvUser, m_user[i].userName))
					{	
						//���Է�����	
						int rtval = send(m_user[i].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
						//CString sendSize;
						if (SOCKET_ERROR == rtval)
						{
							MessageBox(_T("send ʧ��"));
						}
						break;
					}
				}
			}
			else //Ⱥ��
			{
				for (int i=0; i<m_clientCnt; i++)
				{
					send(m_user[i].userSocket, (char *)&m_recvMsg, sizeof(m_recvMsg), 0);
				}
			}
		}
		break;

	case FD_WRITE:

		break;

	case FD_ACCEPT://�пͻ�������
		accept(s, NULL, NULL);
		m_user[m_clientCnt].accFlag = TRUE;
		//�������ж��Ƿ����Ͽͻ�

		break;

	case FD_CLOSE://�пͻ�������
		for (i=0; i<m_clientCnt; i++)
		{
			if (m_user[i].userSocket == s)
			{
				m_user[i].bOnLine = FALSE;
				logInfo.Format(_T("%s �����ˣ�"), m_user[i].userName);
				logTempInfo += logInfo;
				((CListBox *)GetDlgItem(IDC_LIST_LOG))->InsertString(-1, logTempInfo);

				//m_userList.DeleteItem(i);
				for (int m=0; m<m_userList.GetItemCount(); m++)
				{
					if (!_tcscmp(m_user[i].userName, m_userList.GetItemText(m, 0)))
					{
						//m_userList.DeleteItem(m);
						m_userList.SetItemText(m, 1, _T("����"));
						break;
					}
				}
				
				//�����пͻ��˷���������Ϣ
				SendMsg outOfLineMsg;
				outOfLineMsg.isFriendInfo = TRUE;
				_tcscpy(outOfLineMsg.userName, m_user[i].userName);
				outOfLineMsg.isOnLine = FALSE;

				for (k=0; k<m_clientCnt; k++)
				{
					if (k!=i)
						send(m_user[k].userSocket, (char *)&outOfLineMsg, sizeof(outOfLineMsg), 0);
				}
				break;
			}
		}
	}
	return 0;
}

void COpenQQSerDlg::OnBnClickedBtned()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i=0; i<m_clientCnt; i++)
		closesocket(m_sockCli[i]);
	closesocket(m_sockSrv);

	((CButton *)GetDlgItem(IDC_BTNBG))->EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_BTNED))->EnableWindow(FALSE);
	//MessageBox(_T("������ֹͣ"));
}

void COpenQQSerDlg::InitListCtr(void)
{
	DWORD dwStyle = m_userList.GetExtendedStyle(); //��ʾ������
	dwStyle |= LVS_EX_FULLROWSELECT;            
    dwStyle |= LVS_EX_GRIDLINES;     
	m_userList.SetExtendedStyle(dwStyle);

	m_userList.InsertColumn(0, _T("�û���"), LVCFMT_CENTER, 80);
	m_userList.InsertColumn(1, _T("����״̬"), LVCFMT_CENTER, 80);
}


void COpenQQSerDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DestroyWindow();
}


void COpenQQSerDlg::OnBnClickedBtnMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_MINIMIZE);
}


void COpenQQSerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL COpenQQSerDlg::VerifyUser(const CString& vUserName, const CString& vUserPasswd)
{
	//���������ļ�
	//���ر�������������ļ�
	CString lpPath = _T(".\\userNameAndPasswd.ini");
	CFileFind finder;
	BOOL ifFind = finder.FindFile(lpPath);

	if (ifFind)
	{
		//�Զ���ini�ļ����뱣����û���������
		TCHAR userName[20];
		TCHAR passWord[20];
		for (int i=0; i<m_registerUserCnt; i++)
		{
			CString szCnt;
			szCnt.Format(_T("%d"), i);
			::GetPrivateProfileString(szCnt, _T("UserName"), NULL,  userName, 
					20, lpPath);

			if (!_tcscmp(vUserName, userName))
			{
				TCHAR tcHeadNum[3];
				char chHeadNum[3];
				::GetPrivateProfileString(userName, _T("Password"), NULL,  passWord, 
						20, lpPath);
				::GetPrivateProfileString(userName, _T("HeadNum"), NULL,  tcHeadNum, 
						3, lpPath);

				WideCharToMultiByte(CP_OEMCP, 0, tcHeadNum, -1, chHeadNum, 3, 0, FALSE);

				m_tHeadNum = (UINT)(chHeadNum[0] - 48);

				if (!_tcscmp(vUserPasswd, passWord))
				{
					//�û�����������֤ͨ��
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


BOOL COpenQQSerDlg::WriteRegInfoToProfile(const CString &wUserName, const CString &wPasswd, const UINT & headNum)
{

	CString lpPath = _T(".\\userNameAndPasswd.ini");

	CString szClientCnt;
	szClientCnt.Format(_T("%d"), m_registerUserCnt);

	//��ѭ����������userNameAndPasswd�ļ��������û������ڲ�����
	for (int i=0; i<m_registerUserCnt; i++)
	{
		TCHAR userName[20];
		CString szCnt;
		szCnt.Format(_T("%d"), i);
		::GetPrivateProfileString(szCnt, _T("UserName"), NULL,  userName, 
			20, lpPath);
		//���û������ڣ�д��ʧ��
		if (!_tcscmp(userName, wUserName))
		{
			return FALSE;
		}
	}

	CString szHeadNum;
	szHeadNum.Format(_T("%d"), headNum);

	::WritePrivateProfileString(szClientCnt, _T("UserName"), wUserName, lpPath);
	::WritePrivateProfileString(wUserName, _T("Password"), wPasswd, lpPath);
	::WritePrivateProfileString(wUserName, _T("HeadNum"), szHeadNum, lpPath);//д��ͷ��
	m_registerUserCnt++;

	//���������Ҳд��һ�������ļ�
	lpPath = _T(".\\UserCnt.ini");
	szClientCnt.Format(_T("%d"), m_registerUserCnt);
	::WritePrivateProfileString(_T("ע���û��ĸ���"), _T("RegisterUserCnt"), 
		szClientCnt, lpPath);

	return TRUE;
}


void COpenQQSerDlg::LoadClientCnt(void)
{
	//����һ���ж��ٸ��û�
	CString lpPath = _T(".\\UserCnt.ini");
	TCHAR szClientCnt[3];
	char chClientCnt[3];

	::GetPrivateProfileString(_T("ע���û��ĸ���"), _T("RegisterUserCnt"),
				NULL, szClientCnt, 3, lpPath);
	WideCharToMultiByte(CP_OEMCP, 0, szClientCnt, -1, chClientCnt, 3, 0, FALSE);
	m_registerUserCnt = atoi(chClientCnt);
}


BOOL COpenQQSerDlg::VerifyRepeatLogin(const CString & loginUserName)
{
	for (int i=0; i<this->m_clientCnt; i++)
	{
		if (!_tcscmp(m_user[i].userName, loginUserName))
		{
			if (m_user[i].bOnLine == TRUE)
				return TRUE;
		}
	}
	return FALSE;
}


void COpenQQSerDlg::UpdateHeadPic(const CString & userName, const UINT & headNum)
{
	CString lpPath = _T(".\\userNameAndPasswd.ini");

	CString szClientCnt;
	szClientCnt.Format(_T("%d"), m_registerUserCnt);

	//��ѭ����������userNameAndPasswd�ļ��������û������ڲ�����
	for (int i=0; i<m_registerUserCnt; i++)
	{
		TCHAR chUserName[20];
		CString szCnt;
		szCnt.Format(_T("%d"), i);
		::GetPrivateProfileString(szCnt, _T("UserName"), NULL,  chUserName, 
			20, lpPath);

		if (!_tcscmp(userName, chUserName))
		{
			CString szHeadNum;
			szHeadNum.Format(_T("%d"), headNum);
			::WritePrivateProfileString(chUserName, _T("HeadNum"), szHeadNum, lpPath);//д��ͷ��
			break;
		}
	}

	//�����û���ͷ��idҲ�޸ĵ�
	for (int i=0; i<m_clientCnt; i++)
	{
		if (!_tcscmp(userName, m_user[i].userName))
		{
			m_user[i].headNum = headNum;
			break;
		}
	}
}


HBRUSH COpenQQSerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(CTLCOLOR_STATIC == nCtlColor)  
	{ 
		pDC->SetTextColor(RGB(255, 255, 255));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}  
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
