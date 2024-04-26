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
	Vertices m_Vertices;	//��������
	AdjMatrix m_AdjMatrix;	//��ϵ����
	int m_nVexNum;			//��������
	int m_nArcNum;			//�ߵ�����
public:
	void InitGraph();						//��ʼ��ͼ�Ķ���͹�ϵ
	int AddVertex(int info);				//������info��ӵ���������
	int GetVertex(int nIndex);				//��ȡ��������������ΪnIndex�Ķ���
	void AddArc(int nV1Index, int nV2Index);//��ӹ�ϵ������nV1Index��nV2Index�Ĺ�ϵ
	int GetVexNum();						//��ȡ���������еĶ�����
};

