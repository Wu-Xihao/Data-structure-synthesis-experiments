#pragma once
#include "afxdialogex.h"


// CPage1 对话框

class CPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	int m_nRow;
	int m_nCol;
	int m_nElem;
	int m_nTime;
	afx_msg void OnEnChangeEditRow();
	afx_msg void OnEnChangeEditCol();
	afx_msg void OnEnChangeEditElem();
	afx_msg void OnEnChangeEditGametime();
	afx_msg void OnBnClickedButtonOk();
	bool CheckData();
	CEdit edit_row;
	CEdit edit_col;
	CEdit edit_elem;
	CEdit edit_time;
	virtual BOOL OnInitDialog();
};
