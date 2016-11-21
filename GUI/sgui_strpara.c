/**
  ******************************************************************************
  * @file    sgui_strpara.c
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
#include "sgui_strpara.h"	

/****************************************************************************/
/**
* @brief
*    修改显示的字符参数
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    dir                      增减方向
*                                      ADD_DIR  增 
*                                      SUB_DIR  减
*
* @retval 
*          修改成功返回1，失败返回0
*
*/
uint8_t  Modify_stringParameter(sGUI * me, uint8_t dir)
{
		if (IS_STR_PARAMETER())
		{	
				if (dir == 1) 
				{
						GUI_STR_PARA_POINT->currOptionNum++;
						if (GUI_STR_PARA_POINT->currOptionNum > GUI_STR_PARA_POINT->maxOptionNum)
						{
							GUI_STR_PARA_POINT->currOptionNum = 1;
						}
				}
				else if (dir == 0)
				{
						GUI_STR_PARA_POINT->currOptionNum--;
						if (GUI_STR_PARA_POINT->currOptionNum < 1)
						{
							GUI_STR_PARA_POINT->currOptionNum = GUI_STR_PARA_POINT->maxOptionNum;
						}		
				}
				else
				{
						return 0;
				}
				return 1;
		}
		else
		{
			return 0;
		}	
	
}



/****************************************************************************/
/**
* @brief
*    初始化显示的字符参数部分
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_strParameterInit_(sGUI * me, uint8_t i)
{
		Str_ParameterAttribute * str_para;
		if (GET_N_PARA_TYPE_(i) == STRING_PARAMETER)
			{
					str_para = STR_PARA_POINT_(i);
					/* 显示参数 */
					display_(
												str_para->parameterStr[str_para->currOptionNum], 
												str_para->paraPosition,
												str_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
												HORI_DISPLAY
											);
					
					/* 显示附加参数 */
					if (str_para->added_instruction != NULL)
					{		
						display_(
											str_para->added_instruction[str_para->currOptionNum],
											str_para->instructionPositon,
											str_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
											HORI_DISPLAY
										);
					}			
			}		
}




/****************************************************************************/
/**
* @brief
*    更新显示的字符参数部分
*
* @param  
*     @arg    me                       当前gui对象
*
* @retval 
*          None
*
*/
void  Show_strParameter_(sGUI * me)
{
	Str_ParameterAttribute * str_para;
	
	if (IS_STR_PARAMETER())
	{
			str_para = GUI_STR_PARA_POINT;

			display_(str_para->parameterStr[str_para->currOptionNum], str_para->paraPosition,
										str_para->fontSize, GET_SELECTED_STATE(), HORI_DISPLAY);
			
			/* 附加信息*/
			if (str_para->added_instruction != NULL)
			{		
				display_(
									str_para->added_instruction[str_para->currOptionNum], 
									str_para->instructionPositon,
									str_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
									HORI_DISPLAY
								);
			}
	}		



}
	

/****************************************************************************/
/**
* @brief
*    文字类型自由参数显示
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_strFreePara_(sGUI * me, uint8_t i)
{
	Str_ParameterAttribute * str_para;
	
	if (GUI_INFO_POINT->pFreeParameter[i]->parameterType == STRING_PARAMETER)
	{
			str_para = (Str_ParameterAttribute *)(GUI_INFO_POINT->pFreeParameter[i]);
			/* 显示参数 */
			display_(
								str_para->parameterStr[str_para->currOptionNum],
								str_para->paraPosition,
								str_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
								HORI_DISPLAY
							);
			
			/* 显示附加参数 */
			if (str_para->added_instruction != NULL)
			{		
				display_(
									str_para->added_instruction[str_para->currOptionNum], 
									str_para->instructionPositon,
									str_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
									HORI_DISPLAY
								);
			}			
	}		
	
}






