/**
  ******************************************************************************
  * @file    awe_table.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ���ȼ���;�����ͷ�ļ�
  ******************************************************************************
  * @attention
  *     ���ȼ���;�����
	*
	*
	*
  ******************************************************************************
  */
	

#ifndef   AF_TABLE_H_
#define   AF_TABLE_H_

#include "awe_Aobj.h"

void  PrioTable_add(AObj * me, uint8_t prio_);


#define  AF_add(me_, prio_)             PrioTable_add(me_, prio)            /*�Ѷ����������*/
void  Set_AObj_SetTable(uint8_t prio_);                                     /*���ö�Ӧ���ȼ��ľ�����*/
void  Clear_AObj_SetTable(uint8_t prio_);                                   /*���ö�Ӧ���ȼ��ľ�����*/
uint8_t  Is_AobjTable_set(void);                                            /*�������Ƿ���׼���õĶ��� */
AObj *   PrioReady_findMax(void);                                           /*�ҵ�������ȼ�׼���õĶ���*/



#endif



