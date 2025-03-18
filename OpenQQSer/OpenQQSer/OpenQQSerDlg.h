
// OpenQQSerDlg.h : ͷ�ļ�
//

#pragma once
#include "userinfo.h"
#include "afxcmn.h"
#include "sendmsg.h"
#include "afx.h"

#define WM_SOCK WM_USER+1

// COpenQQSerDlg �Ի���
class COpenQQSerDlg : public CDialogEx
{
// ����
public:
	COpenQQSerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENQQSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT OnSock(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedCancel();
private:
	// //��������¼���߿ͻ��˵�����
	int m_clientCnt;
public:
	afx_msg void OnBnClickedBtnbg();
	BOOL InitSocket(void);
private:
	SOCKET m_sockSrv;
	SOCKET m_sockCli[256];
public:
	afx_msg void OnBnClickedBtned();
private:
	UserInfo m_user[255];
	CListCtrl m_userList;
public:
	void InitListCtr(void);
private:
	SendMsg m_recvMsg;
public:
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CFile m_recvFile;
	BOOL m_firstRecvFile;
	CString m_recvFilePath;
public:
	BOOL VerifyUser(const CString& vUserName, const CString& vUserPasswd);
	BOOL WriteRegInfoToProfile(const CString &wUserName, const CString &wPasswd, const UINT & headNum);
private:
	int m_registerUserCnt;
public:
	void LoadClientCnt(void);
	BOOL VerifyRepeatLogin(const CString & loginUserName);
	void UpdateHeadPic(const CString & userName, const UINT & headNum);
private:
	UINT m_tHeadNum;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
