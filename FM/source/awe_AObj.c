/**
  ******************************************************************************
  * @file   awe_AObj.c
  * @author  
  * @version V1.0
  * @date    
  * @brief 用户创建基本单位
  ******************************************************************************
  * @attention
  *    用户对于每个单独整体的可创建一个对象作为基本单位进行操作。
	*    一个独立的对象带有事件队列，并且拥有一个唯一的优先级
	*    对象可以发送事件，处理事件的功能
	*    是把EP框架进行进一步封装的结果
	*		 对于每个单独的程序来说，对象个数不超过64个
	*
  ******************************************************************************
  */
	
#include "awe_Aobj.h"


/**************************************************************/
/*         创建对象      */
void Aobj_ctor(AObj *me, AStateHandler *state_table, AStateHandler  initial, 
                     ASignal  max_sig, uint8_t max_state, uint8_t method)
{
		ACTIVE_OBJECT_CTOR_(me, (AStateHandler *)state_table,
									(AStateHandler)initial, max_sig, max_state, method);

}
	



/**************************************************************/
/*         活动对象开始       */
void Aobj_start(AObj *me, uint8_t prio,
										AEvt const *qSto[], uint32_t qLen,
										void *stkSto, uint32_t stkSize,
										AEvt const *e)
{
		//Assert();   /*优先级检查，保证优先级的唯一性*/
		me->prio = prio; /* 设置优先级 */
    AF_add(me, prio);        /*框架中添加对象 */
 		ACTIVE_OBJECT_INIT_(me, e); /* 执行初始化（根据自己的定义的框架） */
		// 初始化事件队列
		OBJ_QEVT_INIT(&(me->qEvent), qSto, qLen);
	
}
	



/**************************************************************/
/*         发送事件到目标对象       */
void AObj_sendEvt(AObj *me, AEvt const * const e, AObj *aim)
{
	AWE_INT_LOCK_KEY_
	
	//无目标 assert()
	
	AWE_INT_LOCK_();               		       /*  加锁操作  */	
	if (!OBJ_IS_QUEUE_Full((&(aim->qEvent))))            /* 判断事件队列是否满 */
	{
		OBJ_QEVT_INSERT_(&(aim->qEvent), e, aim->prio);  /*插入事件*/
	}
	AWE_INT_UNLOCK_();              /* 解锁 */
	
}





/**************************************************************/
/*         获得事件队列中最上端的事件       */
AEvt const *AObj_getEvt_(AObj *me)
{	
		return OBJ_QEVT_GET_(&(me->qEvent), me->prio);
}





