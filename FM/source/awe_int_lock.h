/**
  ******************************************************************************
  * @file    awe_int_lock.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  框架的中断锁
  ******************************************************************************
  * @attention
  *    中断锁主要为解决临界区问题
	*
	*
  ******************************************************************************
  */
#include "awe_fm_port.h"
	
#ifndef   AWE_INT_LOCK_H
#define   AWE_INT_LOCK_H

/****************************************************************************/
/*!     带存储中断状态的中断锁    */
/**
* @description
* 		该策略的主要优点是可以嵌套临界区的能力
*     
*/
#ifdef   AWE_INT_KEY_LOCK            
		/*!     加中断锁    */
		#define  AWE_INT_LOCK(key_)  				 do{  \
																					key_ = get_int_status();       \
																					int_lock();                    \
																					}while(0)                         

		/*!     解中断锁    */		
		#define AWE_INT_UNLOCK(key_)          set_int_status(key_)

#else
		/*!     无条件的中断锁        */
		/*!     加中断锁    */
		#define  AWE_INT_LOCK(key_)           int_lock()                   
																					
		/*!     解中断锁    */		
		#define AWE_INT_UNLOCK(key_)          set_int_status()      

#endif
																				
																				
																				
																				

#endif
																			
																			




