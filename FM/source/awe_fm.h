/**
  ******************************************************************************
  * @file    awe_fm.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  合作式内核头文件
  ******************************************************************************
  * @attention
  *     该文件定义了合作式内核提供给外界的接口
	*
	*
  ******************************************************************************
  */
#include  "aqueue.h"
#include  "awe_mpool.h"
#include   "awe_table.h"	
#include "awe_fm_port.h"


#ifndef   AWE_FM_H
#define   AWE_FM_H



/*************************************************************/
/*! 内核和事件队列之间的接口 */		
/*! 等待事件队列 */		
#define         EQUEUE_WAIT_EVT_(me_)	
	
/*! 事件队列为空 清除就绪表 */		
#define        	EQUEUE_CLEAR_EVT_(prio_)          Clear_AObj_SetTable(prio_)   
			

/*! 事件队列插入时间 插入就绪表 */	
#define        	EQUEUE_INSERT_EVT_(prio_)         Set_AObj_SetTable(prio_)
	
	
/*************************************************************/
/*! 内核和内存池之间的接口 */		
#define         EVT_POOL_TYPE_                    AMPool
#define         EVT_POOL_INIT_(me_, sto_, poolSize_,blockSize_)   \
																						  		AMPool_init(me_, sto_, poolSize_,blockSize_)
#define         EVT_POOL_GET_()  




void AFM_init(void);
void AFM_stop(void);
int AFM_run(void);
void AFM_gc(AEvt *e);
#define   AFM_startup() 
#define   AFM_onIdle()       IdleHandle()


#endif	
	
	
	
	

