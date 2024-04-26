//实现景区信息管理系统的相关功能
#include"Header.h"
using namespace std;

//构造函数
cTourism::cTourism()
{
	graph.Init();
}

//读取文件，创建景区景点图
void cTourism::CreateGraph()
{
	cout << "===== 创建景点景区图 =====" << endl;
	cout << "顶点数：" << graph.GetVexNum() << endl;
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	cout << "----- 边 -----" << endl;
	for (int i = 0; i < graph.GetEdgeNum(); i++) {
		Edge e = graph.GetEdge(i);
		cout << "<v" << e.vex1 << ",v" << e.vex2 << "> " << e.weight << endl;
	}
}

//查询指定景点信息，显示到相邻景点的距离
void cTourism::GetSpotInfo()
{
	cout << "===== 查询景点信息 =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int num;
	cout << "请输入想要查询的景点编号：";
	do {
		cin >> num;
		if (num < 0 || num >= graph.GetVexNum()) {
			cerr << "编号错误！" << endl;
			cout << "请重新输入：";
		}
		else {
			break;
		}
	} while (true);
	Vex v = graph.GetVex(num);
	cout << v.name << endl;
	cout << v.introduce << endl;
	cout << "----- 周边景区 -----" << endl;
	vector<Edge> aEdge = graph.FindEdge(num);
	for (auto it:aEdge) {
		cout << graph.GetVex(it.vex1).name << "->" << graph.GetVex(it.vex2).name << " " << it.weight << "m" << endl;
	}
}

//查询旅游景点导航路线
void cTourism::TravelPath()
{
	cout << "===== 旅游景点导航 =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int n;
	cout << "请输入起点的编号：";
	do {
		cin >> n;
		if (n < 0 || n >= graph.GetVexNum()) {
			cerr << "输入编号错误！" << endl;
			cout << "请重新输入：";
		}
		else {
			break;
		}
	} while (true);
	PathList pList = new Path();
	pList->next = NULL;
	pList->vexs[0] = n;
	graph.DFSTraverse(n, pList);
	PathList p = graph.GetPath()->next;
	int num = 1;
	while (p != NULL) {
		cout << "路线" << num << "：";
		cout << graph.GetVex(n).name;
		for (int i = 1; i < graph.GetVexNum(); i++) {
			cout << "->";
			cout << graph.GetVex(p->vexs[i]).name;
		}
		cout << endl;
		p = p->next;
		num++;
	}
}

//搜索两个景点间的最短路径
void cTourism::FindShortPath()
{
	cout << "===== 搜索最短路径 =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int n1, n2;
	cout << "请输入起点的编号：";
	do {
		cin >> n1;
		if (n1 < 0 || n1 >= graph.GetVexNum()) {
			cerr << "输入编号错误！" << endl;
			cout << "请重新输入：";
		}
		else {
			break;
		}
	} while (true);
	cout << "请输入终点编号：";
	do {
		cin >> n2;
		if (n2 < 0 || n2 >= graph.GetVexNum()) {
			cerr << "输入编号错误！" << endl;
			cout << "请重新输入：";
		}
		else {
			break;
		}
	} while (true);
	vector<int> aPath;
	//aPath第一个元素为最短路径长度，后面元素依次为路径的顶点索引
	int pathLength = graph.FindShortPath(n1, n2, aPath);
	//输出路径和距离
	for (auto it : aPath) {
		cout << graph.GetVex(it).name;
		cout << "->";
	}
	cout << graph.GetVex(n2).name << endl;
	cout << "路径长度：" << pathLength << "m" << endl;
}

//查询铺设电路规划图
void cTourism::DesignPath()
{
	cout << "===== 铺设电路规划 =====" << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	vector<Edge> aPath;
	int allWeight = graph.FindMinTree(aPath);
	for (auto it : aPath) {
		cout << graph.GetVex(it.vex1).name << " - " << graph.GetVex(it.vex2).name << '\t' << it.weight << "m" << endl;
	}
	cout << "铺设电路总长度：" << allWeight << "m" << endl;
}
