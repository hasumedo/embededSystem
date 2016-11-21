/**
  ******************************************************************************
  * @file    awe_table.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  优先级表和就绪表头文件
  ******************************************************************************
  * @attention
  *     优先级表和就绪表
	*
	*
	*
  ******************************************************************************
  */
	

#ifndef   AF_TABLE_H_
#define   AF_TABLE_H_

#include "awe_Aobj.h"

void  PrioTable_add(AObj * me, uint8_t prio_);


#define  AF_add(me_, prio_)             PrioTable_add(me_, prio)            /*把对象添加入框架*/
void  Set_AObj_SetTable(uint8_t prio_);                                     /*设置对应优先级的就绪表*/
void  Clear_AObj_SetTable(uint8_t prio_);                                   /*设置对应优先级的就绪表*/
uint8_t  Is_AobjTable_set(void);                                            /*就绪表是否有准备好的对象 */
AObj *   PrioReady_findMax(void);                                           /*找到最大优先级准备好的对象*/



#endif



