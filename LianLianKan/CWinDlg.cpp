// CWinDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CWinDlg.h"


// CWinDlg 对话框

IMPLEMENT_DYNAMIC(CWinDlg, CDialogEx)

CWinDlg::CWinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WIN_DIALOG, pParent)
{
	//加载图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CWinDlg::~CWinDlg()
{
}

void CWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWinDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_WIN, &CWinDlg::OnBnClickedBtnWin)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWinDlg 消息处理程序


void CWinDlg::OnBnClickedBtnWin()
{
	this->EndDialog(0);
}

BOOL CWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//绘制图标
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	//设置对话框标题——游戏胜利
	CString title("欢乐连连看——游戏胜利");
	SetWindowText(title);
	//初始化背景图片
	InitBackground();
	//调整游戏窗口大小
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWinDlg::InitBackground()
{
	//初始化内存CD
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\win.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
}

void CWinDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 400 + nSpanWidth, 300 + nSpanHeight);
	CenterWindow();
}

void CWinDlg::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0, 0, 400, 300, &m_dcMem, 0, 0, SRCCOPY);
	Invalidate(FALSE);
	CDialogEx::OnPaint();
}
