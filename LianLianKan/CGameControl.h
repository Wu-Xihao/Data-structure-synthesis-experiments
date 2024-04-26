#pragma once
#include "CGameLogic.h"
#include "global.h"
#include "CGraph.h"


class CGameControl
{
public:
	//构造函数与析构函数
	CGameControl();
	~CGameControl();
public:
	//静态成员变量
	static int s_nRows;		//游戏行数
	static int s_nCols;		//游戏列数
	static int s_nPicNum;	//图片数
	//数据成员
	//CGraph m_garph;
	int** m_pGameMap;		//游戏地图数组指针
	CGameLogic m_GameLogic;	//游戏逻辑操作对象
	Vertex m_ptSelFirst;	//选中的第一个元素
	Vertex m_ptSelSec;		//选中的第二个元素
	Vertex* m_pAvPath;		//相连路径
	int m_nVexNum;			//相连路径中元素个数
	int m_nElemNum;			//元素剩余总数
	//成员函数
	void StartGame();						//开始游戏
	int GetElement(int nRow, int nCol);		//得到某一个元素
	void SetFirstPoint(int nRow, int nCol);	//设置第一个元素
	void SetSecPoint(int nRow, int nCol);	//设置第二个元素
	bool Link();							//判断是否相连并得到路径
	bool GiveTip();							//提示操作获得一对连通图片和路径
	bool IsWin();							//判断游戏是否胜利
	void ReSet();							//重排游戏地图
};

