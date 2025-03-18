// CgHeadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenQQ.h"
#include "CgHeadDlg.h"
#include "afxdialogex.h"

#include "OpenQQDlg.h"

#include "FriDlg.h"

// CCgHeadDlg �Ի���

IMPLEMENT_DYNAMIC(CCgHeadDlg, CDialogEx)

CCgHeadDlg::CCgHeadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCgHeadDlg::IDD, pParent)
{

}

CCgHeadDlg::~CCgHeadDlg()
{
}

void CCgHeadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCgHeadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTNHEAD1, &CCgHeadDlg::OnBnClickedBtnhead1)
	ON_BN_CLICKED(IDC_BTNHEAD2, &CCgHeadDlg::OnBnClickedBtnhead2)
	ON_BN_CLICKED(IDC_BTNHEAD3, &CCgHeadDlg::OnBnClickedBtnhead3)
	ON_BN_CLICKED(IDC_BTNHEAD4, &CCgHeadDlg::OnBnClickedBtnhead4)
	ON_BN_CLICKED(IDC_BTNHEAD5, &CCgHeadDlg::OnBnClickedBtnhead5)
	ON_BN_CLICKED(IDC_BTNHEAD6, &CCgHeadDlg::OnBnClickedBtnhead6)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CCgHeadDlg::OnBnClickedBtnClose)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCgHeadDlg ��Ϣ�������


BOOL CCgHeadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���ͷ��
	HBITMAP hBmp;
	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD1));
	((CButton *)GetDlgItem(IDC_BTNHEAD1))->SetBitmap(hBmp);

	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD2));
	((CButton *)GetDlgItem(IDC_BTNHEAD2))->SetBitmap(hBmp);

	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD3));
	((CButton *)GetDlgItem(IDC_BTNHEAD3))->SetBitmap(hBmp);

	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD4));
	((CButton *)GetDlgItem(IDC_BTNHEAD4))->SetBitmap(hBmp);

	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD5));
	((CButton *)GetDlgItem(IDC_BTNHEAD5))->SetBitmap(hBmp);

	hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BTHEAD6));
	((CButton *)GetDlgItem(IDC_BTNHEAD6))->SetBitmap(hBmp);

	return TRUE; 
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCgHeadDlg::OnBnClickedBtnhead1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//AfxGetMainWnd  ��ȡ������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD1)));

	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD1));

	UpdateHeadPic(1);
}


void CCgHeadDlg::OnBnClickedBtnhead2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD2)));
	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD2));

	UpdateHeadPic(2);
}

void CCgHeadDlg::OnBnClickedBtnhead3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD3)));

	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD3));

	UpdateHeadPic(3);
}


void CCgHeadDlg::OnBnClickedBtnhead4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD4)));

	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD4));

	UpdateHeadPic(4);
}


void CCgHeadDlg::OnBnClickedBtnhead5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD5)));

	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD5));

	UpdateHeadPic(5);
}


void CCgHeadDlg::OnBnClickedBtnhead6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton *)AfxGetMainWnd()->GetDlgItem(IDC_BTNHEAD))->SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BTHEAD6)));

	((CButton *)GetParent()->GetDlgItem(IDC_BTN_HEAD))->SetIcon(AfxGetApp()->LoadIcon(IDI_HEAD6));

	UpdateHeadPic(6);
}


void CCgHeadDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//�������ͬ��ͷ��

	CDialogEx::OnCancel();
}


void CCgHeadDlg::UpdateHeadPic(UINT headNum)
{
	SendMsg sendMsg;
	CString windowText;
	((CFriDlg *)GetParent())->GetWindowText(windowText);
	sendMsg.isHeadPic = TRUE;
	_tcscpy(sendMsg.userName, windowText);
	sendMsg.headNum = headNum;
	send(((CFriDlg *)GetParent())->GetSockCli(), (char *)&sendMsg, sizeof(sendMsg), 0);
}

void CCgHeadDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CCgHeadDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCgHeadDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BTBK4);

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


HBRUSH CCgHeadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
