/**
  ******************************************************************************
  * @file    sgui_strpara.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  简单的菜单GUI 文字参数部分
  ******************************************************************************
  * @attention
  *     
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SGUI_STR_PARA_H_
#define   SGUI_STR_PARA_H_



/*************************************************************/
/*! 文字类参数属性 */		
typedef struct Str_ParameterAttribute
{
		ParameterAttribute    super;                  /*继承数值类参数属性*/
	  const uint8_t    **   parameterStr;           /*显示的字符串指针数组,
																										这里最好保证每项文字数量都一样*/
		uint8_t       const   maxOptionNum;           /*最大文字选项*/
		int8_t                currOptionNum;          /*当前文字顺序*/
		uint8_t       const   fontSize;               /*字体大小*/	
		GUIPosition   const   paraPosition;           /*当前坐标*/	  
	
    /* 附加说明 */
		GUIPosition   const   instructionPositon;      /*附加说明显示的起始位置*/	
		const uint8_t **      added_instruction;       /*附加说明
																										这里最好保证每项文字数量都一样*/
																						
}Str_ParameterAttribute;



/*************************************************************/
/*! 当前页面第i个选项的参数属性转换  */	
#define  STR_PARA_POINT_(i_)		    	      ((Str_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para))  


/*************************************************************/
/*! 获取参数指针,(现在默认每个参数最多带一个参数) */	
#define  GUI_STR_PARA_POINT				         ((Str_ParameterAttribute *)(GUI_OPTION_POINT->para)) 


/*************************************************************/
/*! 判断参数类型*/
#define  IS_STR_PARAMETER()                (GET_PARA_TYPE == STRING_PARAMETER)

/*************************************************************/
/* 初始化显示的字符参数部分 */
void  Show_strParameterInit_(sGUI * me, uint8_t i);

/* 更新显示的字符参数部分 */
void  Show_strParameter_(sGUI * me);

/* 文字类型自由参数显示 */
void  Show_strFreePara_(sGUI * me, uint8_t i);


/*************************************************************/
/*! 改变文字选项参数,步进为1  */	
uint8_t  Modify_stringParameter(sGUI * me, uint8_t dir);





#endif

