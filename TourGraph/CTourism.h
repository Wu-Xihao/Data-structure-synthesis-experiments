#pragma once
#include"Header.h"
using namespace std;

class cTourism {
public :
	cTourism();//���캯��
	void CreateGraph();//��ȡ�ļ���������������ͼ
	void GetSpotInfo();//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
	void TravelPath();//��ѯ���ξ��㵼��·��
	void FindShortPath();//�����������������·��
	void DesignPath();//��ѯ�����·�滮ͼ
private:
	CGraph graph;//CGraph�������ڴ洢��������ͼ
};