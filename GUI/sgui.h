/**
  ******************************************************************************
  * @file    sgui.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  简单的菜单GUI设计
  ******************************************************************************
  * @attention
  *     该类GUI的特点：
	*        页面是静态的（固定不变的）,并且图形界面不会过于复杂,显示单色
	*        且不支持触屏，只支持按键
	*     详细设计资料见文档
	*			
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SAMPLE_GUI_H
#define   SAMPLE_GUI_H

/**********************************************************/
/**
 * @description
 *	 GUI基础结构
 * @usage
 *   包括继承的对象框架
 *	 附加状态信息
 *   目录结构
 */
typedef struct GUITag 
{
		GUI_OBJ super;
		GUI_INFO * state_info;             /* 状态自带信息*/
	
}sGUI;




/*************************************************************/
/**
 * @description
 *      位置坐标
 * @usage
 * 		GUI位置坐标的描述
 *
 */
typedef struct GUIPosition
{
	uint16_t  x;
	uint16_t  y;
	
}GUIPosition;



/*************************************************************/
/**
 * @description
 *      参数属性
 * @usage
 * 		
 *
 */	
typedef struct ParameterAttribute
{
	  uint8_t      const    parameterType;          /*当前参数种类, 
	                                                 1表示数值参数，2表示文字参数，3表示时间信息*/  
}ParameterAttribute;





/*************************************************************/
/**
 * @description
 *      选项属性
 * @usage
 * 		
 *
 */	
typedef struct OptionAttribute
{
		/* 不变部分信息 */
		const uint8_t         fontSize;               /*字体大小*/	
		const uint8_t * const string;                 /*显示字符串*/
		const uint8_t         reserved;               /*保留项，主要针对于目录字体指向*/
		const GUIPosition     position;               /*显示字符位置*/	
		
		/*选项所带参数信息*/
	  const uint8_t         para_num;               /*选项所带参数个数，0为不带参数*/	
		const ParameterAttribute *  const  para;      /*选项对应的指向参数指针,
	                                                   若不带指针则为NULL指针*/   
           
}OptionAttribute;
	




/*************************************************************/
/**
 * @description
 *    目录结构
 * @usage
 * 		
 *
 */
typedef struct GUIDirectory
{
		const uint8_t  *      pString[MAX_DIRECTORY];          /*目录数组,最深层次不超过MAX_DIRECTORY*/
		const uint8_t         fontSize;                        /*字体大小*/	
		const GUIPosition     position;                        /*显示字符位置*/	
		const GUIPosition     outRangePosition;                /*超范围字符位置，超过用...代替*/	 
	
}GUIDirectory;




/*************************************************************/
/**
 * @description
 *    Sample GUI状态附加属性的定义
 * @usage
 * 		每个页面都需要带一个GUIStateInfo类型的参数做为这页的属性
 *
 */
typedef struct GUIStateInfo
{
		const GUI_INFO         super;                            /*状态附加属性继承*/
		const uint8_t          maxOption;                        /*当前页面（状态）下最多的选项*/
		int8_t                 currentOption;                    /*当前选中选项位置  0 表示未选中，第一项默认 NULL
	                                                               1 表示选中逻辑顺序上的第一项  */	
		uint8_t                selectedState;                    /*是否处于选中状态, 0表示未选中，1表示选中*/ 
		const OptionAttribute * const  pContent;                 /*为每个选项中对应的内容，指向指针数组，
	                                                              在创建时自动绑定到数组*/
		GUIDirectory     *     pGUIDirectory;                    /*页面自带目录*/               
		const ParameterAttribute **   pFreeParameter;            /*页面自带的自由参数*/
		const uint8_t          freeParaNumber;                   /*自由参数个数*/	 
	 
}GUIStateInfo; 


/*************************************************************/
/*! 增减方向  */
#define  ADD_DIR                            1
#define  SUB_DIR                            0


/*************************************************************/
/*! 获取当前页面信息指针  */	
#define  GUI_INFO_POINT          	         ((GUIStateInfo *)(me->state_info))

/*! 获取当前选项指针*/	
#define  GUI_OPTION_POINT                  (N_OPT_ATTRIBUTE_(GUI_INFO_POINT->currentOption))

/*! 获取参数个数 0为不带参数 */	
#define  GET_PARA_NUMBER                   (GUI_OPTION_POINT->para_num)

/*! 获取当前页面当前选中选项的参数类型*/ 
#define  GET_PARA_TYPE                  	 (GUI_OPTION_POINT->para->parameterType)	


/*************************************************************/																		
/*! 获取当前页面第i个选项的属性指针，第0个默认为NULL */	
#define  N_OPT_ATTRIBUTE_(i_)               (GUI_INFO_POINT->pContent+i_)


/*! 获取当前页面第i个选项的选中选项的参数类型， 
   1表示数值参数，2表示文字参数*/	
#define  GET_N_PARA_TYPE_(i_)            	  (N_OPT_ATTRIBUTE_(i_)->para->parameterType)					


/*************************************************************/
/*! 设置当前页面信息指针,成功返回1，不成功返回0  */	
uint8_t  Set_selectedState_(sGUI * me, uint8_t state);



/*************************************************************/
/*! 切换到页面 */	
#define  TRANS_PAGE(target_)              (me->state_info = (GUI_INFO *)GUI_Infomation[target_],\
                                            GUI_INFO_POINT->selectedState = 0,\
																						PAGE_TRANS(target_))

/*!  不改变页面*/
#define  HANDLED_PAGE()                    PAGE_HANDLED()


/*************************************************************/
/*! 获取当前是否有选项选中状态 
   必须是有参数的，若无参数则返回的都是0（未选中）*/	
#define  GET_SELECTED_STATE()              (GUI_INFO_POINT->selectedState)

/*! 设置当前选项进入设置参数状态,返回值是成功为1，不成功为0  */	 
#define  ENTER_SET_PARAMETER()             (Set_selectedState_(me, (uint8_t)1)) 

/*! 设置当前选项退出设置参数状态,返回值是成功为1，不成功为0  */	 
#define  EXIT_SET_PARAMETER()              (Set_selectedState_(me, (uint8_t)0))



/*************************************************************/
/*! 最小数值选项宏默认为1 */
#define  MIN_OPTION                              1 

/*! 获取当前选项位置  */	
#define  GET_CURRENT_OPTION()              (GUI_INFO_POINT->currentOption)

/*! 获取最大选项数 */
#define  GET_MAX_OPTION()                  (GUI_INFO_POINT->maxOption-(uint8_t)1)

/*! 修改当前选项位置， 修改成功返回1，失败返回0  */	
uint8_t  Modify_currentOption(sGUI * me, uint8_t dir, uint8_t offset);
		


/*************************************************************/
/*!    GUI初始化    */
void GUI_initial(sGUI * me, AEvt const *e);



/*************************************************************/
/*! 更新目录：将当前路径增加到目录或删除于目录 */
void Updata_directory(sGUI * me, uint8_t dir);



/*************************************************************/
/*! 初始化显示的目录部分*/
void  Show_directoryInit_(sGUI * me);





#endif
	
	
	
	
	
	
	
	
	
