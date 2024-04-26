#include"Header.h"
using namespace std;

int menu() {
	cout << "===== 景区信息管理系统 =====" << endl;
	cout << "1.创建景区景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.搜索最短路径" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出" << endl;
	cout << "============================" << endl;
	cout << "请输入操作编号（0~5）：";
	int num;
	do {
		cin >> num;
		if (num != 0 && num != 1&&num != 2 && num != 3 && num != 4 && num != 5) {
			cerr << "输入编号错误！" << endl;
			cout << "请重新输入：";
		}
		else {
			break;
		}
	} while (true);
	return num;
}

void process() {
	int num = 0;
	cTourism tour;
	do {
		num = menu();
		switch (num) {
		case 1:
			tour.CreateGraph();
			break;
		case 2:
			tour.GetSpotInfo();
			break;
		case 3:
			tour.TravelPath();
			break;
		case 4:
			tour.FindShortPath();
			break;
		case 5:
			tour.DesignPath();
			break;
		default:
			break;
		}
		cout << endl;
	} while (num != 0);
}

int main() {
	process();
	return 0;
}