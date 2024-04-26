//ʵ�־�����Ϣ����ϵͳ����ع���
#include"Header.h"
using namespace std;

//���캯��
cTourism::cTourism()
{
	graph.Init();
}

//��ȡ�ļ���������������ͼ
void cTourism::CreateGraph()
{
	cout << "===== �������㾰��ͼ =====" << endl;
	cout << "��������" << graph.GetVexNum() << endl;
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	cout << "----- �� -----" << endl;
	for (int i = 0; i < graph.GetEdgeNum(); i++) {
		Edge e = graph.GetEdge(i);
		cout << "<v" << e.vex1 << ",v" << e.vex2 << "> " << e.weight << endl;
	}
}

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
void cTourism::GetSpotInfo()
{
	cout << "===== ��ѯ������Ϣ =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int num;
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	do {
		cin >> num;
		if (num < 0 || num >= graph.GetVexNum()) {
			cerr << "��Ŵ���" << endl;
			cout << "���������룺";
		}
		else {
			break;
		}
	} while (true);
	Vex v = graph.GetVex(num);
	cout << v.name << endl;
	cout << v.introduce << endl;
	cout << "----- �ܱ߾��� -----" << endl;
	vector<Edge> aEdge = graph.FindEdge(num);
	for (auto it:aEdge) {
		cout << graph.GetVex(it.vex1).name << "->" << graph.GetVex(it.vex2).name << " " << it.weight << "m" << endl;
	}
}

//��ѯ���ξ��㵼��·��
void cTourism::TravelPath()
{
	cout << "===== ���ξ��㵼�� =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int n;
	cout << "���������ı�ţ�";
	do {
		cin >> n;
		if (n < 0 || n >= graph.GetVexNum()) {
			cerr << "�����Ŵ���" << endl;
			cout << "���������룺";
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
		cout << "·��" << num << "��";
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

//�����������������·��
void cTourism::FindShortPath()
{
	cout << "===== �������·�� =====" << endl;
	for (int i = 0; i < graph.GetVexNum(); i++) {
		Vex v = graph.GetVex(i);
		cout << i << "-" << v.name << endl;
	}
	int n1, n2;
	cout << "���������ı�ţ�";
	do {
		cin >> n1;
		if (n1 < 0 || n1 >= graph.GetVexNum()) {
			cerr << "�����Ŵ���" << endl;
			cout << "���������룺";
		}
		else {
			break;
		}
	} while (true);
	cout << "�������յ��ţ�";
	do {
		cin >> n2;
		if (n2 < 0 || n2 >= graph.GetVexNum()) {
			cerr << "�����Ŵ���" << endl;
			cout << "���������룺";
		}
		else {
			break;
		}
	} while (true);
	vector<int> aPath;
	//aPath��һ��Ԫ��Ϊ���·�����ȣ�����Ԫ������Ϊ·���Ķ�������
	int pathLength = graph.FindShortPath(n1, n2, aPath);
	//���·���;���
	for (auto it : aPath) {
		cout << graph.GetVex(it).name;
		cout << "->";
	}
	cout << graph.GetVex(n2).name << endl;
	cout << "·�����ȣ�" << pathLength << "m" << endl;
}

//��ѯ�����·�滮ͼ
void cTourism::DesignPath()
{
	cout << "===== �����·�滮 =====" << endl;
	cout << "��������������֮�������·��" << endl;
	vector<Edge> aPath;
	int allWeight = graph.FindMinTree(aPath);
	for (auto it : aPath) {
		cout << graph.GetVex(it.vex1).name << " - " << graph.GetVex(it.vex2).name << '\t' << it.weight << "m" << endl;
	}
	cout << "�����·�ܳ��ȣ�" << allWeight << "m" << endl;
}
