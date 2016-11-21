/**
  ******************************************************************************
  * @file    awe_fsm.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  事件调度框架
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
* 预留的标准事件
*
*/
// static AEvt AEvt_reservedEvt_[] = 
// {
//    {(ASignal)A_ENTRY_SIG, (uint8_t)0},    /* 进入状态动作 */
//    {(ASignal)A_EXIT_SIG, (uint8_t)0},     /*退出状态动作 */
//    {(ASignal)A_USER_SIG, (uint8_t)0}        /*用户预留信号 */
// };




/****************************************************************************/
/**
* @brief
* 	FSM构造函数
*
* @param  
*     @arg    me                       当前FSM指针
*     @arg    state_table              指向状态表指针
*     @arg    initial                  FSM初始化函数  
*     @arg    n_signals                信号量总数
*     @arg    n_states                 状态量总数 
*     @arg    method                   动作响应模式
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
* 	FSM初始化函数
*
* @param  
*     @arg     me                       当前FSM指针
*
*
* @retval None
*
*/
void AFsm_init(AFsm *me)
{
		AStateHandler t;
		(me->initial)(me, (AEvt *)0);  //初始化
		//assert((me->state) < (me->n_state));
		if ((me->method == FSM_DEFAULT_METHOD))       //默认方式，其他方式的实现还没做
		{
			t = *(me->state_table + me->state * me->n_signals + A_ENTRY_SIG);     //默认进入预留 
			(*t)(me, (void *)0);
		}
		else
		{
			t = *(me->state_table + me->state * me->n_signals);          //默认进入第一个状态
			(*t)(me, (void *)0);
		}
}





/****************************************************************************/
/**
* @brief
* 	FSM调度函数
*
* @param  
*     @arg     me                       显示汉字表
*     @arg     e                        事件
*
* @retval None
*
*/
void AFsm_dispatch(AFsm * me, AEvt const * e)
{
	AStateHandler t;
	uint8_t sta;
	//assert(e);//事件合法性
	//assert(state);
	sta = me->state;
	t = *(me->state_table + me->state * me->n_signals + e->sig);  //获取函数指针
	
	if ((*t)(me, e) == A_RET_TRANS && (me->method == FSM_DEFAULT_METHOD))  //得到执行结果
	{
		/* 退出 */
		//assert(state);
			t = *(me->state_table + sta * me->n_signals + A_EXIT_SIG);
			(*t)(me, (void *)0);
			
		/* 进入 */
		//assert(state);
			t = *(me->state_table + me->state * me->n_signals + A_ENTRY_SIG);       
			(*t)(me, (void *)0);
	}
	
}


/****************************************************************************/
/**
* @brief
* 	   FSM空函数
*
* @description
*      当状态未对应信号量时调用
*      
* @param  
*     @arg     me                       显示汉字表
*     @arg     e                        事件
*
* @retval None
*
*/
void AFsm_empty(AFsm * me, AEvt const * const e)
{
		(void)me;
		(void)e;
}

