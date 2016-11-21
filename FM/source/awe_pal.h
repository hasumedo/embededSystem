/**
  ******************************************************************************
  * @file    awe_pal.h
  * @author  
  * @version V1.0
  * @date    
  * @brief ����ƽ̨
  ******************************************************************************
  * @attention
  *    ƽ̨���ƣ�����Ķ��ǹ̶����롣���ɸĶ���ֻ����Ӧ�Բ�ͬƽ̨���˲�ͬ���ԣ�
	*    ��ϸ��ֲ���port
	*
  ******************************************************************************
  */

#ifndef   AWE_PAL_H
#define   AWE_PAL_H

#include "awe_int_lock.h"


	/*******************************************************/
/*!   �ж���      */  
/**
* @usage
*      QF_INT_LOCK_KEY_
*           ...
*      QF_INT_LOCK_();
*         �ٽ����
*      QF_INT_UNLOCK_();   
*
*/    
#ifndef AWE_INT_KEY_LOCK
/*!     ���������ж���        */
	#define    AWE_INT_LOCK_KEY_
	#define    AWE_INT_LOCK_()        AWE_INT_LOCK()
	#define    AWE_INT_UNLOCK_()      AWE_INT_UNLOCK()  
	
#else
/*!     ���洢�ж�״̬���ж���    */
	#define    AWE_INT_LOCK_KEY_      unsigned int  key_;
	#define    AWE_INT_LOCK_()        AWE_INT_LOCK(key_)
	#define    AWE_INT_UNLOCK_()      AWE_INT_UNLOCK(key_)  
	
#endif





#endif

