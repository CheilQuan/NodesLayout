#include "DegreeAlgorithm.h"
#include "MacroDef.h"

CDegreeAlgorithm::CDegreeAlgorithm(void)
{
  m_CurNodesDegree.clear();
  m_NodesNum     = 0;
  m_EdgesNum     = 0;
}


CDegreeAlgorithm::~CDegreeAlgorithm(void)
{
}

bool CDegreeAlgorithm::isGraphSequence(std::vector<SNodesDegree> &p)
{
  clearDegree();
  m_NodesNum = p.size();

  degreeSort(p);   //��ͼ���н�������;
  for (int idx = 0; idx < m_NodesNum; ++idx)
  {
    m_EdgesNum += p[idx].m_NodesDegree;
  }
  if (0 != (m_EdgesNum % 2))  //������Ϊ����;
  {
    return false;
  }
  m_EdgesNum /= 2;          //�������ڶ�����һ��;

  for (int idx = 1; idx < m_NodesNum - 1; ++idx)
  {
    uint leftDegree = 0;
    for (int loop = 0; loop < idx; ++loop)
    {
      leftDegree += p[loop].m_NodesDegree;
    }
    uint rightDegree = idx * (idx - 1);
    for (int loop = idx; loop < m_NodesNum; ++loop)
    {
      rightDegree += Min(p[loop].m_NodesDegree, loop + 1);
    }

    if (leftDegree > rightDegree)
    {
      return false;
    }
  }

  return true;
}

void CDegreeAlgorithm::calcGraphInfo(const std::vector<SNodesDegree> &p, std::vector<SEdgeInfo> &e, uint &aEdgesCount)
{
  if (p.empty())
  { return;}

  m_CurNodesDegree.clear();
  e.resize(m_EdgesNum);
  aEdgesCount = m_EdgesNum;
  uint edgesIdx = 0;    //���±�;

  m_CurNodesDegree = p;
  for (int idx = 0; idx < m_NodesNum; ++idx)
  {
    degreeSort(m_CurNodesDegree);   //��ͼ���н�������;

    if (m_CurNodesDegree[0].m_NodesDegree == 0)   //ͼ���е�������;
    { break;}
    if (edgesIdx + m_CurNodesDegree[0].m_NodesDegree > m_EdgesNum)  //����������;
    { break;}

    for (int loop = 0; loop < m_CurNodesDegree[0].m_NodesDegree; ++loop)    //����ǰͼ���е��׵����δ洢�ڵ�ı�;
    {
      e[edgesIdx].m_EdgeId = edgesIdx;
      e[edgesIdx].m_Nodes.m_Node1 = m_CurNodesDegree[0].m_NodesID;
      e[edgesIdx].m_Nodes.m_Node2 = m_CurNodesDegree[loop + 1].m_NodesID;
      edgesIdx++;
    }
    std::vector<SNodesDegree> t(m_CurNodesDegree);    //��ʱ�洢��ǰͼ����;
    calcNextSequence(t);                              //���㵱ǰͼ���е���һ���ȼ�����;
  }
}

void CDegreeAlgorithm::clearDegree()
{
  m_CurNodesDegree.clear();
  m_EdgesNum = 0;
  m_NodesNum = 0;
}

void CDegreeAlgorithm::calcNextSequence(std::vector<SNodesDegree> &p)
{
  m_CurNodesDegree.clear();
  m_CurNodesDegree.resize(p.size() - 1);

  for (int idx = 0; idx < m_CurNodesDegree.size(); ++idx)
  {
    if (idx < p[0].m_NodesDegree)
    { 
      m_CurNodesDegree[idx].m_NodesDegree = p[idx + 1].m_NodesDegree - 1;
    }
    else
    {
      m_CurNodesDegree[idx].m_NodesDegree = p[idx + 1].m_NodesDegree;
    }
    m_CurNodesDegree[idx].m_NodesID = p[idx + 1].m_NodesID;
  }
}

void CDegreeAlgorithm::degreeSort(std::vector<SNodesDegree> &p)
{
  for (int idx = 0; idx < p.size() - 1; ++idx)
  {
    SNodesDegree maxDegree = p[idx];
    uint maxDgrIdx = idx;
    for (int loop = idx + 1; loop < p.size(); ++loop)
    {
      if (maxDegree.m_NodesDegree < p[loop].m_NodesDegree)
      {
        maxDegree = p[loop];
        maxDgrIdx = loop;
      }
    }
    p[maxDgrIdx] = p[idx];
    p[idx]       = maxDegree;
  }
}
