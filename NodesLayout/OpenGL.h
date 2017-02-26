#ifndef OPENGL_H
#define OPENGL_H

#include <QtOpenGL/qgl.h>
#include <gl/glut.h>
#include <qevent.h>
#include "NodeDataManager.h"

class COpenGL : public QGLWidget
{
    Q_OBJECT

public:
    COpenGL(QWidget *parent = 0, const char *aName = 0, bool aFullScreen = false);
    ~COpenGL();
   
    void drawSphere(GLfloat aX, GLfloat aY, GLfloat aZ);  //������;

protected:
    void initializeGL();                    //��ʼ��OpenGL����;
    void paintGL();                         //����OpenGL���ڣ��и��¾ͻ����;
    void resizeGL( int width, int height ); //�����ڳ���仯���ͻ����;
    void keyPressEvent(QKeyEvent *e);       //��������;
    void mousePressEvent(QMouseEvent *e);   //������¼�;
    void mouseMoveEvent(QMouseEvent *e);    //����ƶ��¼�;
    void mouseReleaseEvent(QMouseEvent *e); //����ͷ��¼�;
    void wheelEvent(QWheelEvent *e);        //�����¼�;

    void timerEvent(QTimerEvent *t);        //��ʱ��;

    void RotateViewPoint();                 //�������ת�ӵ�;
    void dispalyLable(SNodeInfo &aNI);       //�Ƿ���ʾ�ڵ��ǩ;
protected slots:
    void slot_fishEyes(bool aFishEyes);       //����;
    void slot_algorithmFinished(int);         //�㷨��������;
    void slot_algorithmBegin(SParamPack aP);  //�㷨��ʼ����ʼˢ��ͼ��;
    void slot_lableDisplay(bool aDisplay);    //������ʾ�ڵ��ǩ;
signals:
     void signal_closedWin(int);              //�رմ��ڣ�����Ϊ����ID,Ϊ������չ��׼��;
private:
    bool        m_FullScreen;   //�Ƿ�ȫ��;
    bool        m_Light;        //�Ƿ�򿪹�Դ;
    double      m_Rotate;       //��ת�Ƕ�;

    GLfloat     m_ZPos;         //���;
    GLfloat     m_XPos;         //X����;
    GLfloat     m_YPos;         //Y����;

    GLfloat     m_Scale;        //���ſ���;
//��������ת;
private:
    QPoint      m_StartPoint;     //��¼��갴�µĵ�;
    QPoint      m_EndPoint;       //����ƶ������еĵ�;

    //gluLookAt�����е�һ�����������������;
    GLdouble    m_eyex;
    GLdouble    m_eyey;
    GLdouble    m_eyez;

    GLdouble    m_upx;
    GLdouble    m_upy;
    GLdouble    m_upz ;

    double       m_CurrentAngleZ;   //��ǰ��Z��ļн�;
    double       m_CurrentAngleY;   //��ǰ��Y��ļн�;

    double       m_LastAngleZ;      //��һ����Z��ļн�;
    double       m_LastAngleY;      //��һ����Y��ļн�;

private:
    double       m_SphereRad;       //��İ뾶;
    uint         m_NodesNum;        //�ڵ���;
    uint         m_EdgesNum;        //����;
    int          m_TimerId;         //��ʱ��ID;
    std::vector<SNodeInfo> *p;      //ȡ�ڵ�����; 
    bool         m_DisplayLable;    //�Ƿ���ʾ�ڵ��ǩ;
};

#endif // OPENGLTEST_H
