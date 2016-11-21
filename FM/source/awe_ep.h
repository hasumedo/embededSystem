/**
  ******************************************************************************
  * @file    awe_ep.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  �¼����ȿ��ͷ�ļ�
  ******************************************************************************
  * @attention
  *    
	*
	*
  ******************************************************************************
  */
/**********************************************************/
/*! �ӿ�ͷ�ļ�*/
#include "awe_ep_port.h"


#ifndef  AWE_EP_H
#define  AWE_EP_H



/**********************************************************/
/*! ��ܰ汾 */
#define   A_VERSION       100                    //��ǰ�汾��
#define   A_VERSION_STR   "V1.00"


/*! ��ȡ�汾��Ϣ */
#define  GET_AFSM_VERSION()           (uint8_t)(A_VERSION)
#define  GET_AFSM_STR_VERSION()       (uint8_t*)(A_VERSION_STR)


/**********************************************************/
/*! �ṹ������*/
typedef   struct  AFsmTag   AFsm;




/*************************************************************/
/*! �������ԵĶ��� */
/**
 * @description 
 *	��ĸ�����Ϣ
 * @usage
 * 	��Ϊ������ĵ�һ����Ա���м̳�
 *
 */
typedef struct AInfo
{
		uint16_t infoID;   /* ״̬��Ϣ��� */
}AInfo;




/**************************************************************/
/*! �¼��ź�����ȡֵ��С����Χֵ��1,2,4���ֽڣ�Ĭ��ֵ��2*/
/**
* @description
* �ú�ָ�������port�ļ��У������� Qsignal ���ͣ�Ĭ�ϵ�ֵΪ2
*/
#ifndef     A_SIGNAL_SIZE                    /*��ȡ��С��Χ1,2,4���ֽ�*/
	#define   A_SIGNAL_SIZE          2         /*Ĭ���ͺ�����С2���ֽ�*/
#endif

#if          (A_SIGNAL_SIZE == 1)
		typedef     uint8_t     ASignal;
#elif        (A_SIGNAL_SIZE == 2)
		typedef     uint16_t    ASignal;
#elif        (A_SIGNAL_SIZE == 4)
		typedef     uint32_t    ASignal;
#else
		#error "SIGNAL_SIZE defined out of range!"
#endif





/*************************************************************/
/*! �¼��ṹ��Ķ��� */
/**
 * @description
 * AEvt�������¼��Ļ����¼������Ҳ�������
 * @usage
 * 	��Ϊ������ĵ�һ����Ա���м̳�
 *
 */
typedef  struct  AEvtTag  AEvt;
struct AEvtTag
{
		ASignal sig;         /* �¼��ź��� */
		uint16_t poolID;      /* �ڴ�ر�ţ���Ӧ�����¼����� */
};



/**************************************************************/
/*! ��״̬���ķ��ص����� */
typedef    uint8_t    AState;

/*! ״̬������ָ��*/
typedef AState (*AStateHandler)(AFsm *, AEvt const *);

/*! ִ��AStateHandleת�� */
/**
* @description
* �ú�ǿ��ת��״̬����ָ��AStateHandle
*
* @usage
* @include 
*/

#define A_STATE_CAST(handler_)  ((AStateHandle)(handler_))





/**************************************************************/
/*          FSM       */
/**
* @description
* 	����״̬��
*
*/
struct AFsmTag
{
		const AStateHandler * state_table;  /* ָ��״̬�� */
		ASignal  n_signals;                 /* �ź������� */
		uint8_t  n_states;                  /* ״̬���� */
		uint8_t  state;                     /* ��ǰ״̬��� */
		uint8_t  method ;                   /* ѡ��ʽ: Ŀǰ�ṩ2�֣��Ƿ�ʡ�Խ����˳�������Ĭ����ʡ���˳����� 
																					�������������Ҫ��Ϊ��ʡ�ڴ棬����ҵ����õ�ӳ�䷽ʽʱ�Ľ�*/
		AStateHandler initial;              /* ��ʼ�� ת�� */

};


/*!      ������Ӧ��ʽ      */
enum
{
		FSM_DEFAULT_METHOD,                 /* Ĭ�Ϸ�ʽ������������ */
		FSM_IGNORED_METHOD                  /* ���Գ��붯��ģʽ*/       
};



/* �ӿ� */
/* ���캯�� */
void AFsm_ctor(AFsm *me, AStateHandler * state_table, AStateHandler initial, 
                   ASignal  n_signals, uint8_t n_states, uint8_t method);   

/* ��ʼ������ */
void AFsm_init(AFsm *me);      

/* �¼����� */
void AFsm_dispatch(AFsm * me, AEvt const * e);

/* ���¼� */
void AFsm_empty(AFsm * me, AEvt const * e);   





/**************************************************************/
/*!     Ԥ���ź�״̬     */
enum 
{
    A_ENTRY_SIG = 0,                     /* ����״̬���� */
    A_EXIT_SIG,                          /*�˳�״̬���� */
    A_DEFAULT_SIG                        /*�û�Ԥ���ź� */
};




/**************************************************************/
/*!  ����״̬�����з���״̬ */
#define   A_RET_HANDLED     ((AState)0)
#define   A_RET_TRANS       ((AState)1)



/*!  ״̬��ת��״̬ */
#define   A_HANDLED()        (A_RET_HANDLED)
#define   A_TRANS(target_) \
				  (((AFsm *)me)->state = (uint8_t)(target_), A_RET_TRANS)



#endif



