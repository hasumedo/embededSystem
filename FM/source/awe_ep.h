/**
  ******************************************************************************
  * @file    awe_ep.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  事件调度框架头文件
  ******************************************************************************
  * @attention
  *    
	*
	*
  ******************************************************************************
  */
/**********************************************************/
/*! 接口头文件*/
#include "awe_ep_port.h"


#ifndef  AWE_EP_H
#define  AWE_EP_H



/**********************************************************/
/*! 框架版本 */
#define   A_VERSION       100                    //当前版本号
#define   A_VERSION_STR   "V1.00"


/*! 获取版本信息 */
#define  GET_AFSM_VERSION()           (uint8_t)(A_VERSION)
#define  GET_AFSM_STR_VERSION()       (uint8_t*)(A_VERSION_STR)


/**********************************************************/
/*! 结构体声明*/
typedef   struct  AFsmTag   AFsm;




/*************************************************************/
/*! 附加属性的定义 */
/**
 * @description 
 *	类的附加信息
 * @usage
 * 	作为衍生类的第一个成员进行继承
 *
 */
typedef struct AInfo
{
		uint16_t infoID;   /* 状态信息编号 */
}AInfo;




/**************************************************************/
/*! 事件信号量的取值大小，范围值是1,2,4个字节，默认值是2*/
/**
* @description
* 该宏指令可以在port文件中（）配置 Qsignal 类型，默认的值为2
*/
#ifndef     A_SIGNAL_SIZE                    /*可取大小范围1,2,4个字节*/
	#define   A_SIGNAL_SIZE          2         /*默认型号量大小2个字节*/
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
/*! 事件结构体的定义 */
/**
 * @description
 * AEvt是所有事件的基础事件，并且不带参数
 * @usage
 * 	作为衍生类的第一个成员进行继承
 *
 */
typedef  struct  AEvtTag  AEvt;
struct AEvtTag
{
		ASignal sig;         /* 事件信号量 */
		uint16_t poolID;      /* 内存池编号，对应的是事件块编号 */
};



/**************************************************************/
/*! 从状态机的返回的类型 */
typedef    uint8_t    AState;

/*! 状态机函数指针*/
typedef AState (*AStateHandler)(AFsm *, AEvt const *);

/*! 执行AStateHandle转换 */
/**
* @description
* 该宏强制转化状态函数指向AStateHandle
*
* @usage
* @include 
*/

#define A_STATE_CAST(handler_)  ((AStateHandle)(handler_))





/**************************************************************/
/*          FSM       */
/**
* @description
* 	有限状态机
*
*/
struct AFsmTag
{
		const AStateHandler * state_table;  /* 指向状态表 */
		ASignal  n_signals;                 /* 信号量总数 */
		uint8_t  n_states;                  /* 状态总数 */
		uint8_t  state;                     /* 当前状态编号 */
		uint8_t  method ;                   /* 选择方式: 目前提供2种：是否省略进入退出动作，默认是省略退出动作 
																					这里设置这个主要是为了省内存，如果找到更好的映射方式时改进*/
		AStateHandler initial;              /* 初始化 转换 */

};


/*!      动作响应方式      */
enum
{
		FSM_DEFAULT_METHOD,                 /* 默认方式：带进出动作 */
		FSM_IGNORED_METHOD                  /* 忽略出入动作模式*/       
};



/* 接口 */
/* 构造函数 */
void AFsm_ctor(AFsm *me, AStateHandler * state_table, AStateHandler initial, 
                   ASignal  n_signals, uint8_t n_states, uint8_t method);   

/* 初始化函数 */
void AFsm_init(AFsm *me);      

/* 事件处理 */
void AFsm_dispatch(AFsm * me, AEvt const * e);

/* 空事件 */
void AFsm_empty(AFsm * me, AEvt const * e);   





/**************************************************************/
/*!     预留信号状态     */
enum 
{
    A_ENTRY_SIG = 0,                     /* 进入状态动作 */
    A_EXIT_SIG,                          /*退出状态动作 */
    A_DEFAULT_SIG                        /*用户预留信号 */
};




/**************************************************************/
/*!  所有状态机所有返回状态 */
#define   A_RET_HANDLED     ((AState)0)
#define   A_RET_TRANS       ((AState)1)



/*!  状态机转换状态 */
#define   A_HANDLED()        (A_RET_HANDLED)
#define   A_TRANS(target_) \
				  (((AFsm *)me)->state = (uint8_t)(target_), A_RET_TRANS)



#endif



