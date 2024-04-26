// CSetDialog.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CSetDialog.h"
#include "global.h"

extern int Rows;
extern int Cols;
extern int Elem;
extern int Time;
// CSetDialog 对话框

IMPLEMENT_DYNAMIC(CSetDialog, CDialogEx)

CSetDialog::CSetDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nRow = Rows;
	m_nCol = Cols;
	m_nElem = Elem;
	m_nTime = Time;
}

CSetDialog::~CSetDialog()
{
}

void CSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROW, m_editRow);
	DDX_Control(pDX, IDC_EDIT_COL, m_editCol);
	DDX_Control(pDX, IDC_EDIT_ELEM, m_editElem);
	DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
}


BEGIN_MESSAGE_MAP(CSetDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ROW, &CSetDialog::OnEnChangeEditRow)
	ON_EN_CHANGE(IDC_EDIT_COL, &CSetDialog::OnEnChangeEditCol)
	ON_EN_CHANGE(IDC_EDIT_ELEM, &CSetDialog::OnEnChangeEditElem)
	ON_EN_CHANGE(IDC_EDIT_TIME, &CSetDialog::OnEnChangeEditTime)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CSetDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSetDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetDialog 消息处理程序


BOOL CSetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString title("欢乐连连看——设置");
	SetWindowText(title);
	UpdateWindow();
	InitBackground();
	CString row;
	CString col;
	CString elem;
	CString time;
	row.Format(_T("%d"), m_nRow);
	col.Format(_T("%d"), m_nCol);
	elem.Format(_T("%d"), m_nElem);
	time.Format(_T("%d"), m_nTime);
	m_editRow.SetWindowTextW(row);
	m_editCol.SetWindowTextW(col);
	m_editElem.SetWindowTextW(elem);
	m_editTime.SetWindowTextW(time);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetDialog::OnEnChangeEditRow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString row;
	m_editRow.GetWindowText(row);
	m_nRow = _ttoi(row);
}


void CSetDialog::OnEnChangeEditCol()
{
	CString col;
	m_editCol.GetWindowText(col);
	m_nCol = _ttoi(col);
}


void CSetDialog::OnEnChangeEditElem()
{
	CString elem;
	m_editElem.GetWindowText(elem);
	m_nElem = _ttoi(elem);
}


void CSetDialog::OnEnChangeEditTime()
{
	CString time;
	m_editTime.GetWindowText(time);
	m_nTime = _ttoi(time);
}

void CSetDialog::InitBackground()
{
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\bk3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
}

void CSetDialog::UpdateWindow()
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

void CSetDialog::CheckData()
{
	if (m_nRow == 0) {
		MessageBoxW(_T("行数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	else if (m_nRow < 0 || m_nRow>10) {
		MessageBoxW(_T("不匹配，请重新行数（0-10）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	if (m_nCol == 0) {
		MessageBoxW(_T("列数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	else if (m_nCol <= 0 || m_nCol > 14) {
		MessageBoxW(_T("不匹配，请重新输入列数（0-14）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	if (m_nElem == 0) {
		MessageBoxW(_T("元素数输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	else if (m_nElem < 0 || m_nElem>16) {
		MessageBoxW(_T("不匹配，请重新输入元素数（0-16）！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	if (m_nTime == 0) {
		MessageBoxW(_T("时间输入有误！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	else if (m_nTime < 0) {
		MessageBoxW(_T("请重新输入时间！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	Rows = m_nRow;
	Cols = m_nCol;
	Elem = m_nElem;
	Time = m_nTime;
}


void CSetDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, 600, 300, &m_dcMem, 0, 0, SRCCOPY);
}


void CSetDialog::OnBnClickedOk()
{
	CheckData();
	CDialogEx::OnOK();
}


void CSetDialog::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CSetDialog::SetData(int data[4])
{
	m_nRow = data[0];
	m_nCol = data[1];
	m_nElem = data[2];
	m_nTime = data[3];
}

int* CSetDialog::GetData()
{
	int data[4];
	CString row;
	CString col;
	CString elem;
	CString time;
	m_editRow.GetWindowText(row);
	m_editCol.GetWindowText(col);
	m_editElem.GetWindowText(elem);
	m_editTime.GetWindowText(time);
	m_nRow = _ttoi(row);
	m_nCol = _ttoi(col);
	m_nElem = _ttoi(elem);
	m_nTime = _ttoi(time);
	data[0] = m_nRow;
	data[1] = m_nCol;
	data[2] = m_nElem;
	data[3] = m_nTime;
	return data;
}
