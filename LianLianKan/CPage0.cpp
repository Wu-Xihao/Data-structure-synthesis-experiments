// CPage0.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CPage0.h"
#include <string>

extern std::string PATH;
extern int SelBG;
// CPage0 对话框

IMPLEMENT_DYNAMIC(CPage0, CDialogEx)

CPage0::CPage0(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE0, pParent)
{

}

CPage0::~CPage0()
{
}

void CPage0::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, radio1);
	DDX_Control(pDX, IDC_RADIO2, radio2);
	DDX_Control(pDX, IDC_RADIO3, radio3);
	DDX_Control(pDX, IDC_RADIO4, radio4);
}


BEGIN_MESSAGE_MAP(CPage0, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CPage0::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPage0::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CPage0::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CPage0::OnBnClickedRadio4)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPage0 消息处理程序

void CPage0::OnBnClickedRadio1()
{
	PATH = "theme\\picture\\bk1.bmp";
	SelBG = 1;
}

void CPage0::OnBnClickedRadio2()
{
	PATH = "theme\\picture\\bk4.bmp";
	SelBG = 2;
}

void CPage0::OnBnClickedRadio3()
{
	PATH = "theme\\picture\\bk6.bmp";
	SelBG = 3;
}

void CPage0::OnBnClickedRadio4()
{
	PATH = "theme\\picture\\bk7.bmp";
	SelBG = 4;
}


BOOL CPage0::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//InitBackground();
	switch (SelBG) {
	case 1:
		radio1.SetCheck(1);
		break;
	case 2:
		radio2.SetCheck(1);
		break;
	case 3:
		radio3.SetCheck(1);
		break;
	case 4:
		radio4.SetCheck(1);
		break;
	default:
		break;
	}
	return TRUE;
}

void CPage0::InitBackground()
{
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\bk3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
}


void CPage0::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0, 0, 600, 300, &m_dcMem, 0, 0, SRCCOPY);
}
