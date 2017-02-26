#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "StructDefine.h"
#include "OpenGL.h"
#include <QString>
#include <QVBoxLayout>

class CFRAlgorithm;
class CSetingDialog;
class CNodesDegreeDialog;

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

public:
    void keyPressEvent(QKeyEvent *e);       //���ذ����¼�;
public slots:
    void slot_newFile(bool aClicked);       //�½��ļ�,����һ���ڵ����ݰ�;
    void slot_openFile(bool aClicked);      //���ļ�;
    void slot_savePic(bool aClicked);       //���沼�ֽ��ͼƬ;
    void slot_saveDoc(bool aClicked);       //���沼�ֽ���ĵ�;
    void slot_exit(bool aClicked);          //�˳�����;
 //   void slot_algorithmSet(bool aClicked);  //���ò����㷨�����;
    void slot_degreeEdit(bool aClicked);    //�����б༭;  
    void slot_beginLayout(bool aClicked);   //��ʼ�ڵ㲼��(ֻ�ǽ��벼�����ã��Լ�׼��ǰ�ڹ������������Ʋ�����/��άͼ��;
    void slot_algoFinished(int aAlgorId);   //�㷨�������(aAlgorIdΪ���ֽ����㷨��ID,���ں��湦����չ�����ƶ���ͬʱ����);
    void slot_stopLayout(bool);             //��ͣ����;
    void slot_continueLayout(bool);         //�������֣�ֻ�ǽ��벼�����ã��Լ�׼��ǰ�ڹ�����;
    void slot_runAlgorithm(bool);           //��ʼ�����㷨;
    void slot_fishEyes(bool);               //����Ч������ʱδ���ã�����˼����������;
    void slot_relayout(bool);               //���¿�ʼ����;
    void slot_openGLWinClosed(int aWinId);  //opengl���ڹر�;
    void slot_fullScreen(bool);             //ȫ��/�����л�;
    void slot_degreeEditOver(bool);         //�ڵ����Ϣ�༭���;
    void slot_lableDisplay(bool);           //��ʾ�ڵ��ǩ;
signals:
    void signal_runAlgorithm(SParamPack aData);    //���俪ʼ�㷨�ź�,aData���д�ȷ��;
    void signal_algFinished(int aAlgorId);  //�㷨�����ź�(aAlgorIdΪ���ֽ����㷨��ID);    
    void signal_fishEyes(bool);             //�����ź�;
    void signal_lableDisplay(bool);         //��ʾ�ڵ��ǩ;
private:
    void test();                            //���ڲ��Բ��ִ���;
    void paramSeting();                     //�Ӳ������öԻ����ȡ�㷨����;
    void openglConfig();                    //��OpenGL��������;
private:
    Ui::CMainWindowClass  m_ui;             //������;
    CSetingDialog        *m_SetingDialog;   //��������;
    CNodesDegreeDialog         *m_DegreeDialog;   //�ڵ�ȱ༭����;
    QString               m_FilePath;       //�½��ļ�·��;
    CFRAlgorithm         *m_Algorithm;      //�㷨��; 
    QThread              *m_AlgoThread;     //�㷨�����߳�;
    bool                  m_FullScreen;     //�л�ȫ��;
    COpenGL              *m_OpenGL;         //��ʱ������ͼ���������źŴ���,�ȴ�֮����չΪ�̳߳غ����ݳ�;
    bool                  m_fishEyes;       //�Ƿ�����Ч��;
    bool                  m_displayLable;   //�Ƿ���ʾ�ڵ��ǩ;
};

#endif // MAINWINDOW_H
