/**
  ******************************************************************************
  * @file    aqueue.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  事件环形队列头文件
  ******************************************************************************
  * @attention
  *     这里的事件队列为环形队列
	*
	*
	*
  ******************************************************************************
  */
#include "awe_ep.h"	
#include "awe_pal.h" 	
	
	
#ifndef   A_QUEUE_H_
#define   A_QUEUE_H_
	
    


/**************************************************************/
/*! 队列事件的取值大小，范围值是1,2,4个字节，默认值是1*/	
/**
* @description
* 该宏指令可以在port文件中（）配置 
*/
#ifndef      AEVTQUEUE_SIZE
	#define    AEVTQUEUE_SIZE      1	         /*如果没有定义，默认定义为1个字节*/	
#endif 	
	
	
#if (AEVTQUEUE_SIZE == 1)
	typedef    uint8_t         AQueueCtr;       
#elif  (AEVTQUEUE_SIZE == 2)
	typedef    uint16_t        AQueueCtr;
#elif  (AEVTQUEUE_SIZE == 4)
	typedef    uint32_t        AQueueCtr;
#else
  #error  "AEvtQueue size is outof range!"
#endif
	
	
	
/*************************************************************/	
/*! 事件队列结构体的定义 */
typedef struct AEvtQueueTag
{
		AEvt const * frontEvent;                  /*当前缓冲区头部要出去的指针 */
		AEvt const ** ring;                       /*指向环形队列（数组） */
		
		AQueueCtr end;                            /*队列底部的偏移量，队列长度 */ 
		AQueueCtr head;                           /*缓冲头的偏移 */
		AQueueCtr tail;                           /*缓冲尾的偏移 */
		AQueueCtr freeEvt;                        /*缓冲区剩余事件的数量 */
	
}AEvtQueue;


	
/* 接口 */	
/*! 队列初始化函数 */
void AEvtQueue_init(AEvtQueue *me, AEvt const *qSto[], AQueueCtr qLen);
	

/*! 从事件队列中获取 */
AEvt const *AEvtQueue_get_(AEvtQueue * me, uint8_t prio);


/*! 向事件队列中插入队列 */
void AEvtQueue_post_(AEvtQueue *me, AEvt const *e, uint8_t prio);

#define  Is_QueueFull(me_)                  ((me_->freeEvt== 0) ? 1 : 0)




#endif
	
	
	
	

