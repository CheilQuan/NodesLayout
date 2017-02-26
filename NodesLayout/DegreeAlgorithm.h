#ifndef _DEGREEALGORITHM_H_
#define _DEGREEALGORITHM_H_

#include "SingleTon.h"
#include "StructDefine.h"
#include <vector>

class CDegreeAlgorithm : public CSingleTon<CDegreeAlgorithm>
{
public:
  CDegreeAlgorithm(void);
  ~CDegreeAlgorithm(void);

  bool isGraphSequence(std::vector<SNodesDegree> &p); //�ж�ĳ�������Ƿ�Ϊͼ����;
  void calcGraphInfo(const std::vector<SNodesDegree> &p,
                     std::vector<SEdgeInfo> &e,
                     uint &aEdgesNum);                   //�Ӷ���Ϣ��p���õ�����Ϣ��e���ͽڵ�����aNodesCount��;
  void clearDegree();                                      //�������Ϣ;
  void degreeSort(std::vector<SNodesDegree> &p);           //�Խڵ����Ϣ�Ӵ�С����;

private:
  void calcNextSequence(std::vector<SNodesDegree> &p);     //�ɴ����ͼ���м�����һ�ȼ�����;

private:
  std::vector<SNodesDegree>       m_CurNodesDegree;      //��ǰ�Ľڵ����Ϣ;
  uint                            m_NodesNum;            //�ڵ���;
  uint                            m_EdgesNum;            //����;
  
};


#endif
