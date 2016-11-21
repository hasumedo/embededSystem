/**
  ******************************************************************************
  * @file    awe_int_lock.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ��ܵ��ж���
  ******************************************************************************
  * @attention
  *    �ж�����ҪΪ����ٽ�������
	*
	*
  ******************************************************************************
  */
#include "awe_fm_port.h"
	
#ifndef   AWE_INT_LOCK_H
#define   AWE_INT_LOCK_H

/****************************************************************************/
/*!     ���洢�ж�״̬���ж���    */
/**
* @description
* 		�ò��Ե���Ҫ�ŵ��ǿ���Ƕ���ٽ���������
*     
*/
#ifdef   AWE_INT_KEY_LOCK            
		/*!     ���ж���    */
		#define  AWE_INT_LOCK(key_)  				 do{  \
																					key_ = get_int_status();       \
																					int_lock();                    \
																					}while(0)                         

		/*!     ���ж���    */		
		#define AWE_INT_UNLOCK(key_)          set_int_status(key_)

#else
		/*!     ���������ж���        */
		/*!     ���ж���    */
		#define  AWE_INT_LOCK(key_)           int_lock()                   
																					
		/*!     ���ж���    */		
		#define AWE_INT_UNLOCK(key_)          set_int_status()      

#endif
																				
																				
																				
																				

#endif
																			
																			




