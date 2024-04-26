#pragma once
#include "pch.h"
#include "CGameLogic.h"
#include "CGameException.h"

extern int Rows;
extern int Cols;
extern int Elem;
extern int Time;

CGameLogic::CGameLogic()
{
	m_nVertexNum = 0;
}

CGameLogic::~CGameLogic()
{
}

int** CGameLogic::InitMap()
{
	//��ȡ��ͼ��С�ͻ�ɫ
	int nRows = Rows;
	int nCols = Cols;
	int nPicNum = Elem;
	//�����ڴ�����
	int** pGameMap = new int* [nRows];
	if (pGameMap == NULL) {
		throw CGameException(("�ڴ��쳣!"));
	}
	else {
		for (int i = 0; i < nRows; i++) {
			pGameMap[i] = new int[nCols];
			if (pGameMap[i] == NULL) {
				throw CGameException(("�ڴ��쳣!"));
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}
	//���ٻ�ɫ
	if ((nRows * nCols) % (nPicNum * 2) != 0) {
		ReleaseMap(pGameMap);
		throw CGameException(("��ƥ��!"));
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++) {
		//�ظ���
		for (int j = 0; j < nRepeatNum; j++) {
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}
	//��������
	srand((int)time(NULL));
	//�������������������
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		//����������ֵ
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
	return pGameMap;
}

void CGameLogic::ReleaseMap(int**& pGameMap)
{
	for (int i = 0; i < Rows; i++) {
		delete[] pGameMap[i];
	}
	delete[] pGameMap;
}

bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	//���³�ʼ��·��Ԫ�ظ���
	m_nVertexNum = 0;
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	//�ж�һ��ֱ���Ƿ���ͨ
	if (nRow1 == nRow2) {
		if (LinkInRow(pGameMap, v1, v2)) {
			//���·��Ԫ��
			AddVertex(v1);
			AddVertex(v2);
			return true;
		}
	}
	else if (nCol1 == nCol2) {
		if (LinkInCol(pGameMap, v1, v2)) {
			//���·��Ԫ��
			AddVertex(v1);
			AddVertex(v2);
			return true;
		}
	}
	//�ж�����ֱ���Ƿ���ͨ
	if (OneCornerLink(pGameMap, v1, v2)) {
		return true;
	}
	//�ж�����ֱ���Ƿ���ͨ
	if (TwoCornerLink(pGameMap, v1, v2)) {
		return true;
	}
	return false;
}

void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2)
{
	pGameMap[v1.row][v1.col] = BLANK;
	pGameMap[v2.row][v2.col] = BLANK;
}

int CGameLogic::GetVexPath(Vertex* avPath)
{
	for (int i = 0; i < m_nVertexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVertexNum;
}

bool CGameLogic::SearchValidPath(int** pGameMap)
{
	for (int nRow1 = 0; nRow1 < Rows; nRow1++) {
		for (int nCol1 = 0; nCol1 < Cols; nCol1++) {
			if (pGameMap[nRow1][nCol1] == BLANK) {
				continue;
			}
			for (int nRow2 = nRow1; nRow2 < Rows; nRow2++) {
				for (int nCol2 = 0; nCol2 < Cols; nCol2++) {
					if (nRow2 == nRow1 && nCol2 <= nCol1) {
						nCol2 = nCol1;
						continue;
					}
					if (pGameMap[nRow2][nCol2] == BLANK) {
						continue;
					}
					if (pGameMap[nRow1][nCol1] == pGameMap[nRow2][nCol2]) {
						Vertex v1;
						Vertex v2;
						v1.row = nRow1;
						v1.col = nCol1;
						v1.info = pGameMap[nRow1][nCol1];
						v2.row = nRow2;
						v2.col = nCol2;
						v2.info = pGameMap[nRow2][nCol2];
						bool flag = IsLink(pGameMap, v1, v2);
						if (flag) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void CGameLogic::ReSetMap(int**& pGameMap)
{
	int nRows = Rows;
	int nCols = Cols;
	//��������
	srand((int)time(NULL));
	//�������������������
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++) {
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		//����������ֵ
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
}

bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (nCol1 > nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}
	for (int nCol = nCol1 + 1; nCol <= nCol2; nCol++) {
		if (nCol == nCol2) {
			return true;
		}
		if (pGameMap[nRow][nCol] != BLANK) {
			break;
		}
	}
	return false;
}

bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nCol = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}
	for (int nRow = nRow1 + 1; nRow <= nRow2; nRow++) {
		if (nRow == nRow2) {
			return true;
		}
		if (pGameMap[nRow][nCol] != BLANK) {
			break;
		}
	}
	return false;
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	//���жϹյ��Ƿ�Ϊ�գ����ж��Ƿ���ͨ
	if (pGameMap[v1.row][v2.col] == BLANK) {
		if (LinkX(pGameMap, v1.row, v1.col, v2.col) && LinkY(pGameMap, v2.col, v1.row, v2.row)) {
			//���·��Ԫ��
			Vertex v3;
			v3.row = v1.row;
			v3.col = v2.col;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v2);
			return true;
		}
	}
	if (pGameMap[v2.row][v1.col] == BLANK) {
		if (LinkX(pGameMap, v2.row, v1.col, v2.col) && LinkY(pGameMap, v1.col, v1.row, v2.row)) {
			//���·��Ԫ��
			Vertex v3;
			v3.row = v2.row;
			v3.col = v1.col;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v2);
			return true;
		}
	}
	return false;
}

bool CGameLogic::LinkX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
	//�ж�(nRow,nCol1)��(nRow,nCol2)�Ƿ���ͨ
	Vertex v1;
	v1.row = nRow;
	v1.col = nCol1;
	v1.info = pGameMap[nRow][nCol1];
	Vertex v2;
	v2.row = nRow;
	v2.col = nCol2;
	v2.info = pGameMap[nRow][nCol2];
	return LinkInRow(pGameMap, v1, v2);
}

bool CGameLogic::LinkY(int** pGameMap, int nCol, int nRow1, int nRow2)
{
	//�ж�(nRow1,nCol)��(nRow2,nCol)�Ƿ���ͨ
	Vertex v1;
	v1.row = nRow1;
	v1.col = nCol;
	v1.info = pGameMap[nRow1][nCol];
	Vertex v2;
	v2.row = nRow2;
	v2.col = nCol;
	v2.info = pGameMap[nRow2][nCol];
	return LinkInCol(pGameMap, v1, v2);
}

bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	//�ж��м������Ƿ�����
	if (LinkMiddle(pGameMap, v1, v2)) {
		return true;
	}
	//�ж���Χ�����Ƿ�����
	if (LinkOut(pGameMap, v1, v2)) {
		return true;
	}
	return false;
}

bool CGameLogic::LinkMiddle(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if (nRow1 == nRow2 || nCol1 == nCol2) {
		return false;
	}
	//YXY��ͨ���
	int minRow = nRow1;
	int maxRow = nRow2;
	if (minRow > maxRow) {
		int temp = minRow;
		minRow = maxRow;
		maxRow = temp;
	}
	for (int nRow = minRow + 1; nRow < maxRow; nRow++) {
		if (LinkYXY(pGameMap, v1, v2, nRow)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = nRow;
			v4.row = nRow;
			v3.col = v1.col;
			v4.col = v2.col;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	//XYX��ͨ���
	int minCol = nCol1;
	int maxCol = nCol2;
	if (minCol > maxCol) {
		int temp = minCol;
		minCol = maxCol;
		maxCol = temp;
	}
	for (int nCol = minCol + 1; nCol < maxCol; nCol++) {
		if (LinkXYX(pGameMap, v1, v2, nCol)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = v1.row;
			v4.row = v2.row;
			v3.col = nCol;
			v4.col = nCol;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	return false;
}

bool CGameLogic::LinkOut(int** pGameMap, Vertex v1, Vertex v2)
{
	int minRow = v1.row;
	int maxRow = v2.row;
	if (minRow > maxRow) {
		int temp = minRow;
		minRow = maxRow;
		maxRow = temp;
	}
	int minCol = v1.col;
	int maxCol = v2.col;
	if (minCol > maxCol) {
		int temp = minCol;
		minCol = maxCol;
		maxCol = temp;
	}
	//�ϲ�������
	for (int nRow = minRow-1; nRow >= 0; nRow--) {
		if (LinkYXY(pGameMap, v1, v2, nRow)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = nRow;
			v4.row = nRow;
			v3.col = v1.col;
			v4.col = v2.col;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	//�²�������
	for (int nRow = maxRow+1; nRow < Rows; nRow++) {
		if (LinkYXY(pGameMap, v1, v2, nRow)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = nRow;
			v4.row = nRow;
			v3.col = v1.col;
			v4.col = v2.col;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	//�󲿷�����
	for (int nCol = minCol - 1; nCol >= 0; nCol--) {
		if (LinkXYX(pGameMap, v1, v2, nCol)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = v1.row;
			v4.row = v2.row;
			v3.col = nCol;
			v4.col = nCol;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	//�Ҳ�������
	for (int nCol = maxCol+1; nCol < Cols; nCol++) {
		if (LinkXYX(pGameMap, v1, v2, nCol)) {
			//���·��
			Vertex v3;
			Vertex v4;
			v3.row = v1.row;
			v4.row = v2.row;
			v3.col = nCol;
			v4.col = nCol;
			AddVertex(v1);
			AddVertex(v3);
			AddVertex(v4);
			AddVertex(v2);
			return true;
		}
	}
	return false;
}

bool CGameLogic::LinkYXY(int** pGameMap, Vertex v1, Vertex v2, int nRow)
{
	if (pGameMap[nRow][v1.col] != BLANK || pGameMap[nRow][v2.col] != BLANK) {
		return false;
	}
	Vertex v3;
	Vertex v4;
	v3.row = nRow;
	v4.row = nRow;
	v3.col = v1.col;
	v4.col = v2.col;
	bool flag1 = LinkInRow(pGameMap, v3, v4);
	bool flag2 = LinkInCol(pGameMap, v1, v3);
	bool flag3 = LinkInCol(pGameMap, v2, v4);
	return flag1 && flag2 && flag3;
}

bool CGameLogic::LinkXYX(int** pGameMap, Vertex v1, Vertex v2, int nCol)
{
	if (pGameMap[v1.row][nCol] != BLANK || pGameMap[v2.row][nCol] != BLANK) {
		return false;
	}
	Vertex v3;
	Vertex v4;
	v3.row = v1.row;
	v4.row = v2.row;
	v3.col = nCol;
	v4.col = nCol;
	bool flag1 = LinkInCol(pGameMap, v3, v4);
	bool flag2 = LinkInRow(pGameMap, v1, v3);
	bool flag3 = LinkInRow(pGameMap, v2, v4);
	return flag1 && flag2 && flag3;
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVertexNum++] = v;
}

void CGameLogic::DeleteVertex()
{
	m_nVertexNum--;
}


