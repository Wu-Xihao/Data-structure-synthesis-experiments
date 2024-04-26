#pragma once
#include "afxdialogex.h"


// CFailDlg 对话框

class CFailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFailDlg)

public:
	CFailDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFailDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAIL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnFail();
	virtual BOOL OnInitDialog();
public:
	HICON m_hIcon;
	CDC m_dcMem;
	void InitBackground();
	void UpdateWindow();
};
