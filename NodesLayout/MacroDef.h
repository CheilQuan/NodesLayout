#ifndef _MACRODEF_H_
#define _MACRODEF_H_

#include <stddef.h>

/******************�궨��****************/
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))

//��������ָ���Ա������get��set��������;
/*ע�⣺set����ֻ�Ǽ򵥵�ǳ����;*/
#define DEFSETGET(_NAME_, _TYPE_, _ACCESS_RIGHT_) \
_ACCESS_RIGHT_: \
  _TYPE_ m_##_NAME_; \
public: \
  _TYPE_ get##_NAME_(void) const\
{ \
  return m_##_NAME_; \
  }\
  void set##_NAME_(_TYPE_ (aData)) \
{ \
  m_##_NAME_ = (aData); \
  }

//�жϴ����ָ�򵥸������ָ���Ƿ�Ϊ�գ���Ϊ����delete;
#define IF_NOT_NULL_DELETE_s(_Data_) if (NULL != (_Data_)){delete (_Data_); (_Data_) = NULL;}
//�жϴ����ָ����������ָ���Ƿ�Ϊ�գ���Ϊ����delete;
#define IF_NOT_NULL_DELETE_a(_Data_) if (NULL != (_Data_)){delete [](_Data_); (_Data_) = NULL;}

#endif