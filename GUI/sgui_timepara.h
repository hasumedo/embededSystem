/**
  ******************************************************************************
  * @file    sgui_timepara.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  简单的菜单GUI 时间参数部分
  ******************************************************************************
  * @attention
  *     
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SGUI_TIME_PARA_H_
#define   SGUI_TIME_PARA_H_


/*************************************************************/
/*! 时间类参数属性 */		
typedef struct Time
{
		ParameterAttribute    super;                  /*继承数值类参数属性*/		
	  int8_t                currentSelect;          /*当前年月日时分秒选择*/ 
		int8_t                currentbit;             /*当前选中位置*/
		uint8_t       const   paraFontSize;           /*参数字体大小*/	
		uint16_t              time[6];                /*时间*/
		GUIPosition const * const  paraPosition;		  /*时间字符显示位置*/
}Time_ParameterAttribute;


/*************************************************************/
/*! 当前页面第i个选项的参数属性转换  */	
#define  TIME_PARA_POINT_(i_)		    	      ((Time_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para)) 


/*************************************************************/
/*! 获取参数指针,(现在默认每个参数最多带一个参数) */	
#define  GUI_TIME_PARA_POINT				       ((Time_ParameterAttribute *)(GUI_OPTION_POINT->para)) 


/*************************************************************/
/*! 判断参数类型*/
#define  IS_TIME_PARAMETER()               (GET_PARA_TYPE == TIME_PARAMETER)


/*************************************************************/
/*! 初始化显示的时间参数部分*/	
void  Show_timeParameterInit_(sGUI * me, uint8_t i);

/*! 改变时间当前选中位 */	
void  Modify_timeCurrentBit(sGUI * me, uint8_t dir);

/*! 调整时间 */	
void  Modify_timeParameter(sGUI * me, uint8_t dir);

/*! 时间类型自由参数显示  */	
void  Show_timeFreePara_(sGUI * me, uint8_t i);


/*************************************************************/
/*! 更新显示的文字参数部分  */	
void  Show_timeParameter_(sGUI * me);


#endif

