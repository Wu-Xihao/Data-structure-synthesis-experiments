// CSettleDialog.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CSettleDialog.h"
#include "CPage0.h"
#include "CPage1.h"


// CSettleDialog 对话框

IMPLEMENT_DYNAMIC(CSettleDialog, CDialogEx)

CSettleDialog::CSettleDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTLE_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSettleDialog::~CSettleDialog()
{
}

void CSettleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}


BEGIN_MESSAGE_MAP(CSettleDialog, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CSettleDialog::OnTcnSelchangeTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, &CSettleDialog::OnTcnSelchangingTab)
END_MESSAGE_MAP()


// CSettleDialog 消息处理程序


BOOL CSettleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString title("欢乐连连看——设置");
	SetWindowText(title);
	UpdateWindow();
	InitTab();

	return TRUE;
}

void CSettleDialog::InitTab()
{
	m_Tab.InsertItem(0, _T("主题设置"));
	m_Tab.InsertItem(1, _T("难度设置"));
	page0.Create(IDD_PAGE0, &m_Tab);
	page1.Create(IDD_PAGE1, &m_Tab);

	CRect rect;
	m_Tab.GetClientRect(&rect);
	rect.top += 25;
	rect.bottom -= 5;
	rect.right += 5;
	rect.right -= 5;
	page0.MoveWindow(&rect);
	page1.MoveWindow(&rect);
	page0.SetParent(&m_Tab);
	page1.SetParent(&m_Tab);
	page0.ShowWindow(TRUE);
	m_Tab.SetCurSel(0);

}

void CSettleDialog::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 600 + nSpanWidth, 300 + nSpanHeight);
	CenterWindow();
}


void CSettleDialog::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	cursel = m_Tab.GetCurSel();
	switch (cursel) {
	case 0:
		page0.ShowWindow(TRUE);
		page1.ShowWindow(FALSE);
		break;
	case 1:
		page0.ShowWindow(FALSE);
		page1.ShowWindow(TRUE);
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CSettleDialog::OnTcnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	cursel = m_Tab.GetCurSel();
	*pResult = 0;
}
