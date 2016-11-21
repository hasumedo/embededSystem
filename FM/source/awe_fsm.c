/**
  ******************************************************************************
  * @file    awe_fsm.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  �¼����ȿ��
  ******************************************************************************
  * @attention
  *    
	*
	*
  ******************************************************************************
  */
#include "awe_ep.h"


/****************************************************************************/
/**
* @description
* Ԥ���ı�׼�¼�
*
*/
// static AEvt AEvt_reservedEvt_[] = 
// {
//    {(ASignal)A_ENTRY_SIG, (uint8_t)0},    /* ����״̬���� */
//    {(ASignal)A_EXIT_SIG, (uint8_t)0},     /*�˳�״̬���� */
//    {(ASignal)A_USER_SIG, (uint8_t)0}        /*�û�Ԥ���ź� */
// };




/****************************************************************************/
/**
* @brief
* 	FSM���캯��
*
* @param  
*     @arg    me                       ��ǰFSMָ��
*     @arg    state_table              ָ��״̬��ָ��
*     @arg    initial                  FSM��ʼ������  
*     @arg    n_signals                �ź�������
*     @arg    n_states                 ״̬������ 
*     @arg    method                   ������Ӧģʽ
*
* @retval None
*
*/
void AFsm_ctor(AFsm *me, AStateHandler *state_table, AStateHandler  initial, 
                     ASignal  n_signals, uint8_t n_states, uint8_t method)
{
		//assert(method);
		me->state_table = state_table;
		me->initial = initial;
		me->n_signals = n_signals;
		me->n_states = n_states;
		me->state = n_states;
		me->method = method;
}




/****************************************************************************/
/**
* @brief
* 	FSM��ʼ������
*
* @param  
*     @arg     me                       ��ǰFSMָ��
*
*
* @retval None
*
*/
void AFsm_init(AFsm *me)
{
		AStateHandler t;
		(me->initial)(me, (AEvt *)0);  //��ʼ��
		//assert((me->state) < (me->n_state));
		if ((me->method == FSM_DEFAULT_METHOD))       //Ĭ�Ϸ�ʽ��������ʽ��ʵ�ֻ�û��
		{
			t = *(me->state_table + me->state * me->n_signals + A_ENTRY_SIG);     //Ĭ�Ͻ���Ԥ�� 
			(*t)(me, (void *)0);
		}
		else
		{
			t = *(me->state_table + me->state * me->n_signals);          //Ĭ�Ͻ����һ��״̬
			(*t)(me, (void *)0);
		}
}





/****************************************************************************/
/**
* @brief
* 	FSM���Ⱥ���
*
* @param  
*     @arg     me                       ��ʾ���ֱ�
*     @arg     e                        �¼�
*
* @retval None
*
*/
void AFsm_dispatch(AFsm * me, AEvt const * e)
{
	AStateHandler t;
	uint8_t sta;
	//assert(e);//�¼��Ϸ���
	//assert(state);
	sta = me->state;
	t = *(me->state_table + me->state * me->n_signals + e->sig);  //��ȡ����ָ��
	
	if ((*t)(me, e) == A_RET_TRANS && (me->method == FSM_DEFAULT_METHOD))  //�õ�ִ�н��
	{
		/* �˳� */
		//assert(state);
			t = *(me->state_table + sta * me->n_signals + A_EXIT_SIG);
			(*t)(me, (void *)0);
			
		/* ���� */
		//assert(state);
			t = *(me->state_table + me->state * me->n_signals + A_ENTRY_SIG);       
			(*t)(me, (void *)0);
	}
	
}


/****************************************************************************/
/**
* @brief
* 	   FSM�պ���
*
* @description
*      ��״̬δ��Ӧ�ź���ʱ����
*      
* @param  
*     @arg     me                       ��ʾ���ֱ�
*     @arg     e                        �¼�
*
* @retval None
*
*/
void AFsm_empty(AFsm * me, AEvt const * const e)
{
		(void)me;
		(void)e;
}

