#pragma once
#include "afxdialogex.h"
#include "CPage0.h"
#include "CPage1.h"
// CSettleDialog 对话框

class CSettleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettleDialog)

public:
	CSettleDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTLE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	CTabCtrl m_Tab;
	CPage0 page0;
	CPage1 page1;
	int cursel;
	virtual BOOL OnInitDialog();
	void InitTab();
	void UpdateWindow();
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
};
