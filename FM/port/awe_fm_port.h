/**
  ******************************************************************************
  * @file    awe_fm_port.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  框架内核移植接口头文件
  ******************************************************************************
  * @attention
  *    根据对象平台不同实现不同移植实现。
	*	  	针对事件处理部分的
	*
	*
  ******************************************************************************
  */
	
#include "sys.h"

#ifndef   AWE_FM_PORT_H
#define   AWE_FM_PORT_H
	
/*******************************************************/
/*!   临界中断    */
#define int_lock(key)                   __set_PRIMASK(1)
#define set_int_status(key)  	          __set_PRIMASK(0)
	

void IdleHandle(void);

#include  "awe_ep_port.h"
#include  "awe_fm.h"
#include  "awe_AObj.h"
	
	
	
#endif


	
	

