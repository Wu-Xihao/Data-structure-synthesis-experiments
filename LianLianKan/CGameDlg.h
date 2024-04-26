#pragma once
#include "afxdialogex.h"
#include "CGameControl.h"
#include "global.h"
#include <string>

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr,int flag = 0);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//成员变量
	std::string title;		//标题
	std::string BGPath;		//背景图片路径
	int level;				//挑战模式等级
	bool bWin;				//游戏成功
	int sign;				//模式标志

	HICON m_hIcon;				//图标
	CDC m_dcMem;				//内存CD
	CDC m_dcBG;					//背景CD
	CDC m_dcElement;			//元素CD
	CDC m_dcCache;				//缓存CD
	CDC m_dcPause;				//暂停图片CD
	//CDC m_dcMask;				//掩码CD
	CPoint m_ptGameTop;			//游戏区起始点
	CSize m_sizeElem;			//元素图片大小
	CRect m_rtGameRect;			//游戏区域大小
	CGameControl m_GameControl;	//游戏控制类
	CProgressCtrl m_GameProgress;//进度条变量
	//成员函数
	virtual BOOL OnInitDialog();		//窗口初始化函数
	afx_msg void OnPaint();				//WM_PAINT消息函数
	afx_msg void OnBnClickedBtnBegin();	//开始按钮
	void InitData();					//初始化数据
	void InitBackground();				//初始化窗口背景
	void InitElement();					//初始化元素图片与DC
	void UpdateWindow();				//更新界面
	void UpdateMap();					//更新游戏地图
	void InitSleepPicture();			//初始化暂停时的覆盖图片
protected:
	bool m_bFirstPoint;		//图片是否第一次选中
	bool m_bPlaying;		//游戏是否正在进行
	bool m_bStartGame;		//是否已经点击开始游戏
	bool m_bPause;			//游戏是否暂停，true为已暂停
	int m_nTime;			//游戏时间
	void DrawGameTime();	//绘制游戏时间
public:
	void DrawTipFrame(int nRow, int nCol);					//根据选择的图片的行号和列号，绘制矩形提示框
	void DrawTipLine();										//绘制连接线
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	//鼠标点击WM_LBUTTONUP消息响应函数				
	afx_msg void OnBnClickedBtnTip();						//点击提示按钮响应事件
	afx_msg void OnBnClickedBtnReset();						//点击重排按钮响应事件
	afx_msg void OnBnClickedBtnPuase();						//点击暂停按钮响应事件
	afx_msg void OnTimer(UINT_PTR nIDEvent);				//WM_TIMER消息响应事件，进行游戏计时
	afx_msg void OnBnClickedBtnHelp();						//点击帮助按钮响应事件
	afx_msg void OnBnClickedBtnSet();						//点击设置按钮响应事件
	void SetBasicGame();				//基础模式设置
	void SetRelaxGame();				//休闲模式设置
	void SetLevelGame();				//挑战模式设置
	void LevelSet();					//挑战模式关卡设置
};
