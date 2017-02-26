#ifndef _TABWIDGET_H_
#define _TABWIDGET_H_

#include <QTabWidget>
#include <QTabBar>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>

class CTabWidget : public QTabWidget
{
  Q_OBJECT

public:
  explicit CTabWidget(QWidget *parent = 0);
  ~CTabWidget(void);

public:
  bool newTab(QWidget *aTargetWin, const QString &aTabName);//�ڱ�ǩ����������±�ǩ;
  
  template<class WidgetType> //�����ڵĺ���ģ��,�ƺ�ֻ����������ʵ��;
  int ifWidgetExist(WidgetType *aTargetType) const
  {
    int cnt = count();

    for (int idx = 0; idx < cnt; ++ idx)
    {
      if (NULL != dynamic_cast<WidgetType *> (widget(idx)))
      {
        return idx;
      }
    }
    return -1;
  }
  bool ifWidgetExist(const QString &aTabName) const;

  static CTabWidget *getInstance();
  static void destroyInstance();
public slots:
  void slot_NewTab();
  void slot_CloseTab(int idx);
  void slot_ShowTab(QAction *a);

protected:
  void resizeEvent(QResizeEvent *e);

private:
  enum EResetFlag{ERF_New, ERF_Close, ERF_Normal, ERF_Special,};
  
  void initTabControl();
  void resetTabBar(EResetFlag flag) const;
  void setListTabs() const;

private:
 
  QToolBar *m_tabControl;
  QAction *m_newTab;
  QAction *m_listTab;
  QWidget *m_paddingWidget;

private:
  static CTabWidget *m_SingleTon;
};

#endif