/**
  ******************************************************************************
  * @file    awe_fm.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  合作式内核
  ******************************************************************************
  * @attention
  *     该部分为框架内核
	*
	*
  ******************************************************************************
  */
	
#include "awe_fm.h"	
#include "awe_Aobj.h"

/*************************************************************/
/*! 内核初始化 */		
void AFM_init(void)
{
}

/*************************************************************/
/*! 内核停止 */		
void AFM_stop(void) 
{
}



/*************************************************************/
/*! 运行内核 */		
int AFM_run(void)
{
		AObj *obj; 
	  const AEvt *e;
		AWE_INT_LOCK_KEY_  
	
		AFM_startup();
		while(1)
		{
			AWE_INT_LOCK_();               		       /*  加锁操作  */	
			if (Is_AobjTable_set())
			{
 				obj = PrioReady_findMax();
				AWE_INT_UNLOCK_();
 				e = OBJ_QEVT_GET_(&(obj->qEvent), obj->prio); /* 从对象中获取事件 */
 				ACTIVE_OBJECT_DISPATCH_(&obj->super, e); /* 派发事件到对象 */
				AFM_gc((AEvt *)e); /* 回收动态 */
			}
			else
			{
				AFM_onIdle(); 
			}
		}
	
}



/*************************************************************/
/*! 内核回收事件 */		
void AFM_gc(AEvt *e)
{
	
}



