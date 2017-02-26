#ifndef _FRALGORITHM_H_
#define _FRALGORITHM_H_

#include <QObject>
#include "MacroDef.h"
#include "StructDefine.h"

class CFRAlgorithm : public QObject
{
  Q_OBJECT
public:
  CFRAlgorithm(QObject *parent = 0);
  ~CFRAlgorithm(void);

  void FRAlgorithm(const short aIterTimes = 100);
protected:
  double calcRepulsion(const double &aDist, const double &aIdealDist);    //���������ĳ���;
  double calcAttraction(const double &aDist, const double &aIdealDist);   //��������������;
  double calcDistance(const SNodeCoordinate &aC1,                       //���������ľ���;
                      const SNodeCoordinate &aC2);                      

  double calcIdealDist(uint aNodeNum);                                  //�����������;

  /*
  �� �� ����calcMoveCoordinate();
  ����˵����aC1Ϊ���㣬aMoveCΪ��Ҫ�ƶ��ĵ㣬aJionForceΪ������С(+��ʾ������-��ʾ����);
  ��    �ܣ������aMoveC�����꽫ֱ�ӱ���Ϊ�ƶ��������,�ƶ��������ܺ����ƶ�;
  */
  void calcMoveCoordinate(SNodeCoordinate &aMoveC,       
                          SNodeCoordinate &aJionForce);             
  
  /*
  �� �� ����calcJoinForce();
  ����˵���������������������������Ҫ�ڸ����������ϵ�����������ε��ã�����õ��ܵ��ĺ���;
  ����˵����aBeForceCΪ�����㣬aCΪ�����㣬aForceΪ����С(+��ʾ������-��ʾ����);
  ��    �ܣ������aMoveC�����꽫ֱ�ӱ���Ϊ�ƶ��������,�ƶ�����Ϊ�����㹹�ɵ���������;
  */
  void calcJoinForce(const SNodeCoordinate &aBeForceC, 
                     const SNodeCoordinate &aC, 
                     const double aForce);

  void cool();                           //�����㷨,�����¶�ϵ��;
  void resetParameter(SParamPack &aData);                 //���ò���;

protected slots:
  void slot_runAlgorithm(SParamPack aData);     //��ʼ�����㷨�Ľӿڲ�;

signals:
  void signal_algoFinished(int);              //�㷨���н���;
private:
  DEFSETGET(IterTimes, uint, private);         //�㷨��������;
  DEFSETGET(IdealDist, double, private);       //�������(ƽ�����);
  DEFSETGET(NodesDist, double, private);       //�������������;
  DEFSETGET(Repulsion, double, private);       //����;
  DEFSETGET(Attraction, double, private);      //����;
  DEFSETGET(UnitDistance, double, private);    //�㷨����ƽ�Ƶĵ�λ����;
  DEFSETGET(Temperature, double,  private);    //�㷨���¶�ϵ��;
  DEFSETGET(TempK, double, private);           //����ϵ��;
  DEFSETGET(JionForce, SNodeCoordinate, private);//һ�����ܵ��ĺ���;
  DEFSETGET(AttractParam, float, private);     //����ϵ��;
  DEFSETGET(RepulsParam, float, private);      //����ϵ��;
};

#endif

