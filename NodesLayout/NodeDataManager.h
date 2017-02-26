#ifndef _NODEDATAMANAGER_H_
#define _NODEDATAMANAGER_H_

#include "MacroDef.h"
#include "SingleTon.h"
#include "StructDefine.h"
#include "DegreeAlgorithm.h"
#include <vector>
#include <QMutexLocker>

class CNodeDataManager : public CSingleTon<CNodeDataManager>
{
public:
  CNodeDataManager(void);
  ~CNodeDataManager(void);

  bool setEdgesNodesInfo(const std::vector<SNodesDegree> &p);//�Ӷ�����ת��Ϊ�ڵ����Ϣ;
  bool loadEdgesNodesInfo(const char *aPath);               //���ļ������ȡ�ڵ��ϵ��Ϣ;
  bool saveNodesInfo(const SNodeInfo &aNodeInfo);           //��NodeInfoVector���������;
  std::vector<SNodeInfo> &getNodesInfo();                   //ȡ��NodeInfoVector;
  std::vector<SEdgeInfo> &getEdgesInfo();                   //ȡ��NodeRelationPairVector;

  void initNodesPostion();                                  //��ʼ���ڵ�λ��(��������ڵ�λ��);
  void clearNodesInfo();                                    //����ڵ���Ϣ����;
  void clearEdgesInfo();                                    //����ڵ��ϵ����;

protected:
  void randomCoordinate(SNodeCoordinate &aNodeCoord) const;  //�����������;
  int findTheFirstNumFromStr(const char *aStr, int &aIndex) const;                  //ȡ��aStr�еĵ�һ�������ַ���תΪint;
private:
  std::vector<SEdgeInfo>          m_vEdgesInfo;           //���ڴ洢���нڵ��ϵ��;
  std::vector<SNodeInfo>          m_vNodesInfo;           //���ڴ洢�ڵ�������Ϣ;
  
  DEFSETGET(RandRoomSize, uint, private);                //�����ʼ���Ŀռ��С;
  DEFSETGET(NodeCount, uint, private);                   //��¼�ڵ����;   
  DEFSETGET(EdgeCount, uint, private);                   //��¼������;     

  mutable QMutex                  m_Mutex;               //������;
};


#endif
