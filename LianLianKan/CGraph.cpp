#include "pch.h"
#include "CGraph.h"

CGraph::CGraph()
{
	InitGraph();
}

CGraph::~CGraph()
{
}

void CGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}

}

int CGraph::AddVertex(int info)
{
	if (m_nVexNum >= MAX_VERTEX_NUM) {
		return m_nVexNum;
	}
	m_Vertices[m_nVexNum++] = info;
	return m_nVexNum;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVexNum()
{
	return m_nVexNum;
}
