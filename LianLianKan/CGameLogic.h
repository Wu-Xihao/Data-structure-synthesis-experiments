#pragma once
#include "global.h"

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
public:
	Vertex m_avPath[4];
	int m_nVertexNum;
	int** InitMap();									//��ʼ����Ϸ��ͼ
	void ReleaseMap(int**& pGameMap);					//�ͷŵ�ͼ
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);	//�ж��Ƿ�����
	void Clear(int** pGameMap, Vertex v1, Vertex v2);	//���
	int GetVexPath(Vertex* avPath);
	bool SearchValidPath(int** pGameMap);
	void ReSetMap(int**& pGameMap);
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);			//�жϺ����Ƿ���ͨ
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);			//�ж������Ƿ���ͨ
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);		//һ���յ���ͨ�ж�
	bool LinkX(int** pGameMap, int nRow, int nCol1, int nCol2);		//ֱ����ͨX��
	bool LinkY(int** pGameMap, int nCol, int nRow1, int nRow2);		//ֱ����ͨY��
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);		//�����յ���ͨ�ж�
	bool LinkMiddle(int** pGameMap, Vertex v1, Vertex v2);			//�ж��ڲ��Ƿ���ͨ
	bool LinkOut(int** pGameMap, Vertex v1, Vertex v2);				//�ж���Χ�Ƿ���ͨ
	bool LinkYXY(int** pGameMap, Vertex v1, Vertex v2, int nRow);	//Y��X��Y����ͨ���
	bool LinkXYX(int** pGameMap, Vertex v1, Vertex v2, int nCol);	//X��Y��X����ͨ���
	void AddVertex(Vertex v);										//��Ԫ����ӵ�·������
	void DeleteVertex();
};

