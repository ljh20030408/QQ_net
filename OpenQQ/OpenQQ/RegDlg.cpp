// RegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenQQ.h"
#include "RegDlg.h"
#include "afxdialogex.h"
#include "OpenQQDlg.h"
#include "UserInfo.h"

// CRegDlg �Ի���

IMPLEMENT_DYNAMIC(CRegDlg, CDialogEx)

CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegDlg::IDD, pParent)
{

}

CRegDlg::~CRegDlg()
{
}

void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	ON_WM_PAINT()

ON_BN_CLICKED(IDC_REG, &CRegDlg::OnBnClickedReg)
ON_BN_CLICKED(IDC_BTN_CLOSE, &CRegDlg::OnBnClickedBtnClose)
ON_WM_LBUTTONDOWN()
ON_WM_PAINT()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRegDlg ��Ϣ�������

void CRegDlg::OnBnClickedReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	 //MessageBox(_T("ע��"));
	if (FALSE == ((COpenQQDlg *)GetParent())->InitSocket())
	{
		return ;
	}

	//����һ���û��ṹ
	UserInfo user;
	user.bOnLine = FALSE;
	user.accFlag = FALSE;
	user.isRegister = TRUE;
	user.headNum = 0; //ע��Ĭ�Ͼ���ͷ��0

	//��ȡ�û���Ϣ
	GetDlgItemText(IDC_USERNAME, user.userName, 20);
	GetDlgItemText(IDC_PASSWD, user.passWord, 20);
	CString passWord2;
	GetDlgItemText(IDC_PASSWD2, passWord2);

	//�ж��û��������벻��Ϊ��
	if (_tcscmp(user.userName, _T("")) 
		&&	_tcscmp(user.passWord, _T("")))
	{
		if (_tcscmp(user.passWord, passWord2))
		{
			MessageBox(_T("�����������벻ƥ�䣬���������룡"));
			return ;
		}

		send(((COpenQQDlg *)GetParent())->GetSockCli(), (char *)&user, sizeof(user), 0);

		char chReg[40];

		recv(((COpenQQDlg *)GetParent())->GetSockCli(), chReg, 40, 0);
		if (!strcmp(chReg, "Register success!"))
		{
			MessageBox(_T("ע��ɹ���"));
		}
		else
		{
			MessageBox(_T("���û����Ѿ����ڣ�ע��ʧ�ܣ�"));
		}
	}
	else
	{
		MessageBox(_T("�û��������벻��Ϊ�գ�"), _T("����"), MB_ICONWARNING);
	}
}


void CRegDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CRegDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRegDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BTREGBK);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


HBRUSH CRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(CTLCOLOR_STATIC == nCtlColor)
	{ 
		//pDC->SetBkColor(RGB(255,0,0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0,   0,   0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}  
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
