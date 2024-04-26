// CFailDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CFailDlg.h"


// CFailDlg 对话框

IMPLEMENT_DYNAMIC(CFailDlg, CDialogEx)

CFailDlg::CFailDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FAIL_DIALOG, pParent)
{

}

CFailDlg::~CFailDlg()
{
}

void CFailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFailDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FAIL, &CFailDlg::OnBnClickedBtnFail)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFailDlg 消息处理程序


void CFailDlg::OnBnClickedBtnFail()
{
	this->EndDialog(0);
}


BOOL CFailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//绘制图标
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	//设置对话框标题——基本模式
	CString title("欢乐连连看——游戏失败");
	SetWindowText(title);
	//初始化背景图片
	InitBackground();
	//调整游戏窗口大小
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFailDlg::InitBackground()
{
	//初始化内存CD
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\fail.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
}

void CFailDlg::UpdateWindow()
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


void CFailDlg::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0, 0, 400, 300, &m_dcMem, 0, 0, SRCCOPY);
	Invalidate(FALSE);
	CDialogEx::OnPaint();
}
