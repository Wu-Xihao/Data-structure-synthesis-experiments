#pragma once
#include"Header.h"
using namespace std;

//����ṹ�壨����һ���������Ϣ��
struct Vex {
	int num;//���
	string name;//��������
	string introduce;//�������
	set<int> nexts;//���ھ��㼯��
};
struct Edge {
	int vex1;//����1
	int vex2;//����2
	int weight;//Ȩֵ
};
typedef struct Path {
	int vexs[20];//����һ��·��
	Path* next;//��һ��·��
}*PathList;

class CGraph {
public:
	CGraph();//���캯��
	void Init();//��ʼ��ͼ�ṹ
	int InsertVex(Vex sVex);//��������ӵ�����������
	int InsertEdge(Edge s);//���߱��浽�ڽӾ�����
	Vex GetVex(int nVex);//��ѯָ��������Ϣ
	Edge GetEdge(int nEdge);//��ѯָ������Ϣ
	vector<Edge> FindEdge(int nVex);//��ѯ��ָ�����������ı�
	int GetVexNum();//��õ�ǰ������
	int GetEdgeNum();//��õ�ǰ����
	void DFSTraverse(int nVex, PathList& pList);//��ñ������
	int FindShortPath(int nVexStart, int nVexEnd, vector<int>& aPath);//�������������·��
	int FindMinIndex(int path[], int visited[]);
	int FindMinTree(vector<Edge>& aPath);//������С������
	int GetMinVex(int nVex,set<int>& set);//Ѱ�Ҿ��������δ���ʹ��ĵ�
	PathList GetPath();
protected:
	void DFS(int nVex, bool aVisited[], int& nIndex, set<int> nexts[], PathList& pList);//���������������ͼ

private:
	int aAdjMatrix[20][20];//�ڽӾ���
	Vex aVexs[20];//��������
	Edge aEdges[20];//������
	int nVexNum;//�������
	int nEdgeNum;//�߸���
	PathList pathList;
};
