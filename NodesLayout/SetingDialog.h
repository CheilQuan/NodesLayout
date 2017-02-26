#ifndef SETINGDIALOG_H
#define SETINGDIALOG_H

#include <QDialog>
#include "ui_ParamSetDialog.h"
#include "StructDefine.h"

class CSetingDialog : public QDialog, public Ui_Dialog
{
  Q_OBJECT

public:
    CSetingDialog(QWidget *parent);
    ~CSetingDialog();
    
protected slots:
    void slot_paramSeting(bool);
signals:
    void signal_okClicked(bool);      //���ȷ����ť;
public:
    SParamPack     m_ParamPack;       //�������ý��;
};

#endif // SETINGDIALOG_H
