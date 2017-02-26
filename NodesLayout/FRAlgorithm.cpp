#include "FRAlgorithm.h"
#include <vector>
#include <QThread>
#include <ctime>
#include "NodeDataManager.h"
#include "debug_new.h"

CFRAlgorithm::CFRAlgorithm(QObject *parent)
  : QObject(parent),
    m_IterTimes(0),    //Ĭ�ϵ�������0��;
    m_IdealDist(0.0),
    m_NodesDist(0.0),
    m_Repulsion(0.0),
    m_Attraction(0.0),
    m_UnitDistance(0.001),
    m_Temperature(WINDOW_WIDTH / 2),
    m_TempK(0.7),
    m_AttractParam(100.0),
    m_RepulsParam(0.08)
{
   
}

CFRAlgorithm::~CFRAlgorithm(void)
{
}

void CFRAlgorithm::FRAlgorithm(const short aData)
{
  m_IterTimes = (aData & EBC_IterTimes) >> 4;
  if (0 == m_IterTimes)
  { return;}

  std::vector<SEdgeInfo> &e = (CNodeDataManager::getInstance()->getEdgesInfo());
  std::vector<SNodeInfo> &p = (CNodeDataManager::getInstance()->getNodesInfo());
  
  if ((aData & EBC_IS3Dims) == 0)  //��ά�л�;
  {
    for (int idx = 0; idx < p.size(); ++idx)
    {
      p[idx].m_Coordinate.m_Z = 0.0;
    }
  }
  
  calcIdealDist(p.size());  //�����������;
  for (int iterTimes = 0; iterTimes < m_IterTimes; ++iterTimes)   //��������;
  {
    //����Ĺ����д��Ż�;
    for (int nodesIdx = 0; nodesIdx < p.size(); ++nodesIdx)       //�������;
    {
      for (int nodesIdx1 = 0; nodesIdx1 < p.size(); ++nodesIdx1)
      {
        if (nodesIdx1 != nodesIdx)
        {
          calcDistance(p[nodesIdx].m_Coordinate, p[nodesIdx1].m_Coordinate);  //�����������ľ���;
          calcRepulsion(m_NodesDist, m_IdealDist);        //�����;
          calcJoinForce(p[nodesIdx].m_Coordinate,      //����nodesIdx���ܵ��ĺ���; 
                        p[nodesIdx1].m_Coordinate, 
                          m_Repulsion);
        }
      }
      for (int edgeIdx = 0; edgeIdx < e.size(); ++edgeIdx)    //������;
      {
         if (e[edgeIdx].m_Nodes.m_Node1 == nodesIdx + 1)
         {
            e[edgeIdx].m_EdgeLegth = calcDistance(p[e[edgeIdx].m_Nodes.m_Node1 - 1].m_Coordinate, 
                                                     p[e[edgeIdx].m_Nodes.m_Node2 - 1].m_Coordinate); //�������;
            calcAttraction(m_NodesDist, m_IdealDist);              //��������;
            calcJoinForce(p[nodesIdx].m_Coordinate,             //����nodesIdx���ܵ��ĺ���; 
                          p[e[edgeIdx].m_Nodes.m_Node2 - 1].m_Coordinate, 
                            m_Attraction);
         }
         else if (e[edgeIdx].m_Nodes.m_Node2 == nodesIdx + 1)
         {
           e[edgeIdx].m_EdgeLegth = calcDistance(p[nodesIdx].m_Coordinate,      //�������;
                                        p[e[edgeIdx].m_Nodes.m_Node1 - 1].m_Coordinate); 
           
           calcAttraction(m_NodesDist, m_IdealDist);              //��������;
           calcJoinForce(p[nodesIdx].m_Coordinate,             //����nodesIdx���ܵ��ĺ���; 
                         p[e[edgeIdx].m_Nodes.m_Node1 - 1].m_Coordinate, 
                           m_Attraction);
         }
      }
      calcMoveCoordinate(p[nodesIdx].m_Coordinate, m_JionForce);  //�������ܺ����µ��ƶ�����;
      if ((aData & EBC_seeNodesMove))  //���Ҫ����ڵ�鿴����;
      {QThread::msleep(300);}
    }
    if (aData & EBC_seeProcess)        //����û���Ҫ������̲鿴����;
    { QThread::msleep(500);}
           
    m_JionForce.clear();              //����ϴεĺ�������;
    cool();

    //��ͼ���Ƶ���Ļ����;
    for (int indx = 1; indx < p.size(); ++indx)
    {
      p[indx].m_Coordinate -= p[0].m_Coordinate;
    }
    p[0].m_Coordinate.clear();
  }

  emit signal_algoFinished(1);   //�źŷ�������Ӧ�����߳�ID;
  return;
}

inline double CFRAlgorithm::calcRepulsion(const double &aDist, const double &aIdealDist)
{
  if (0.0 == aDist)
  {
    m_Repulsion = INFINITY_NUM;
  }
  else
    m_Repulsion = powf(aIdealDist, 2.0) / aDist * m_RepulsParam;

  //m_Repulsion = Min(m_Repulsion, 1000.0);
  return m_Repulsion;
}

inline double CFRAlgorithm::calcAttraction(const double &aDist, const double &aIdealDist)
{
  if (0.0 == aIdealDist)
  {
    m_Attraction = INFINITY_NUM;
  }
  else 
    m_Attraction = powf(aDist, 2.0) / aIdealDist * m_AttractParam;

  m_Attraction = -m_Attraction;
  return m_Attraction;
}

inline double CFRAlgorithm::calcDistance(const SNodeCoordinate &aC1, const SNodeCoordinate &aC2)
{
  m_NodesDist = sqrtf(powf(aC1.m_X - aC2.m_X, 2.0) + powf(aC1.m_Y - aC2.m_Y, 2.0) + powf(aC1.m_Z - aC2.m_Z, 2.0));
  m_NodesDist = Max(INFINITESIMAL_NUM, m_NodesDist);
  
  return m_NodesDist;
}

double CFRAlgorithm::calcIdealDist(uint aNodeNum)
{
  if (0 == aNodeNum)
  {
    return 0.0;
  }
  m_IdealDist = sqrtf(WINDOW_HEIGHT * WINDOW_WIDTH / aNodeNum); 
  return m_IdealDist;
}

void CFRAlgorithm::calcMoveCoordinate(SNodeCoordinate &aMoveC, SNodeCoordinate &aJionForce)
{
  //ʹ�ý����㷨�����Ƶ��ƶ�����;
  double dist = sqrtf(powf(aJionForce.m_X, 2.0) + powf(aJionForce.m_Y, 2.0) + powf(aJionForce.m_Z, 2.0));
  if (dist != Min(dist, m_Temperature))  //�ƶ����볬��������;
  {
    aJionForce.m_X = aJionForce.m_X / dist * m_Temperature;
    aJionForce.m_Y = aJionForce.m_Y / dist * m_Temperature;
    aJionForce.m_Z = aJionForce.m_Z / dist * m_Temperature;
  }
  
  aMoveC += aJionForce;  //�ڽ��𷨺�ĺ���������ƽ��; 

  //ƽ�ƺ��������Ļ��;
  aMoveC.m_X = Max(aMoveC.m_X, -WINDOW_WIDTH  / 2);
  aMoveC.m_X = Min(aMoveC.m_X,  WINDOW_WIDTH  / 2);
  aMoveC.m_Y = Max(aMoveC.m_Y, -WINDOW_HEIGHT / 2);
  aMoveC.m_Y = Min(aMoveC.m_Y,  WINDOW_HEIGHT / 2);
  aMoveC.m_Z = Max(aMoveC.m_Z, -WINDOW_HEIGHT / 2);
  aMoveC.m_Z = Min(aMoveC.m_Z,  WINDOW_HEIGHT / 2);
}

void CFRAlgorithm::calcJoinForce(const SNodeCoordinate &aBeForceC, const SNodeCoordinate &aC, const double aForce)
{
  if (0.0 == m_NodesDist) //�����غ�;
  {
    srand(time(0));
    m_JionForce.m_X += (rand() % 10) / 10.0 * aForce * m_UnitDistance;  //��X����ƽ��;
    m_JionForce.m_Y += (rand() % 10) / 10.0 * aForce * m_UnitDistance;  //��X����ƽ��;
    m_JionForce.m_Z += (rand() % 10) / 10.0 * aForce * m_UnitDistance;  //��X����ƽ��;
     
    return;
  }

  double cos_VX = (aBeForceC.m_X - aC.m_X) / m_NodesDist;   //�����㹹�ɵ�������X���cosֵ;
  double cos_VY = (aBeForceC.m_Y - aC.m_Y) / m_NodesDist;   //�����㹹�ɵ�������Y���cosֵ;
  double cos_VZ = (aBeForceC.m_Z - aC.m_Z) / m_NodesDist;   //�����㹹�ɵ�������Z���cosֵ;

  m_JionForce.m_X += aForce*m_UnitDistance*cos_VX;          //X�����ƶ��ľ���;
  m_JionForce.m_Y += aForce*m_UnitDistance*cos_VY;          //Y�����ƶ��ľ���;
  m_JionForce.m_Z += aForce*m_UnitDistance*cos_VZ;          //Z�����ƶ��ľ���;
}

void CFRAlgorithm::cool()
{
  m_Temperature *= m_TempK;
  m_Temperature = Max(2, m_Temperature);
}

void CFRAlgorithm::slot_runAlgorithm(SParamPack aData)
{
  resetParameter(aData);
  FRAlgorithm(aData.m_5InOneParam);
}

void CFRAlgorithm::resetParameter(SParamPack &aData)
{
    m_UnitDistance = aData.m_DispMove;
    m_TempK        = aData.m_TempK;
    m_RepulsParam  = aData.m_RepulsParam;
    m_AttractParam = aData.m_AttractParam;
    m_JionForce.clear();
}