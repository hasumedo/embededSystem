/**
  ******************************************************************************
  * @file   awe_AObj.h
  * @author  
  * @version V1.0
  * @date    
  * @brief �û�����������λͷ�ļ�
  ******************************************************************************
  * @attention
  *    �û�����ÿ����������Ŀɴ���һ��������Ϊ������λ���в�����
	*    һ�������Ķ�������¼����У�����ӵ��һ��Ψһ�����ȼ�
	*    ������Է����¼��������¼��Ĺ���
	*    �ǰ�EP��ܽ��н�һ����װ�Ľ��
	*		 ����ÿ�������ĳ�����˵���������������64��
	*
  ******************************************************************************
  */
#include   "aqueue.h"
#include   "awe_ep.h"	
#include   "awe_table.h"	

#ifndef   AWE_AOBJECT_H
#define   AWE_AOBJECT_H	


/**************************************************************/
/*         �̳е��¼����       */



#define     ACTIVE_OBJECT_                            AFsm

#define     ACTIVE_OBJECT_CTOR_(me_, state_table_, initial_, n_signals, n_states, method)     \
																											AFsm_ctor(&me->super, (AStateHandler *)state_table,\
																											(AStateHandler)initial, max_sig, max_state, method)
																											
#define     ACTIVE_OBJECT_INIT_(me_, e_)              AFsm_init((AFsm *)me_)

#define     ACTIVE_OBJECT_DISPATCH_(me_, e)           AFsm_dispatch(me_, e)                   



#define     A_EQUEUE_EVT_  					                  AEvtQueue 

#define     OBJ_QEVT_INIT(me_, qSto_, qlen_)          AEvtQueue_init(me_, qSto_, qlen_) 
#define     OBJ_QEVT_GET_(me_, prio_)                 AEvtQueue_get_(me_, prio_)
#define     OBJ_QEVT_INSERT_(me_, e, prio_)           AEvtQueue_post_(me_, e, prio_)
#define     OBJ_IS_QUEUE_Full(me_)                    Is_QueueFull(me_)




/**************************************************************/
/*         �����Ļ����       */
typedef  struct AObjTag
{
		ACTIVE_OBJECT_   super;                 //�̳е��¼�������
		A_EQUEUE_EVT_    qEvent;                //ÿ�������Դ����¼�����
		uint8_t          prio;                  //�������ȼ���Ψһ��ÿһ���������ظ�
}AObj;



/**************************************************************/
/*         ���ýӿ�      */
void Aobj_ctor(AObj *me, AStateHandler *state_table, AStateHandler  initial, 
                     ASignal  max_sig, uint8_t max_state, uint8_t method);

void Aobj_start(AObj *me, uint8_t prio,
										AEvt const *qSto[], uint32_t qLen,
										void *stkSto, uint32_t stkSize,
										AEvt const *e);

void AObj_sendEvt(AObj *me, AEvt const * const e, AObj *aim);

AEvt const *AObj_getEvt_(AObj *me);


#endif

