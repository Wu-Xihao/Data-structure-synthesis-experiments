// CPage1.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CPage1.h"

extern int Rows;
extern int Cols;
extern int Elem;
extern int Time;

// CPage1 对话框

IMPLEMENT_DYNAMIC(CPage1, CDialogEx)

CPage1::CPage1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE1, pParent)
{
	m_nRow = Rows;
	m_nCol = Cols;
	m_nElem = Elem;
	m_nTime = Time;
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_ROW1, edit_row);
	DDX_Control(pDX, IDC_EDIT_COL1, edit_col);
	DDX_Control(pDX, IDC_EDIT_ELEM1, edit_elem);
	DDX_Control(pDX, IDC_EDIT_TIME1, edit_time);
}


BEGIN_MESSAGE_MAP(CPage1, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ROW1, &CPage1::OnEnChangeEditRow)
	ON_EN_CHANGE(IDC_EDIT_COL1, &CPage1::OnEnChangeEditCol)
	ON_EN_CHANGE(IDC_EDIT_ELEM1, &CPage1::OnEnChangeEditElem)
	ON_EN_CHANGE(IDC_EDIT_TIME1, &CPage1::OnEnChangeEditGametime)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPage1::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CPage1 消息处理程序


void CPage1::OnEnChangeEditRow()
{
	CString row;
	edit_row.GetWindowText(row);
	m_nRow = _ttoi(row);
}


void CPage1::OnEnChangeEditCol()
{
	CString col;
	edit_col.GetWindowText(col);
	m_nCol = _ttoi(col);
}


void CPage1::OnEnChangeEditElem()
{
	CString elem;
	edit_elem.GetWindowText(elem);
	m_nElem = _ttoi(elem);
}


void CPage1::OnEnChangeEditGametime()
{
	CString time;
	edit_time.GetWindowText(time);
	m_nTime = _ttoi(time);
}


void CPage1::OnBnClickedButtonOk()
{
	if (CheckData()) {
		GetDlgItem(IDC_BUTTON_OK)->SetWindowTextW(L"成功");
	}
}


bool CPage1::CheckData()
{
	if ((m_nRow * m_nCol) % (m_nElem * 2) != 0) {
		MessageBoxW(_T("元素不匹配！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	if (m_nRow == 0) {
		MessageBoxW(_T("行数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	else if (m_nRow < 0 || m_nRow>10) {
		MessageBoxW(_T("不匹配，请重新行数（0-10）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	if (m_nCol == 0) {
		MessageBoxW(_T("列数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	else if (m_nCol <= 0 || m_nCol > 14) {
		MessageBoxW(_T("不匹配，请重新输入列数（0-14）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	if (m_nElem == 0) {
		MessageBoxW(_T("元素数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	else if (m_nElem < 0 || m_nElem>16) {
		MessageBoxW(_T("不匹配，请重新输入元素数（0-16）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	if (m_nTime == 0) {
		MessageBoxW(_T("时间输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	else if (m_nTime < 0) {
		MessageBoxW(_T("请重新输入时间！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return false;
	}
	Rows = m_nRow;
	Cols = m_nCol;
	Elem = m_nElem;
	Time = m_nTime;
	return true;
}


BOOL CPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString row;
	CString col;
	CString elem;
	CString time;
	row.Format(_T("%d"), m_nRow);
	col.Format(_T("%d"), m_nCol);
	elem.Format(_T("%d"), m_nElem);
	time.Format(_T("%d"), m_nTime);
	edit_row.SetWindowTextW(row);
	edit_col.SetWindowTextW(col);
	edit_elem.SetWindowTextW(elem);
	edit_time.SetWindowTextW(time);

	return TRUE; 
}
