/**
  ******************************************************************************
  * @file    aqueue.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  事件队列
  ******************************************************************************
  * @attention
  *     这里的事件队列为环形队列
	*
	*
	*
  ******************************************************************************
  */
	
#include  "aqueue.h"
#include "awe_fm.h"  


/*! 事件队列初始化函数 */
void AEvtQueue_init(AEvtQueue *me, AEvt const *qSto[], AQueueCtr qLen)
{
		me->frontEvent = (AEvt *)0;
		me->ring = &qSto[0];
		me->end = qLen;
		me->head = (AQueueCtr)0;
		me->tail = (AQueueCtr)0;
		me->freeEvt = qLen;
	
}
	
	
	
	
/* 从事件队列中获取事件 FIFO先入先出，出尾部*/
/*  改成这样：事件队列不阻塞,采用阻塞的方式？？？？？
*		考虑2点：1.队列为空的情况
*           2.尾部在整个完整队列的第一个
*/
AEvt const *AEvtQueue_get_(AEvtQueue * me, uint8_t prio)
{
		AEvt const *e;
		AWE_INT_LOCK_KEY_         
	
		AWE_INT_LOCK_();               		       /*  加锁操作  */		

		EQUEUE_WAIT_EVT_(me);                     /*阻塞获取事件*/
	
		e = me->frontEvent;			                 /* 读取数据 */
			
		if (me->freeEvt != me->end)         /* 是否队列为空 */
		{					
			if (me->head == (AQueueCtr)0)          /* 尾部在数组队列的第一个的情况 */
			{
				me->head = me->end;
			}
			--me->head;
			++me->freeEvt;		   
		  
			me->frontEvent = me->ring[me->head];   /* 移除头数据 */	
		}
		else
		{
			me->frontEvent = (AEvt *)0;
		} 

		EQUEUE_CLEAR_EVT_(prio);                   /*队列为空，清除就绪表*/	
		AWE_INT_UNLOCK_();                       /* 解锁操作  */	
		return e;
	
}
	
	
	
	
	
	
	
/* 向事件队列中插入队列 */
/* 注意锁和直接发送给带来的影响
*   队列是否慢
*/
void AEvtQueue_post_(AEvtQueue *me, AEvt const *e, uint8_t prio)
{
		AWE_INT_LOCK_KEY_
		AWE_INT_LOCK_();           /*  加锁操作  */	
	
		if (me->frontEvent == (AEvt *)0)   /* 是否为空队列 */
		{ 
				EQUEUE_INSERT_EVT_(prio);             /* 直接发送调用处理事件信号 */
				me->frontEvent = e;   	 
				++me->head;							
				--me->freeEvt;
		}
		else 
		{
				//ASSERT(me->eQueue.nFree != (QEQueueCtr)0);
				if (me->freeEvt < me->end)                      /* 是否队列已满 */
				{
						if (me->tail == (AQueueCtr)0)    /* 是否插入事件在队列数组*/
						{ 
								me->head = me->end;                       /* 指向尾部 */
						}
						--me->tail;
						--me->freeEvt; 
						
						/* 向环形队列直接插入事件 */
						me->ring[me->tail] = e;
				}
				else
				{
					/*事件队列满，选择丢失不处理*/
				}
		}			
			
		AWE_INT_UNLOCK_();             /* 解锁操作  */	
		
}
	
	
	
	
	


	
