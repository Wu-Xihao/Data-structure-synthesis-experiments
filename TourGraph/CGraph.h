#pragma once
#include"Header.h"
using namespace std;

//顶点结构体（包含一个景点的信息）
struct Vex {
	int num;//编号
	string name;//景点名称
	string introduce;//景点介绍
	set<int> nexts;//相邻景点集合
};
struct Edge {
	int vex1;//顶点1
	int vex2;//顶点2
	int weight;//权值
};
typedef struct Path {
	int vexs[20];//保存一条路径
	Path* next;//下一条路径
}*PathList;

class CGraph {
public:
	CGraph();//构造函数
	void Init();//初始化图结构
	int InsertVex(Vex sVex);//将顶点添加到顶点数组中
	int InsertEdge(Edge s);//将边保存到邻接矩阵中
	Vex GetVex(int nVex);//查询指定顶点信息
	Edge GetEdge(int nEdge);//查询指定边信息
	vector<Edge> FindEdge(int nVex);//查询与指定顶点相连的边
	int GetVexNum();//获得当前顶点数
	int GetEdgeNum();//获得当前边数
	void DFSTraverse(int nVex, PathList& pList);//获得遍历结果
	int FindShortPath(int nVexStart, int nVexEnd, vector<int>& aPath);//搜索两点间的最短路径
	int FindMinIndex(int path[], int visited[]);
	int FindMinTree(vector<Edge>& aPath);//构造最小生成树
	int GetMinVex(int nVex,set<int>& set);//寻找距离最短且未访问过的点
	PathList GetPath();
protected:
	void DFS(int nVex, bool aVisited[], int& nIndex, set<int> nexts[], PathList& pList);//深度优先搜索遍历图

private:
	int aAdjMatrix[20][20];//邻接矩阵
	Vex aVexs[20];//顶点数组
	Edge aEdges[20];//边数组
	int nVexNum;//顶点个数
	int nEdgeNum;//边个数
	PathList pathList;
};
