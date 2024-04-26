#pragma once
#include "CGameLogic.h"
#include "global.h"
#include "CGraph.h"


class CGameControl
{
public:
	//���캯������������
	CGameControl();
	~CGameControl();
public:
	//��̬��Ա����
	static int s_nRows;		//��Ϸ����
	static int s_nCols;		//��Ϸ����
	static int s_nPicNum;	//ͼƬ��
	//���ݳ�Ա
	//CGraph m_garph;
	int** m_pGameMap;		//��Ϸ��ͼ����ָ��
	CGameLogic m_GameLogic;	//��Ϸ�߼���������
	Vertex m_ptSelFirst;	//ѡ�еĵ�һ��Ԫ��
	Vertex m_ptSelSec;		//ѡ�еĵڶ���Ԫ��
	Vertex* m_pAvPath;		//����·��
	int m_nVexNum;			//����·����Ԫ�ظ���
	int m_nElemNum;			//Ԫ��ʣ������
	//��Ա����
	void StartGame();						//��ʼ��Ϸ
	int GetElement(int nRow, int nCol);		//�õ�ĳһ��Ԫ��
	void SetFirstPoint(int nRow, int nCol);	//���õ�һ��Ԫ��
	void SetSecPoint(int nRow, int nCol);	//���õڶ���Ԫ��
	bool Link();							//�ж��Ƿ��������õ�·��
	bool GiveTip();							//��ʾ�������һ����ͨͼƬ��·��
	bool IsWin();							//�ж���Ϸ�Ƿ�ʤ��
	void ReSet();							//������Ϸ��ͼ
};

