#pragma once
#include "afxdialogex.h"
#include <string>

extern std::string PATH;
extern int SelBG;
// CPage0 对话框

class CPage0 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage0)

public:
	CPage0(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage0();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	virtual BOOL OnInitDialog();
	CButton radio1;
	CButton radio2;
	CButton radio3;
	CButton radio4;
	HICON m_hIcon;
	CDC m_dcMem;
	std::string BGPath;
	void InitBackground();
	afx_msg void OnPaint();
};
