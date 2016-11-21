/**
  ******************************************************************************
  * @file    sgui_valpara.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  简单的菜单GUI 数值参数部分
  ******************************************************************************
  * @attention
  *     
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SGUI_VAL_PARA_H_
#define   SGUI_VAL_PARA_H_

/*************************************************************/
/*! 类型宏 */	
enum 
{
	BOOL,
	CHAR,
	UNSIGNED_CHAR,
	INT,
	UNSIGNED_INT,
	FLOAT,
	DOUBLE
};


/*************************************************************/
/*! 数值类参数属性 */		
typedef struct Val_ParameterAttribute
{
		ParameterAttribute    super;                  /*继承数值类参数属性*/		
	  int8_t                currentSelect;          /*当前选中参数的位置*/  
		uint8_t *     const   parameterStr;           /*参数字符串*/
		uint8_t       const   storeType;              /*存储类型*/
		uint8_t       const   fontSize;               /*字体大小*/	
		GUIPosition   const   paraPosition;           /*当前坐标*/
}Val_ParameterAttribute;





/*************************************************************/
/*! 当前页面第i个选项的参数属性转换  */	
#define  VLA_PARA_POINT_(i_)                ((Val_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para))



/*************************************************************/
/*! 获取参数指针,(现在默认每个参数最多带一个参数) */	
#define  GUI_VLA_PARA_POINT                 ((Val_ParameterAttribute *)(GUI_OPTION_POINT->para))



/*************************************************************/
/*! 判断参数类型*/
#define  IS_VAL_PARAMETER()                 (GET_PARA_TYPE == VALUE_PARAMETER)



/*************************************************************/
/*! 获取当前选中数值型参数位置  */	
#define  GET_VAL_PARA_SELECTION()           (GUI_VLA_PARA_POINT->currentSelect)



/*************************************************************/
/*! 获取存储类型  */	
#define  GET_VAL_PARA_TYPE()                (GUI_VLA_PARA_POINT->storeType)



/*************************************************************/
/*! 获取参数字符串  */	
#define  GET_VAL_PARA_STRING()              (GUI_VLA_PARA_POINT->parameterStr)



/*************************************************************/
/*! 初始化显示的数值参数部分 */
void  Show_valParameterInit_(sGUI * me, uint8_t i);


/*! 更新显示的数值参数部分 */
void  Show_valParameter_(sGUI * me);

/*! 自由参数显示 */
void  Show_valFreePara_(sGUI * me, uint8_t i);

/*************************************************************/
/*!	修改当前选中参数位置 修改成功返回1，失败返回0   */	
uint8_t  Modify_valueCurrentSelected(sGUI * me, uint8_t dir, uint8_t offset);




/*---------------------------------------------------------------------------------------------*/
/*************************************************************/
/*! 数据修改的工具包 */
/*!	数值转化到字符串  */	
void  Val2String(uint8_t * str, uint8_t type, uint8_t dirction, uint8_t bit);





#endif



