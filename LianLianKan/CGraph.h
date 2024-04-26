#pragma once

#define MAX_VERTEX_NUM 16
typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

class CGraph
{
public:
	CGraph();
	~CGraph();
protected:
	Vertices m_Vertices;	//顶点数组
	AdjMatrix m_AdjMatrix;	//关系矩阵
	int m_nVexNum;			//顶点数量
	int m_nArcNum;			//边的数量
public:
	void InitGraph();						//初始化图的顶点和关系
	int AddVertex(int info);				//将顶点info添加到顶点数组
	int GetVertex(int nIndex);				//获取顶点数组中索引为nIndex的顶点
	void AddArc(int nV1Index, int nV2Index);//添加关系矩阵中nV1Index和nV2Index的关系
	int GetVexNum();						//获取顶点数组中的顶点数
};

