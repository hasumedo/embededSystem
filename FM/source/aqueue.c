/**
  ******************************************************************************
  * @file    aqueue.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  �¼�����
  ******************************************************************************
  * @attention
  *     ������¼�����Ϊ���ζ���
	*
	*
	*
  ******************************************************************************
  */
	
#include  "aqueue.h"
#include "awe_fm.h"  


/*! �¼����г�ʼ������ */
void AEvtQueue_init(AEvtQueue *me, AEvt const *qSto[], AQueueCtr qLen)
{
		me->frontEvent = (AEvt *)0;
		me->ring = &qSto[0];
		me->end = qLen;
		me->head = (AQueueCtr)0;
		me->tail = (AQueueCtr)0;
		me->freeEvt = qLen;
	
}
	
	
	
	
/* ���¼������л�ȡ�¼� FIFO�����ȳ�����β��*/
/*  �ĳ��������¼����в�����,���������ķ�ʽ����������
*		����2�㣺1.����Ϊ�յ����
*           2.β���������������еĵ�һ��
*/
AEvt const *AEvtQueue_get_(AEvtQueue * me, uint8_t prio)
{
		AEvt const *e;
		AWE_INT_LOCK_KEY_         
	
		AWE_INT_LOCK_();               		       /*  ��������  */		

		EQUEUE_WAIT_EVT_(me);                     /*������ȡ�¼�*/
	
		e = me->frontEvent;			                 /* ��ȡ���� */
			
		if (me->freeEvt != me->end)         /* �Ƿ����Ϊ�� */
		{					
			if (me->head == (AQueueCtr)0)          /* β����������еĵ�һ������� */
			{
				me->head = me->end;
			}
			--me->head;
			++me->freeEvt;		   
		  
			me->frontEvent = me->ring[me->head];   /* �Ƴ�ͷ���� */	
		}
		else
		{
			me->frontEvent = (AEvt *)0;
		} 

		EQUEUE_CLEAR_EVT_(prio);                   /*����Ϊ�գ����������*/	
		AWE_INT_UNLOCK_();                       /* ��������  */	
		return e;
	
}
	
	
	
	
	
	
	
/* ���¼������в������ */
/* ע������ֱ�ӷ��͸�������Ӱ��
*   �����Ƿ���
*/
void AEvtQueue_post_(AEvtQueue *me, AEvt const *e, uint8_t prio)
{
		AWE_INT_LOCK_KEY_
		AWE_INT_LOCK_();           /*  ��������  */	
	
		if (me->frontEvent == (AEvt *)0)   /* �Ƿ�Ϊ�ն��� */
		{ 
				EQUEUE_INSERT_EVT_(prio);             /* ֱ�ӷ��͵��ô����¼��ź� */
				me->frontEvent = e;   	 
				++me->head;							
				--me->freeEvt;
		}
		else 
		{
				//ASSERT(me->eQueue.nFree != (QEQueueCtr)0);
				if (me->freeEvt < me->end)                      /* �Ƿ�������� */
				{
						if (me->tail == (AQueueCtr)0)    /* �Ƿ�����¼��ڶ�������*/
						{ 
								me->head = me->end;                       /* ָ��β�� */
						}
						--me->tail;
						--me->freeEvt; 
						
						/* ���ζ���ֱ�Ӳ����¼� */
						me->ring[me->tail] = e;
				}
				else
				{
					/*�¼���������ѡ��ʧ������*/
				}
		}			
			
		AWE_INT_UNLOCK_();             /* ��������  */	
		
}
	
	
	
	
	


	
