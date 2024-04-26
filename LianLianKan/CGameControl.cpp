#pragma once
#include "pch.h"
#include "CGameControl.h"
#include "CGameLogic.h"
#include "CGameException.h"

extern int Rows;
extern int Cols;
extern int Elem;
extern int Time;

CGameControl::CGameControl()
{
	m_nVexNum = 0;
	m_pAvPath = new Vertex[4];
	m_nElemNum = s_nRows * s_nCols;
}

CGameControl::~CGameControl()
{
	delete[] m_pAvPath;
}

int CGameControl::s_nRows = Rows;
int CGameControl::s_nCols = Cols;
int CGameControl::s_nPicNum = Elem;

void CGameControl::StartGame()
{
	try {
		m_pGameMap = m_GameLogic.InitMap();
	}
	catch(CGameException e){
		throw e;
	}
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
	m_ptSelFirst.info = m_pGameMap[nRow][nCol];
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
	m_ptSelSec.info = m_pGameMap[nRow][nCol];
}

bool CGameControl::Link()
{
	//�ж�ѡ�е��Ƿ���ͬһ��ͼƬ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col) {
		return false;
	}
	//�ж�ѡ���Ƿ�Ϊ��ͼƬ
	if (m_ptSelFirst.info == BLANK || m_ptSelSec.info == BLANK) {
		return false;
	}
	//�ж�����ͼƬ�Ƿ�Ϊͬ����
	if (m_ptSelFirst.info != m_ptSelSec.info) {
		return false;
	}
	//�ж�m_ptSelFirst��m_ptSelSec�Ƿ�����
	bool flag = m_GameLogic.IsLink(m_pGameMap, m_ptSelFirst, m_ptSelSec);
	m_nVexNum = m_GameLogic.GetVexPath(m_pAvPath);
	return flag;
}

bool CGameControl::GiveTip()
{
	return m_GameLogic.SearchValidPath(m_pGameMap);
}

bool CGameControl::IsWin()
{
	if (m_nElemNum == 0) {
		return true;
	}
	return false;
}

void CGameControl::ReSet()
{
	m_GameLogic.ReSetMap(m_pGameMap);
}
