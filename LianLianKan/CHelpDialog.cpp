// CHelpDialog.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CHelpDialog.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pos = 0;
	m_rtHelp.top = 0;
	m_rtHelp.bottom = 450;
	m_rtHelp.left = 0;
	m_rtHelp.right = 600;
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR, m_ScrollBar);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString title("欢乐连连看——帮助");
	SetWindowText(title);
	//更新窗口大小
	UpdateWindow();
	//初始化图片
	InitGraph();
	InvalidateRect(m_rtHelp, FALSE);
	m_ScrollBar.SetScrollRange(0, 900, TRUE);
	m_ScrollBar.SetScrollPos(0);
	//UpdateHelp(0);
	return TRUE;
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this);
	//UpdateHelp(pos);
	dc.BitBlt(0, 0, 600, 450, &m_dcMem, 0, 0, SRCCOPY);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == &m_ScrollBar) {
		switch (nSBCode)
		{
		case SB_THUMBTRACK: // 拖动滚动滑块时 
			m_ScrollBar.SetScrollPos(nPos);
			pos = m_ScrollBar.GetScrollPos();
			break;
		case SB_LINEUP:
			pos = m_ScrollBar.GetScrollPos() - 10;
			if (pos < 0) {
				pos = 0;
			}
			m_ScrollBar.SetScrollPos(pos);
			break;
		case SB_LINEDOWN:
			pos = m_ScrollBar.GetScrollPos() + 50;
			if (pos > 900) {
				pos = 900;
			}
			m_ScrollBar.SetScrollPos(pos);
			break;
		case SB_PAGEUP:
			pos = m_ScrollBar.GetScrollPos() - 50;
			if (pos < 0) {
				pos = 0;
			}
			m_ScrollBar.SetScrollPos(pos);
			break;
		case SB_PAGEDOWN:
			pos = m_ScrollBar.GetScrollPos() + 100;
			if (pos > 900) {
				pos = 900;
			}
			m_ScrollBar.SetScrollPos(pos);
			break;
		case SB_TOP:
			m_ScrollBar.SetScrollPos(0);
			break;
		case SB_BOTTOM:
			m_ScrollBar.SetScrollPos(900);
			break;
		default:
			break;
		}
		UpdateHelp(pos);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHelpDialog::InitGraph()
{
	//初始化内存CD
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
	HANDLE bk = ::LoadImageW(NULL, _T("theme\\picture\\help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dcBK(this);
	m_dcHelp.CreateCompatibleDC(&dcBK);
	m_dcHelp.SelectObject(bk);
}

void CHelpDialog::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 600 + nSpanWidth, 450 + nSpanHeight);
	CenterWindow();
}

void CHelpDialog::UpdateHelp(int nPos)
{
	m_dcMem.BitBlt(0, 0, 600, 450, &m_dcHelp, 0, pos, SRCCOPY);
	//InvalidateRect(m_rtHelp, FALSE);
	Invalidate(FALSE);
}
