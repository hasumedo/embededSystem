/**
  ******************************************************************************
  * @file    aqueue.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  �¼����ζ���ͷ�ļ�
  ******************************************************************************
  * @attention
  *     ������¼�����Ϊ���ζ���
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
/*! �����¼���ȡֵ��С����Χֵ��1,2,4���ֽڣ�Ĭ��ֵ��1*/	
/**
* @description
* �ú�ָ�������port�ļ��У������� 
*/
#ifndef      AEVTQUEUE_SIZE
	#define    AEVTQUEUE_SIZE      1	         /*���û�ж��壬Ĭ�϶���Ϊ1���ֽ�*/	
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
/*! �¼����нṹ��Ķ��� */
typedef struct AEvtQueueTag
{
		AEvt const * frontEvent;                  /*��ǰ������ͷ��Ҫ��ȥ��ָ�� */
		AEvt const ** ring;                       /*ָ���ζ��У����飩 */
		
		AQueueCtr end;                            /*���еײ���ƫ���������г��� */ 
		AQueueCtr head;                           /*����ͷ��ƫ�� */
		AQueueCtr tail;                           /*����β��ƫ�� */
		AQueueCtr freeEvt;                        /*������ʣ���¼������� */
	
}AEvtQueue;


	
/* �ӿ� */	
/*! ���г�ʼ������ */
void AEvtQueue_init(AEvtQueue *me, AEvt const *qSto[], AQueueCtr qLen);
	

/*! ���¼������л�ȡ */
AEvt const *AEvtQueue_get_(AEvtQueue * me, uint8_t prio);


/*! ���¼������в������ */
void AEvtQueue_post_(AEvtQueue *me, AEvt const *e, uint8_t prio);

#define  Is_QueueFull(me_)                  ((me_->freeEvt== 0) ? 1 : 0)




#endif
	
	
	
	

