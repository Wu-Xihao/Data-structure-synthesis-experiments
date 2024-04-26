#pragma once
#include "afxdialogex.h"
#include <string>


// CSetDialog 对话框

class CSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDialog)

public:
	CSetDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	HICON m_hIcon;
	CDC m_dcMem;
	std::string BGPath;
	int m_nRow;
	int m_nCol;
	int m_nElem;
	int m_nTime;
	CEdit m_editRow;
	CEdit m_editCol;
	CEdit m_editElem;
	CEdit m_editTime;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditRow();
	afx_msg void OnEnChangeEditCol();
	afx_msg void OnEnChangeEditElem();
	afx_msg void OnEnChangeEditTime();
	void InitBackground();
	void UpdateWindow();
	void CheckData();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void SetData(int data[4]);
	int* GetData(); 
};
