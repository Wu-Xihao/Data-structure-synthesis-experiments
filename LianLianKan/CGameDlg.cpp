// CGameDlg.cpp: 实现文件
#pragma once
#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CGameControl.h"
#include "CWinDlg.h"
#include "CFailDlg.h"
#include "CHelpDialog.h"
#include "CGameException.h"
#include "CSetDialog.h"
#include <windows.h>
#include <string>

extern int Rows;
extern int Cols;
extern int Elem;
extern int Time;
extern int Score;
extern std::string PATH;

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*= nullptr*/,int flag/*=0*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	sign = flag;
	switch (flag) {
	case 1:
		SetBasicGame();
		break;
	case 2:
		SetRelaxGame();
		break;
	case 3:
		SetLevelGame();
		break;
	default:
		break;
	}
	//加载图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitData();
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CGameDlg::OnBnClickedBtnBegin)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_TIP, &CGameDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_PUASE, &CGameDlg::OnBnClickedBtnPuase)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_SET, &CGameDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//绘制图标
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//设置对话框标题——基本模式
	CString Title(this->title.c_str());
	SetWindowText(Title);
	//初始化背景图片
	InitBackground();
	//调整游戏窗口大小
	UpdateWindow();
	//初始化元素图片
	InitElement();
	//初始化暂停图片
	InitSleepPicture();
	//初始化游戏时间
	CString time;
	time.Format(_T("%d"), Time);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(time);
	//设置提示按钮、重排按钮、暂停按钮为禁用
	CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
	pButtonTip->EnableWindow(FALSE);
	CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
	pButtonReset->EnableWindow(FALSE);
	CButton* pButtonPause = (CButton*)GetDlgItem(IDC_BTN_PUASE);
	pButtonPause->EnableWindow(FALSE);
	if (sign == 3) {
		CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_SET);
		pButton->EnableWindow(FALSE);
	}
	return TRUE;
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); 
	dc.BitBlt(0, 0, GAMEDLGWIDTH, GAMEDLGHEIGHT, &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}

void CGameDlg::OnBnClickedBtnBegin()
{
	//初始化游戏地图
	try {
		m_GameControl.StartGame();
	}
	catch (CGameException e) {
		CString text(e.what());
		MessageBoxW(_T("请重新进行设置或重试！"), _T("错误信息"), MB_ICONEXCLAMATION);
		return;
	}
	//重置元素个数
	m_GameControl.m_nElemNum = Rows * Cols;
	//更新界面
	UpdateMap();
	Invalidate(FALSE);
	//游戏进行标识
	m_bPlaying = true;
	//设置按钮为禁用
	CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_BEGIN);
	pButton->EnableWindow(FALSE);
	//设置提示按钮、重排按钮、暂停按钮为启用
	if (sign != 3) {
		CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
		pButtonTip->EnableWindow(TRUE);
		CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
		pButtonReset->EnableWindow(TRUE);
	}
	CButton* pButtonPause = (CButton*)GetDlgItem(IDC_BTN_PUASE);
	pButtonPause->EnableWindow(TRUE);
	//初始化进度条
	m_GameProgress.SetRange(0, Time);//范围
	m_GameProgress.SetStep(-1);//步长
	m_GameProgress.SetPos(Time);//开始位置
	//初始化时间
	m_nTime = Time;
	CString time;
	time.Format(_T("%d"), m_nTime);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(time);
	//启动定时器
	this->SetTimer(ID_PLAY_GAME, 1000, NULL);
}

void CGameDlg::InitBackground()
{
	//初始化内存CD
	CString path(BGPath.c_str());
	HANDLE bmp = ::LoadImageW(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
	//初始化背景CD
	HANDLE bk = ::LoadImageW(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dcBG(this);
	m_dcBG.CreateCompatibleDC(&dcBG);
	m_dcBG.SelectObject(bk);
}

void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\ele_pict.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);
}

void CGameDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

void CGameDlg::InitData()
{
	//初始化起始点坐标
	m_ptGameTop.x = CENTERX - ELEMSIZE * Cols / 2;
	m_ptGameTop.y = CENTERY - ELEMSIZE * Rows / 2;
	//初始化元素图片大小
	m_sizeElem.cx = ELEMSIZE;
	m_sizeElem.cy = ELEMSIZE;
	//初始化游戏区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * Cols;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * Rows;
	//初始化布尔值
	m_bFirstPoint = true;
	m_bPlaying = false;
	m_bStartGame = false;
	m_bPause = false;
}

void CGameDlg::UpdateMap()
{
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	//重新绘制游戏区域的背景图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//重新绘制元素图片
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Cols; j++) {
			int nInfo = m_GameControl.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCCOPY);
		}
	}
}

void CGameDlg::InitSleepPicture()
{
	HANDLE sleepPic = ::LoadImageW(NULL, _T("theme\\picture\\sleep.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dcSleep(this);
	m_dcPause.CreateCompatibleDC(&dcSleep);
	m_dcPause.SelectObject(sleepPic);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//如果元素为空，则无效
	if (m_GameControl.m_nElemNum == 0) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//如果在左边空区域和上边空区域内无效
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol= (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	//如果在右边空区域和下边空区域内无效
	if (nRow >= Rows || nCol >= Cols) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//判断选中元素为第一个还是第二个
	if (m_bFirstPoint) {
		//为选中元素绘制矩形框
		DrawTipFrame(nRow, nCol);
		m_GameControl.SetFirstPoint(nRow, nCol);
		m_bFirstPoint = false;
	}
	else {
		//为选中元素绘制矩形框
		DrawTipFrame(nRow, nCol);
		m_GameControl.SetSecPoint(nRow, nCol);
		//判断是否是相同图片
		if (m_GameControl.Link()) {
			//绘制连接线
			DrawTipLine();
			//清除
			m_GameControl.m_GameLogic.Clear(m_GameControl.m_pGameMap, m_GameControl.m_ptSelFirst, m_GameControl.m_ptSelSec);
			m_GameControl.m_nElemNum -= 2;
			//更新游戏地图
			UpdateMap();
		}
		Sleep(200);
		//声明游戏地图无效（使该区域重绘）
		InvalidateRect(m_rtGameRect, FALSE);
		m_bFirstPoint = !m_bFirstPoint;
	}
	//判断游戏是否获胜
	if (m_GameControl.IsWin()) {
		m_bPlaying = false;
		m_bPause = false;
		bWin = true;
		//终止时间
		KillTimer(ID_PLAY_GAME);
		//弹出胜利窗口
		CWinDlg winDlg;
		winDlg.DoModal();
		//设置开始游戏按钮为启用
		CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_BEGIN);
		pButton->EnableWindow(TRUE);
		//设置提示按钮、重排按钮、暂停按钮为禁用
		if (sign != 3) {
			CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
			pButtonTip->EnableWindow(FALSE);
			CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
			pButtonReset->EnableWindow(FALSE);
		}
		CButton* pButtonPause = (CButton*)GetDlgItem(IDC_BTN_PUASE);
		pButtonPause->EnableWindow(FALSE);
		if (sign == 3) {
			LevelSet();
		}
		//分数
		Score += 10;
	}}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	//设定颜色为红色
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	//确定矩形框边界
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	//绘制矩形框
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine()
{
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 225, 0));
	//将画笔选入DC 
	CPen* pOldPen = dc.SelectObject(&penLine);
	//根据路径绘制连接线
	for (int i = 0; i < m_GameControl.m_nVexNum - 1; i++) {
		Vertex fromVertex = m_GameControl.m_pAvPath[i];
		Vertex toVertex = m_GameControl.m_pAvPath[i + 1];
		dc.MoveTo(m_ptGameTop.x + fromVertex.col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + fromVertex.row * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + toVertex.col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + toVertex.row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}


void CGameDlg::OnBnClickedBtnTip()
{
	//获取相连通的两个点以及路径
	bool flag = m_GameControl.GiveTip();
	m_GameControl.m_nVexNum=m_GameControl.m_GameLogic.GetVexPath(m_GameControl.m_pAvPath);
	int vexNum = m_GameControl.m_nVexNum;
	Vertex* pVexPath = m_GameControl.m_pAvPath;
	//绘制两个元素边框
	DrawTipFrame(pVexPath[0].row, pVexPath[0].col);
	DrawTipFrame(pVexPath[vexNum-1].row, pVexPath[vexNum-1].col);
	//绘制连接线
	DrawTipLine();
}


void CGameDlg::OnBnClickedBtnReset()
{
	//调用CGameControl中的重排函数，重排游戏地图数组
	m_GameControl.ReSet();
	//更新游戏地图
	UpdateMap();
	//声明游戏地图无效（使该区域重绘）
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnBnClickedBtnPuase()
{
	if (!m_bPause) {
		//暂停时间
		KillTimer(ID_PLAY_GAME);
		//更换按钮文本
		GetDlgItem(IDC_BTN_PUASE)->SetWindowTextW(L"继续游戏");
		m_bPause = true;
		//将游戏区域覆盖
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
			&m_dcPause, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		//设置提示、重排为禁用
		if (sign != 3) {
			CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
			pButtonTip->EnableWindow(FALSE);
			CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
			pButtonReset->EnableWindow(FALSE);
		}
	}
	else {
		//继续计时
		SetTimer(ID_PLAY_GAME, 1000, NULL);
		//更换按钮文本
		GetDlgItem(IDC_BTN_PUASE)->SetWindowTextW(L"暂停游戏");
		m_bPause = false;
		//恢复游戏区域
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
		//设置提示、重排为启用
		if (sign != 3) {
			CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
			pButtonTip->EnableWindow(TRUE);
			CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
			pButtonReset->EnableWindow(TRUE);
		}
	}
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == ID_PLAY_GAME && m_bPlaying) {
		m_GameProgress.StepIt();
		DrawGameTime();
		if (m_nTime == 0) {
			//终止时间
			KillTimer(ID_PLAY_GAME);
			//弹出失败窗口
			if (!m_GameControl.IsWin()) {
				bWin = false;
				CFailDlg failDlg;
				failDlg.DoModal();
				//设置开始游戏按钮为启用
				CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_BEGIN);
				pButton->EnableWindow(TRUE);
				//设置提示按钮、重排按钮、暂停按钮为禁用
				if (sign != 3) {
					CButton* pButtonTip = (CButton*)GetDlgItem(IDC_BTN_TIP);
					pButtonTip->EnableWindow(FALSE);
					CButton* pButtonReset = (CButton*)GetDlgItem(IDC_BTN_RESET);
					pButtonReset->EnableWindow(FALSE);
				}
				CButton* pButtonPause = (CButton*)GetDlgItem(IDC_BTN_PUASE);
				pButtonPause->EnableWindow(FALSE);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime()
{
	CString time;
	time.Format(_T("%d"), --m_nTime);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(time);
}


void CGameDlg::OnBnClickedBtnHelp()
{
	CHelpDialog helpDlg;
	helpDlg.DoModal();
}

void CGameDlg::SetBasicGame()
{
	//设置背景图片路径
	if (PATH.empty()) {
		BGPath = "theme\\picture\\bk1.bmp";
	}
	else {
		BGPath = PATH;
	}
	//设置标题
	title = "连连看——基本模式";
	//设置初始行列与初始时间
	/*Rows = ROWS;
	Cols = COLS;
	Elem = ELEMNUM;
	Time = GAMETIME;*/
}

void CGameDlg::SetRelaxGame()
{
	//设置背景图片路径
	if (PATH.empty()) {
		BGPath = "theme\\picture\\bk2.bmp";
	}
	else {
		BGPath = PATH;
	}
	//设置标题
	title = "连连看——休闲模式";
	//设置初始行列与初始时间
	/*Rows = ROWS;
	Cols = COLS;
	Elem = ELEMNUM;
	Time = GAMETIME;*/
}

void CGameDlg::SetLevelGame()
{
	//设置背景图片路径
	if (PATH.empty()) {
		BGPath = "theme\\picture\\bk4.bmp";
	}
	else {
		BGPath = PATH;
	}
	//设置标题
	title = "连连看——关卡模式";
	//设置初始行列与初始时间
	Rows = 4;
	Cols = 4;
	Elem = 4;
	Time = 60;
	bWin = false;
	level = 1;
}

void CGameDlg::LevelSet()
{
	if (bWin||level==0) {
		level++;
		level %= 6;
		Rows += 2;
		Cols += 2;
		Elem += 2;
		Time += 40;
		if (level == 5) {
			Cols += 2;
			Elem += 2;
		}
	}
	InitData();
}

void CGameDlg::OnBnClickedBtnSet()
{
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	InvalidateRect(m_rtGameRect, FALSE);
	//OnBnClickedBtnPuase();
	CSetDialog setDlg;
	setDlg.DoModal();
	InitData();
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	Invalidate(FALSE);
	CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_BEGIN);
	pButton->EnableWindow(TRUE);
}
