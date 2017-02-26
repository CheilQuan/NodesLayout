#ifndef NODESDEGREE_H
#define NODESDEGREE_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <vector>
#include "ui_DegreeInput.h"
#include "StructDefine.h"

class CNodesDegreeDialog : public QDialog, public Ui_Form
{
  Q_OBJECT

public:
    CNodesDegreeDialog(QWidget *parent);
    ~CNodesDegreeDialog();

public:
    const std::vector<SNodesDegree> &getNodeDegree(); //��ȡ�ڵ����Ϣ; 
    void clearNodesDegree();          //����ڵ����Ϣ;
private:
    void setNodesDegree();            //���ýڵ����Ϣ;
    const uint calcNodesNum();        //����ڵ���;
   
protected slots:
    void slot_okClicked(bool);        //ȷ����ť;
    void slot_cancelClicked(bool);    //ȡ��;

signals:
    void signal_degreeEditOver(bool); //�ڵ�ȱ༭���;

private:
    std::vector<SNodesDegree>   m_NodesDegree;//�ڵ���Լ�����Ϣ;
    QStringList                *m_NodesList;  //�ڵ��ַ�����;
};

#endif // NODESDEGREE_H
