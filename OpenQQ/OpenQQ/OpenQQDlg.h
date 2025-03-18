
// OpenQQDlg.h : ͷ�ļ�
//

#pragma once
#include "atltypes.h"

// COpenQQDlg �Ի���
class COpenQQDlg : public CDialogEx
{
// ����
public:
	COpenQQDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~COpenQQDlg();
// �Ի�������
	enum { IDD = IDD_OPENQQ_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnlogin();
	BOOL InitSocket(void);
private:
	SOCKET m_sockCli;
public:
	SOCKET GetSockCli(void);
	afx_msg void OnBnClickedBtnSet();
	void InitWindowSize(void);
private:
	CRect m_largeRect;
	CRect m_smallRect;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnNMClickReg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickReturn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAutologin();
	afx_msg void OnBnClickedRempasswd();
	void LoadProfiles(void);
private:
	int m_profileAppnameCnt;
public:
	afx_msg void OnCbnSelchangeUsername();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnAbout();
//	afx_msg void OnBnClickedBtnhead();
	void LoadHeadPic(UINT headNum);
	UINT WhichHeadPic(void);
	HICON GetHICONByHeadNum(UINT headNum);
};
