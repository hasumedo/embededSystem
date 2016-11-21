/**
  ******************************************************************************
  * @file    sgui_port.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  简易GUI的构造和初始化函数接口函数
  ******************************************************************************
  * @attention
  *     作为接口函数，该文件里面的函数是不可或缺的，但需要根据框架对象进行修改。
	*		  
	*   
  ******************************************************************************
  */

#include "sgui_port.h"

/****************************************************************************/
/**
* @brief
* 	GUI构造函数
*
* @param  
*     @arg    me                       当前对象指针
*     @arg    state_table              指向状态表指针
*     @arg    initial                  对象初始化函数  
*     @arg    max_sig                  信号量总数
*     @arg    max_state                状态量总数 
*     @arg    method                   动作响应模式
*
* @retval None
*
*/
void GUI_ctor(sGUI * me, STATE_HANDLE * state_table, STATE_HANDLE initial,
               uint8_t max_sig, uint8_t max_state, uint8_t mode)
{	
		/*这里的对象可以根据对象不同在sgui_port中进行宏定义*/
		AOBJECT_CTOR(&me->super, (STATE_HANDLE *)state_table,
										(STATE_HANDLE)initial, max_sig, max_state, mode);
		
}



/****************************************************************************/
/**
* @brief
*    初始化显示的自由参数部分
*
* @param  
*     @arg    me                       当前gui对象
*
* @retval 
*          None
*
*/
static void  Show_freeParaInit_(sGUI * me)
{
	  uint8_t i = 0;

		/*显示自由参数*/
		if (GUI_INFO_POINT->freeParaNumber != 0)
		{
				for (i = 0; i < GUI_INFO_POINT->freeParaNumber; i++)
				{	
						Show_valFreePara_(me, i);/*数值自由参数显示*/
			
						Show_strFreePara_(me, i);/*文字类自由参数显示*/
						
						Show_timeFreePara_(me, i);/*时间类自由参数显示*/
				}
		}
}




/****************************************************************************/
/**
* @brief
* 	gui默认初始化加载函数
*
* @param  
*     @arg    me                       当前sgui对象
*
* @retval None
*
*/
void GUI_loadInitial(sGUI * me)
{
		uint8_t i = 0;
		uint8_t t;

		/* 显示选项及选项参数 */
		for (i = 0; i < GUI_INFO_POINT->maxOption; i++)
		{
			(GUI_INFO_POINT->currentOption == i) ? (t=SELECT_BLOCK) : (t=NO_SELECT_BLOCK);

			
			/* 显示选项 */
			display_(
								N_OPT_ATTRIBUTE_(i)->string,
								N_OPT_ATTRIBUTE_(i)->position,
								N_OPT_ATTRIBUTE_(i)->fontSize, t,
								HORI_DISPLAY
							);
			
			
			/* 如果有参数则显示 */
			Show_valParameterInit_(me, i);      /*显示数值类初始化参数*/        
			 
			Show_strParameterInit_(me, i);      /*显示文字类初始化参数*/
			
			Show_timeParameterInit_(me, i);    /*显示时间类初始化参数*/
		
		}
		
		Show_directoryInit_(me);/*初始化目录*/
	
		Show_freeParaInit_(me);/*初始化自由参数*/
}



/****************************************************************************/
/**
* @brief
* 	显示参数，并且显示选中的位置
*
* @param  
*     @arg    me                       当前sgui对象
*
* @retval None
*
*/
void 	Display_parameter(sGUI * me)
{	

	Show_valParameter_(me);/*显示数值类参数*/
	Show_strParameter_(me); /*显示文字类参数*/	
	Show_timeParameter_(me); /*显示时间类参数*/	
	

}
	

