/**
  ******************************************************************************
  * @file   awe_table.c
  * @author  
  * @version V1.0
  * @date    
  * @brief 优先级表和就绪表
  ******************************************************************************
  * @attention
  *    优先级表和就绪表
  ******************************************************************************
  */
	
#include "awe_table.h"

/******************************************************************************
* @attention
*    管理每个对象的优先级表
*    对象的优先级是唯一的，且默认不为 0（预留给空闲事件）
*    还管理了事件就绪表
*
******************************************************************************/
volatile uint8_t  AObj_SetTable[8];         /* 对象事件就绪表,对应64位，有事件则置位 */	
volatile uint8_t  AObjHightGroup;           /* 对象事件就绪表最高组别，每次在就绪表检查时候更新，无就绪事件用0表示 */	
volatile AObj *   AObj_PrioTable[64];       /* 对象优先级表，创造事件添加到框架是加入 */



/**************************************************************/
/*把对象添加入优先级表*/
void  PrioTable_add(AObj * me, uint8_t prio_)
{
		AObj_PrioTable[prio_-1] = me;
}



/**************************************************************/
 /*设置对应优先级的就绪表*/
void  Set_AObj_SetTable(uint8_t prio_)
{
	  AObj_SetTable[prio_/8] |= 1 << ((prio_-1)%8);    	
}



/**************************************************************/
 /*设置对应优先级的就绪表*/
void  Clear_AObj_SetTable(uint8_t prio_)
{
	AObj_SetTable[prio_/8] &= ~(1 << ((prio_-1)%8));
	
}


/**************************************************************/
/*       就绪表是否有准备好的对象       */
uint8_t  Is_AobjTable_set(void)
{
	uint8_t i = (uint8_t)7;
	while (i != (uint8_t)0)
	{
		if (AObj_SetTable[--i] != (uint8_t)0)
		{
			AObjHightGroup = ++i;
			return i;
		}
	}
	AObjHightGroup = (uint8_t)0;
	return 0;     //检测到无准备好的
}




/**************************************************************/
/*       找到最大优先级准备好的对象       */
AObj * PrioReady_findMax(void)
{
		uint8_t tmp = 0x80, i = 7;
		uint8_t g = AObjHightGroup - 1;
		uint8_t prio = AObj_SetTable[g];
		 /*这里算法可该进*/
		while (tmp != (uint8_t)0)   
		{
			if (tmp & prio)
			{
				return (AObj_PrioTable[8*g+i]);
			}
			tmp = tmp >> 1;
			i--;
		}			
		//assert()  /*出错。无准备好的对象*/
		return (AObj *)0;
}


