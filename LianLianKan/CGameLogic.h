#pragma once
#include "global.h"

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
public:
	Vertex m_avPath[4];
	int m_nVertexNum;
	int** InitMap();									//初始化游戏地图
	void ReleaseMap(int**& pGameMap);					//释放地图
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);	//判断是否相连
	void Clear(int** pGameMap, Vertex v1, Vertex v2);	//清除
	int GetVexPath(Vertex* avPath);
	bool SearchValidPath(int** pGameMap);
	void ReSetMap(int**& pGameMap);
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);			//判断横向是否连通
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);			//判断纵向是否连通
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);		//一个拐点连通判断
	bool LinkX(int** pGameMap, int nRow, int nCol1, int nCol2);		//直线连通X轴
	bool LinkY(int** pGameMap, int nCol, int nRow1, int nRow2);		//直线连通Y轴
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);		//两个拐点连通判断
	bool LinkMiddle(int** pGameMap, Vertex v1, Vertex v2);			//判断内部是否连通
	bool LinkOut(int** pGameMap, Vertex v1, Vertex v2);				//判断外围是否连通
	bool LinkYXY(int** pGameMap, Vertex v1, Vertex v2, int nRow);	//Y轴X轴Y轴连通情况
	bool LinkXYX(int** pGameMap, Vertex v1, Vertex v2, int nCol);	//X轴Y轴X轴连通情况
	void AddVertex(Vertex v);										//将元素添加到路径数组
	void DeleteVertex();
};

