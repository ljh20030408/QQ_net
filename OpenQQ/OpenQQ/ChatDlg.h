#pragma once

#include "SendMsg.h"
#include "afx.h"
#include "afxcmn.h"

#define WM_SUBWINDOW WM_USER+2

// CChatDlg �Ի���

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChatDlg();

// �Ի�������
	enum { IDD = IDD_CHATDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnSubWindow(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnsend();
private:
	SOCKET m_sockCli;
public:
	virtual BOOL OnInitDialog();
private:
	SendMsg m_sendMsg;
//	HWND m_recvHwnd;
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedWndshake();
	afx_msg void OnBnClickedFile();
public:
	CProgressCtrl m_transFilePro;
};
