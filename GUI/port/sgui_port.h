/**
  ******************************************************************************
  * @file    sgui_port.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  简易GUI的接口头文件
  ******************************************************************************
  * @attention
  *     
	*		  
	*   
  ******************************************************************************
  */
	
#ifndef   SGUI_PORT_H
#define   SGUI_PORT_H


/*************************************************************/
/*! GUI附带信息偏移ID */	
#define       GUI_INFOID       200

/*************************************************************/
/*! 最深层次目录数 */
#define  MAX_DIRECTORY                           5

/*************************************************************/
/*! 默认最大数据位数 */
#define   DEFAULT_MAX_DATALEN                    7     

/*************************************************************/
/*! 现有的参数类型 */
enum 
{
	VALUE_PARAMETER = 1,
	STRING_PARAMETER,
	TIME_PARAMETER       
};

/*************************************************************/
/*! 继承对象宏  */
#define   GUI_OBJ                                        AObj        
#define   STATE_HANDLE                                   AStateHandler
#define   GUI_INFO                                       AInfo
#define   PAGE_TRANS(target_)                            A_TRANS(target_)
#define   PAGE_HANDLED()                                 A_HANDLED()



/*************************************************************/
/*! 创建对象连接对象框架宏 */
#define   AOBJECT_CTOR(me, state_table, initial,              \
					max_sig, max_state, method)                         \
																	                       Aobj_ctor(me, state_table, initial,\
																	                       max_sig, max_state, method)
		

/*************************************************************/
/*! 简易GUI的创建宏和初始化宏 */
#define   SGUI_initial(me, e)      Interface_intial(me, e)
#define   SGUI_ctor(me)            Interface_ctor(me)      



/*************************************************************/
/* 包含框架头文件*/
#include "awe_fm_port.h"


/*! 包括sgui头文件 */
#include  "sgui.h"


/*! 包括sgui中的一些特殊参数头文件 */
#include  "sgui_valpara.h"
#include  "sgui_timepara.h"
#include  "sgui_strpara.h"


/*! BSP液晶显示头文件 */
#include "BSP_display.h"


/*************************************************************/
/*! BSP接口 */
/*! 显示字符和汉字混合的显示接口 */
#define  display_(str_, p_, size_, selBlock_, dir_)        \
														       	BSP_display(str_, p_, size_, selBlock_, dir_)


/*! 只显示ASCII的显示接口 */
#define  displayASC_(str_, p_, size_, selBlock_, dir_)        \
														       	BSP_ASCDisplay(str_, p_, size_, selBlock_, dir_)


/*************************************************************/
/*!    接口声明    */
/*!    GUI构造函数    */
void GUI_ctor(sGUI * me,  STATE_HANDLE *state_table, STATE_HANDLE GUI_initial,
               uint8_t max_sig, uint8_t max_state, uint8_t mode);


/*!  gui默认初始化加载函数 */
void GUI_loadInitial(sGUI * me);


/*! 显示参数，并且显示选中的位置*/
void 	Display_parameter(sGUI * me);




#endif





