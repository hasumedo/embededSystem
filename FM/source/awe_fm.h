/**
  ******************************************************************************
  * @file    awe_fm.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ����ʽ�ں�ͷ�ļ�
  ******************************************************************************
  * @attention
  *     ���ļ������˺���ʽ�ں��ṩ�����Ľӿ�
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
/*! �ں˺��¼�����֮��Ľӿ� */		
/*! �ȴ��¼����� */		
#define         EQUEUE_WAIT_EVT_(me_)	
	
/*! �¼�����Ϊ�� ��������� */		
#define        	EQUEUE_CLEAR_EVT_(prio_)          Clear_AObj_SetTable(prio_)   
			

/*! �¼����в���ʱ�� ��������� */	
#define        	EQUEUE_INSERT_EVT_(prio_)         Set_AObj_SetTable(prio_)
	
	
/*************************************************************/
/*! �ں˺��ڴ��֮��Ľӿ� */		
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
	
	
	
	

