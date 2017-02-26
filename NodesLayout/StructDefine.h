#ifndef _STRUCTDEF_H_
#define _STRUCTDEF_H_

/*���Ͷ���*/
typedef unsigned int      uint;
typedef unsigned short    ushort;
typedef unsigned char     uchar;

/*ȫ�ֱ���/����������*/
static double WINDOW_WIDTH  = 700.0 ;           //���ڿ��;
static double WINDOW_HEIGHT = 400.0 ;           //���ڸ߶�;

const double INFINITY_NUM      = 100000.0;        //�������;
const double INFINITESIMAL_NUM = 0.0000001;       //����С��;

/*ö����������*/
enum EsBitContral    //λ����ö��,��һ��short�����ĸ�bit���躬��;
{
  EBC_IS3Dims      = 0x0001,   //�Ƿ�Ϊ��ά����1bit����1-true,0-false;
  EBC_IsAlgStop    = 0x0002,   //�Ƿ���ͣ�㷨����2bit��,û��;
  EBC_seeNodesMove = 0x0004,   //�Ƿ���鿴�ڵ㲼�ֹ���(��3bit);
  EBC_seeProcess   = 0x0008,   //�Ƿ�����̲鿴���ֹ��̣���4bit����һ�ε���Ϊһ������;
  EBC_IterTimes    = 0x1FF0,   //��������,��short�ĵ�5bit��13bit��0~511��;
                               //��3bit��ʱԤ��;
};



/*�ṹ�嶨����*/
typedef struct _SNodeCoordinate  //�ڵ����ά����;
{
  double m_X;
  double m_Y;
  double m_Z;

  _SNodeCoordinate()
  {
    m_X = m_Y = m_Z = 0.0;
  }

  void clear()
  {
    m_X = m_Y = m_Z = 0.0;
  }
  void operator+=(_SNodeCoordinate &aN)   //����+=�����;
  {
    m_X += aN.m_X;
    m_Y += aN.m_Y;
    m_Z += aN.m_Z;
  }
  void operator-=(_SNodeCoordinate &aN)
  {
    m_X -= aN.m_X;
    m_Y -= aN.m_Y;
    m_Z -= aN.m_Z;
  }
}SNodeCoordinate;

typedef struct _SNodeInfo         //�洢�ڵ������������Ϣ;
{
  SNodeCoordinate m_Coordinate;   //�ڵ�����;
  uint            m_NodeID;       //�ڵ��ǩ,�ڵ��Ψһ��־ID;

  _SNodeInfo()
  {
    m_NodeID = 0;
  }
}SNodeInfo;

typedef struct _SNodeRelationPair //�ڵ��ϵ��,���ڴ洢�����ڵ�Ĺ�����ϵ��a�Žڵ���b�Žڵ������ӣ���m_Node1 = a; m_Node2 = b��;
{
  uint m_Node1;                   //��ʾ�ڵ��ID;
  uint m_Node2;                   //��ʾ�ڵ��ID;

  _SNodeRelationPair()
  {
    m_Node1 = m_Node2 = 0;
  }
}SNodeRelationPair;

typedef struct _SEdgeInfo         //����Ϣ;
{
  SNodeRelationPair m_Nodes;      //�ߵ������ڵ�;
  uint              m_EdgeId;     //�ߵ�ID;
  double            m_EdgeLegth;  //�ߵĳ���; 
  _SEdgeInfo()
  {
    m_EdgeId = 0;
    m_EdgeLegth = 0.0;
  }
}SEdgeInfo;

typedef struct _SParamPack    //�����㷨����Ĳ�����;
{
  short                 m_5InOneParam;    //5����������;
  float                 m_AttractParam;   //����ϵ��;
  float                 m_RepulsParam;    //����ϵ��;
  float                 m_TempK;          //����ϵ��;
  float                 m_DispMove;       //��λλ�ƴ�С;
  _SParamPack()
  {
    clear();
  }
  void clear()
  {
    m_5InOneParam  = 0;
    m_RepulsParam  = 0.0;
    m_AttractParam = 0.0;
    m_TempK        = 0.0;
    m_DispMove     = 0.0;
  }
}SParamPack;

typedef struct _SNodesDegree                   //�ڵ����Ϣ;    
{
  uint            m_NodesID;            //�ڵ�ID;
  uint            m_NodesDegree;        //�ڵ����;

  _SNodesDegree()
  {
    m_NodesDegree = m_NodesID = 0;    
  }

  void operator=(const _SNodesDegree &p)
  {
    this->m_NodesDegree = p.m_NodesDegree;
    this->m_NodesID     = p.m_NodesID;
  }
}SNodesDegree;

// typedef struct _SRelationThread
// {
// 
// }SRealationThread;

#endif