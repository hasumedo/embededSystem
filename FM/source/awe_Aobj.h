/**
  ******************************************************************************
  * @file   awe_AObj.h
  * @author  
  * @version V1.0
  * @date    
  * @brief 用户创建基本单位头文件
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
#include   "aqueue.h"
#include   "awe_ep.h"	
#include   "awe_table.h"	

#ifndef   AWE_AOBJECT_H
#define   AWE_AOBJECT_H	


/**************************************************************/
/*         继承的事件框架       */



#define     ACTIVE_OBJECT_                            AFsm

#define     ACTIVE_OBJECT_CTOR_(me_, state_table_, initial_, n_signals, n_states, method)     \
																											AFsm_ctor(&me->super, (AStateHandler *)state_table,\
																											(AStateHandler)initial, max_sig, max_state, method)
																											
#define     ACTIVE_OBJECT_INIT_(me_, e_)              AFsm_init((AFsm *)me_)

#define     ACTIVE_OBJECT_DISPATCH_(me_, e)           AFsm_dispatch(me_, e)                   



#define     A_EQUEUE_EVT_  					                  AEvtQueue 

#define     OBJ_QEVT_INIT(me_, qSto_, qlen_)          AEvtQueue_init(me_, qSto_, qlen_) 
#define     OBJ_QEVT_GET_(me_, prio_)                 AEvtQueue_get_(me_, prio_)
#define     OBJ_QEVT_INSERT_(me_, e, prio_)           AEvtQueue_post_(me_, e, prio_)
#define     OBJ_IS_QUEUE_Full(me_)                    Is_QueueFull(me_)




/**************************************************************/
/*         单独的活动对象       */
typedef  struct AObjTag
{
		ACTIVE_OBJECT_   super;                 //继承的事件处理框架
		A_EQUEUE_EVT_    qEvent;                //每个对象自带的事件队列
		uint8_t          prio;                  //对象优先级，唯一且每一个都不能重复
}AObj;



/**************************************************************/
/*         调用接口      */
void Aobj_ctor(AObj *me, AStateHandler *state_table, AStateHandler  initial, 
                     ASignal  max_sig, uint8_t max_state, uint8_t method);

void Aobj_start(AObj *me, uint8_t prio,
										AEvt const *qSto[], uint32_t qLen,
										void *stkSto, uint32_t stkSize,
										AEvt const *e);

void AObj_sendEvt(AObj *me, AEvt const * const e, AObj *aim);

AEvt const *AObj_getEvt_(AObj *me);


#endif

