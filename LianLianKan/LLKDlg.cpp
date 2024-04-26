
// LLKDlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CHelpDialog.h"
#include "CSetDialog.h"
#include "CSettleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int Score;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDCANCEL, &CAboutDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLLKDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &CLLKDlg::OnBnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CLLKDlg::OnBnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLLKDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLLKDlg::OnBnClickedButtonRank)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化背景图片
	InitBackground();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//设置对话框标题
		CString title("欢乐连连看");
		SetWindowText(title);
		//创建CPaintDC对象
		CPaintDC dc(this);
		//绘制背景图片
		dc.BitBlt(0, 0, GAMEDLGWIDTH, GAMEDLGHEIGHT, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化背景图片函数
void CLLKDlg::InitBackground()
{
	// 加载位图
	CBitmap bmpBK;
	bmpBK.LoadBitmap(IDB_MAIN_BG);
	// 创建一个兼容DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	// 将位图选进DC
	m_dcMem.SelectObject(&bmpBK);

	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	//标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, GAMEDLGWIDTH + nSpanWidth, GAMEDLGHEIGHT + nSpanHeight);
	CenterWindow();
}


//点击基本模式时的事件处理函数
void CLLKDlg::OnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(nullptr,1);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnBnClickedButtonRelax()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(nullptr,2);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnBnClickedButtonLevel()
{
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(nullptr,3);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedButtonHelp()
{
	CHelpDialog helpDlg;
	helpDlg.DoModal();
}


void CLLKDlg::OnBnClickedButtonSetting()
{
	CSettleDialog settleDlg;
	settleDlg.DoModal();
}




void CLLKDlg::OnBnClickedButtonRank()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string s = "游戏积分：";
	s = s + std::to_string(Score);
	CString text(s.c_str());
	MessageBoxW(text, _T("游戏积分"), MB_OK);
}
