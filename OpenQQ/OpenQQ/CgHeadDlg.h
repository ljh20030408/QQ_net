#pragma once


// CCgHeadDlg �Ի���

class CCgHeadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCgHeadDlg)

public:
	CCgHeadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCgHeadDlg();

// �Ի�������
	enum { IDD = IDD_CGHEADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnhead1();
	afx_msg void OnBnClickedBtnhead2();
	afx_msg void OnBnClickedBtnhead3();
	afx_msg void OnBnClickedBtnhead4();
	afx_msg void OnBnClickedBtnhead5();
	afx_msg void OnBnClickedBtnhead6();
	virtual void OnCancel();
	void UpdateHeadPic(UINT headNum);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
