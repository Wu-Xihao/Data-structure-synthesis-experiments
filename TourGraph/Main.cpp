#include"Header.h"
using namespace std;

int menu() {
	cout << "===== ������Ϣ����ϵͳ =====" << endl;
	cout << "1.������������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.�������·��" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�" << endl;
	cout << "============================" << endl;
	cout << "�����������ţ�0~5����";
	int num;
	do {
		cin >> num;
		if (num != 0 && num != 1&&num != 2 && num != 3 && num != 4 && num != 5) {
			cerr << "�����Ŵ���" << endl;
			cout << "���������룺";
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