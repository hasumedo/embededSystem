/**
  ******************************************************************************
  * @file   awe_AObj.c
  * @author  
  * @version V1.0
  * @date    
  * @brief �û�����������λ
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
	
#include "awe_Aobj.h"


/**************************************************************/
/*         ��������      */
void Aobj_ctor(AObj *me, AStateHandler *state_table, AStateHandler  initial, 
                     ASignal  max_sig, uint8_t max_state, uint8_t method)
{
		ACTIVE_OBJECT_CTOR_(me, (AStateHandler *)state_table,
									(AStateHandler)initial, max_sig, max_state, method);

}
	



/**************************************************************/
/*         �����ʼ       */
void Aobj_start(AObj *me, uint8_t prio,
										AEvt const *qSto[], uint32_t qLen,
										void *stkSto, uint32_t stkSize,
										AEvt const *e)
{
		//Assert();   /*���ȼ���飬��֤���ȼ���Ψһ��*/
		me->prio = prio; /* �������ȼ� */
    AF_add(me, prio);        /*�������Ӷ��� */
 		ACTIVE_OBJECT_INIT_(me, e); /* ִ�г�ʼ���������Լ��Ķ���Ŀ�ܣ� */
		// ��ʼ���¼�����
		OBJ_QEVT_INIT(&(me->qEvent), qSto, qLen);
	
}
	



/**************************************************************/
/*         �����¼���Ŀ�����       */
void AObj_sendEvt(AObj *me, AEvt const * const e, AObj *aim)
{
	AWE_INT_LOCK_KEY_
	
	//��Ŀ�� assert()
	
	AWE_INT_LOCK_();               		       /*  ��������  */	
	if (!OBJ_IS_QUEUE_Full((&(aim->qEvent))))            /* �ж��¼������Ƿ��� */
	{
		OBJ_QEVT_INSERT_(&(aim->qEvent), e, aim->prio);  /*�����¼�*/
	}
	AWE_INT_UNLOCK_();              /* ���� */
	
}





/**************************************************************/
/*         ����¼����������϶˵��¼�       */
AEvt const *AObj_getEvt_(AObj *me)
{	
		return OBJ_QEVT_GET_(&(me->qEvent), me->prio);
}





