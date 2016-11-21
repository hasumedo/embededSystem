/**
  ******************************************************************************
  * @file    awe_fm_port.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ����ں���ֲ�ӿ�ͷ�ļ�
  ******************************************************************************
  * @attention
  *    ���ݶ���ƽ̨��ͬʵ�ֲ�ͬ��ֲʵ�֡�
	*	  	����¼������ֵ�
	*
	*
  ******************************************************************************
  */
	
#include "sys.h"

#ifndef   AWE_FM_PORT_H
#define   AWE_FM_PORT_H
	
/*******************************************************/
/*!   �ٽ��ж�    */
#define int_lock(key)                   __set_PRIMASK(1)
#define set_int_status(key)  	          __set_PRIMASK(0)
	

void IdleHandle(void);

#include  "awe_ep_port.h"
#include  "awe_fm.h"
#include  "awe_AObj.h"
	
	
	
#endif


	
	

