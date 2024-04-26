//定义图的相关结构，实现图的相关操作
#include"Header.h"
#define FILEV "Vex.txt"
#define FILEE "Edge.txt"
using namespace std;

//构造函数
CGraph::CGraph() 
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			aAdjMatrix[i][j] = 0;
		}
	}
	nVexNum = 0;
	nEdgeNum = 0;
	pathList = new Path();
	pathList->next = NULL; 
}

//初始化图结构
void CGraph::Init()
{
	//读取顶点信息文件
	ifstream inVex(FILEV);
	string s;
	getline(inVex, s);
	int num = atoi(s.c_str());
	nVexNum = num;
	for (int i = 0; i < num; i++) {
		getline(inVex, s);
		aVexs[i].num = atoi(s.c_str());
		getline(inVex, s);
		aVexs[i].name = s;
		getline(inVex, s);
		aVexs[i].introduce = s;
		s.clear();
	}
	inVex.close();
	//读取边信息文件
	ifstream inEdge(FILEE);
	stringstream ss;
	int index = 0;
	while (getline(inEdge, s)) {
		ss << s;
		ss >> aEdges[index].vex1 >> aEdges[index].vex2 >> aEdges[index].weight;
		aAdjMatrix[aEdges[index].vex1][aEdges[index].vex2] = aEdges[index].weight;
		aAdjMatrix[aEdges[index].vex2][aEdges[index].vex1] = aEdges[index].weight;
		aVexs[aEdges[index].vex1].nexts.insert(aEdges[index].vex2);
		aVexs[aEdges[index].vex2].nexts.insert(aEdges[index].vex1);
		index++;
		ss.clear();
		s.clear();
	}
	nEdgeNum = index;
}

//将顶点添加到顶点数组中
int CGraph::InsertVex(Vex sVex)
{
	return 0;
}

//将边保存到邻接矩阵中
int CGraph::InsertEdge(Edge s)
{
	return 0;
}

//查询指定顶点信息
Vex CGraph::GetVex(int nVex)
{
	return aVexs[nVex];
}

//查询指定边信息
Edge CGraph::GetEdge(int nEdge)
{
	return aEdges[nEdge];
}

//查询与指定顶点相连的边
vector<Edge> CGraph::FindEdge(int nVex)
{
	vector<Edge> aEdge;
	for (int i = 0; i < nVexNum; i++) {
		if (aAdjMatrix[nVex][i] != 0) {
			Edge e;
			e.vex1 = nVex;
			e.vex2 = i;
			e.weight = aAdjMatrix[nVex][i];
			aEdge.push_back(e);
		}
	}
	return aEdge;
}

//获得当前顶点数
int CGraph::GetVexNum()
{
	return nVexNum;
}

//获得当前边数
int CGraph::GetEdgeNum()
{
	return nEdgeNum;
}

//获得遍历结果
void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	set<int> nexts[20];
	for (int i = 0; i < nEdgeNum; i++){
		int v1 = aEdges[i].vex1;
		int v2 = aEdges[i].vex2;
		nexts[v1].insert(v2);
		nexts[v2].insert(v1);
	}
	bool visited[20] = { false };
	visited[nVex] = true;
	int nIndex = 1;
	DFS(nVex, visited, nIndex, nexts, pList);
}

//搜索两点间的最短路径
int CGraph::FindShortPath(int nVexStart, int nVexEnd,vector<int>& aPath)
{
	int visited[20] = { 0 };
	visited[nVexStart] = 1;
	int path[20];
	int preIndex[20];
	int visitedEdge[20];
	for (int i = 0; i < 20; i++) {
		path[i] = -1;
		preIndex[i] = -1;
	}
	//遍历边，初始化路径距离与边的访问信息
	for (int i = 0; i < nEdgeNum; i++) {
		if (aEdges[i].vex1 == nVexStart) {
			path[aEdges[i].vex2] = aEdges[i].weight;
			preIndex[aEdges[i].vex2] = nVexStart;
			visitedEdge[i] = 1;
		}else if (aEdges[i].vex2 == nVexStart) {
			path[aEdges[i].vex1] = aEdges[i].weight;
			preIndex[aEdges[i].vex1] = nVexStart;
			visitedEdge[i] = 1;
		}
		else {
			visitedEdge[i] = 0;
		}
	}
	for (int i = 0; i < nVexNum-1; i++) {
		//查找未访问的最近的点的下标
		int minIndex = FindMinIndex(path, visited);
		visited[minIndex] = 1;
		//以找到的点为中间媒介更新其它点的距离
		for (int j = 0; j < nEdgeNum; j++) {
			//如果边已经读取过，则直接跳过
			if (visitedEdge[j] != 0) {
				continue;
			}
			//若边中的一个顶点为minIndex，更新路径信息
			if (aEdges[j].vex1 == minIndex) {
				//还未存取路径的情况
				if (path[aEdges[j].vex2] == -1) {
					path[aEdges[j].vex2] = path[aEdges[j].vex1] + aEdges[j].weight;
					preIndex[aEdges[j].vex2] = aEdges[j].vex1;
				}
				//更新后路径更短的情况
				else if (path[aEdges[j].vex2] > path[aEdges[j].vex1] + aEdges[j].weight) {
					path[aEdges[j].vex2] = path[aEdges[j].vex1] + aEdges[j].weight;
					preIndex[aEdges[j].vex2] = aEdges[j].vex1;
				}
				visitedEdge[j] = 1;
			}else if (aEdges[j].vex2 == minIndex) {
				if (path[aEdges[j].vex1] == -1) {
					path[aEdges[j].vex1] = path[aEdges[j].vex2] + aEdges[j].weight;
					preIndex[aEdges[j].vex1] = aEdges[j].vex2;
				}
				else if (path[aEdges[j].vex1] > path[aEdges[j].vex2] + aEdges[j].weight) {
					path[aEdges[j].vex1] = path[aEdges[j].vex2] + aEdges[j].weight;
					preIndex[aEdges[j].vex1] = aEdges[j].vex2;
				}
				visitedEdge[j] = 1;
			}
		}
	}
	//将路径下标添加到vector中
	int index = nVexEnd;
	while (index!=nVexStart) {
		index = preIndex[index];
		aPath.insert(aPath.begin(), index);
	}
	return path[nVexEnd];
}
int CGraph::FindMinIndex(int path[], int visited[]) {
	int min = INT32_MAX;
	int minIndex = -1;
	for (int i = 0; i < nVexNum; i++) {
		if (visited[i] == 0 && path[i] < min && path[i]!=-1) {
			min = path[i];
			minIndex = i;
		}
	}
	return minIndex;
}

//构造最小生成树（Prim算法）
int CGraph::FindMinTree(vector<Edge>& aPath)
{
	set<int> set;
	set.insert(0);
	int visitedEdge[20] = { 0 };
	int allWeight = 0;
	while (set.size() != nVexNum) {
		int minWeight = INT32_MAX;
		int minIndex = -1;
		//找到不构成闭环的最小边
		for (int i = 0; i < nEdgeNum; i++) {
			if (visitedEdge[i] == 1) {
				continue;
			}
			int v1 = aEdges[i].vex1;
			int v2 = aEdges[i].vex2;
			if ((set.count(v1) != 0 && set.count(v2) == 0)|| (set.count(v2) != 0 && set.count(v1) == 0)) {
				if (aEdges[i].weight < minWeight) {
					minWeight = aEdges[i].weight;
					minIndex = i;
				}
			}
		}
		//在aPath中添加找到的不构成闭环的最小边
		aPath.push_back(aEdges[minIndex]);
		allWeight += aEdges[minIndex].weight;
		visitedEdge[minIndex] = 1;
		//向set集合中添加新增的点
		if (set.count(aEdges[minIndex].vex1) == 0) {
			set.insert(aEdges[minIndex].vex1);
		}
		else {
			set.insert(aEdges[minIndex].vex2);
		}
	}
	return allWeight;
}

//寻找距离最短且未访问过的点
int CGraph::GetMinVex(int nVex, set<int>& set) {
	int min = INT32_MAX;
	int index=-1;
	for (int i = 0; i < nEdgeNum; i++) {
		if (aEdges[i].vex1 == nVex && set.count(aEdges[i].vex2)==0) {
			if (min > aEdges[i].weight) {
				min = aEdges[i].weight;
				index = aEdges[i].vex2;
			}
		}else if (aEdges[i].vex2 == nVex && set.count(aEdges[i].vex1) == 0) {
			if (min > aEdges[i].weight) {
				min = aEdges[i].weight;
				index = aEdges[i].vex1;
			}
		}
	}
	return index;
}

//深度优先搜索遍历图结构
void CGraph::DFS(int nVex, bool aVisited[], int& nIndex, set<int> nexts[], PathList& pList)
{
	if (pList == NULL) {
		return;
	}
	if (nIndex == nVexNum) {
		//将新路径加入链表
		pList->next = pathList->next;
		pathList->next = pList;
		return;
	}
	set<int> set;
	vector<int> vec;
	for (auto it : nexts[nVex]) {
		if (!aVisited[it]) {
			vec.push_back(it);
		}
	}
	//将aVisited、nIndex复制保留
	bool visited[20] = { false };
	for (int i = 0; i < 20; i++) {
		visited[i] = aVisited[i];
	}
	int deep = nIndex;
	PathList q = pList;
	PathList p = NULL;
	bool sign = false;
	for (int i = 0; i < vec.size(); i++) {
		if (!sign) {
			bool flag = false;
			for (auto it : nexts[nVex]) {
				if (aVisited[it]) {
					continue;
				}
				pList->vexs[nIndex] = it;
				aVisited[it] = true;
				nIndex++;
				DFS(it, aVisited, nIndex, nexts, pList);
				if (nIndex != nVexNum) {
					if (pList != NULL) {
						delete pList;
						pList = NULL;
					}
					return;
				}
				if (!flag) {
					set.insert(it);
					flag = true;
				}
			}
			sign = true;
		}
		else {
			p = new Path();
			//复制前面已经得到的路径
			for (int j = 0; j < deep; j++) {
				p->vexs[j] = pList->vexs[j];
			}
			//复制aVisited、nIndex；
			bool visit[20] = { false };
			for (int j = 0; j < 20; j++) {
				visit[j] = visited[j];
			}
			int index = deep;
			//递归构建新路径
			bool flag = false;
			for (auto it : nexts[nVex]) {
				if (set.count(it) == 1 || visit[it]) {
					continue;
				}
				p->vexs[index] = it;
				visit[it] = true;
				index++;
				DFS(it, visit, index, nexts, p);
				if (index != nVexNum) {
					if (p != NULL) {
						delete p;
						p = NULL;
					}
					return;
				}
				if (!flag) {
					set.insert(it);
					flag = true;
				}
			}
			/*for (auto it : set) {
				if (visit[it]) {
					continue;
				}
				p->vexs[index] = it;
				visit[it] = true;
				index++;
				DFS(it, visit, index, nexts, p);
			}*/
		}
	}
}

PathList CGraph::GetPath() {
	return pathList;
}

