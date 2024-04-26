#pragma once
#include"Header.h"
using namespace std;

class cTourism {
public :
	cTourism();//构造函数
	void CreateGraph();//读取文件，创建景区景点图
	void GetSpotInfo();//查询指定景点信息，显示到相邻景点的距离
	void TravelPath();//查询旅游景点导航路线
	void FindShortPath();//搜索两个景点间的最短路径
	void DesignPath();//查询铺设电路规划图
private:
	CGraph graph;//CGraph对象，用于存储景区景点图
};