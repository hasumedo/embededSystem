/**
  ******************************************************************************
  * @file    awe_pal.h
  * @author  
  * @version V1.0
  * @date    
  * @brief 抽象平台
  ******************************************************************************
  * @attention
  *    平台定制（里面的都是固定代码。不可改动，只不过应对不同平台做了不同策略）
	*    详细移植请改port
	*
  ******************************************************************************
  */

#ifndef   AWE_PAL_H
#define   AWE_PAL_H

#include "awe_int_lock.h"


	/*******************************************************/
/*!   中断锁      */  
/**
* @usage
*      QF_INT_LOCK_KEY_
*           ...
*      QF_INT_LOCK_();
*         临界代码
*      QF_INT_UNLOCK_();   
*
*/    
#ifndef AWE_INT_KEY_LOCK
/*!     无条件的中断锁        */
	#define    AWE_INT_LOCK_KEY_
	#define    AWE_INT_LOCK_()        AWE_INT_LOCK()
	#define    AWE_INT_UNLOCK_()      AWE_INT_UNLOCK()  
	
#else
/*!     带存储中断状态的中断锁    */
	#define    AWE_INT_LOCK_KEY_      unsigned int  key_;
	#define    AWE_INT_LOCK_()        AWE_INT_LOCK(key_)
	#define    AWE_INT_UNLOCK_()      AWE_INT_UNLOCK(key_)  
	
#endif





#endif

