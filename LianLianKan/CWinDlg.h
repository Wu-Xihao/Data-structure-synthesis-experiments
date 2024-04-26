#pragma once
#include "afxdialogex.h"


// CWinDlg 对话框

class CWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWinDlg)

public:
	CWinDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWinDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnWin();
	virtual BOOL OnInitDialog();
public:
	HICON m_hIcon;
	CDC m_dcMem;
	void InitBackground();
	void UpdateWindow();
	
};
