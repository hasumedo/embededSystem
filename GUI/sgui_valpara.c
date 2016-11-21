  /******************************************************************************
  * @file    sgui_valpara.c
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
	
#include "sgui_valpara.h"
	
/****************************************************************************/
/**
* @brief
*    修改显示的数值参数
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
uint8_t  Modify_valueCurrentSelected(sGUI * me, uint8_t dir, uint8_t offset)
{
		if (IS_VAL_PARAMETER())
		{
				if (dir == ADD_DIR)        //右
				{
						GUI_VLA_PARA_POINT->currentSelect += offset;
						if (GET_VAL_PARA_SELECTION() > DEFAULT_MAX_DATALEN)
						{
							GUI_VLA_PARA_POINT->currentSelect = 0;
						}
				}
				else if (dir == SUB_DIR)                //左
				{
						GET_VAL_PARA_SELECTION() -= offset;
						if (GET_VAL_PARA_SELECTION() < 0)
						{
							GUI_VLA_PARA_POINT->currentSelect = DEFAULT_MAX_DATALEN;
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
*    初始化显示的数值参数部分
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_valParameterInit_(sGUI * me, uint8_t i)
{
			Val_ParameterAttribute * val_para;
			if (GET_N_PARA_TYPE_(i) == VALUE_PARAMETER)
			{
				val_para = VLA_PARA_POINT_(i);
				/* 显示参数 */
				displayASC_(
											val_para->parameterStr, 
											val_para->paraPosition,
											val_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
											HORI_DISPLAY
										);
			}
	
}
	
	
	
/****************************************************************************/
/**
* @brief
*    更新显示的数值参数部分
*
* @param  
*     @arg    me                       当前gui对象
*
* @retval 
*          None
*
*/
void  Show_valParameter_(sGUI * me)
{
	GUIPosition position;
	Val_ParameterAttribute * val_para;
	uint8_t *pStr;
	uint8_t s[2] = {0};
	uint8_t i = 0;
	if (IS_VAL_PARAMETER())
	{
			val_para = GUI_VLA_PARA_POINT;
			position = val_para->paraPosition;
			pStr = val_para->parameterStr;
			if (GET_SELECTED_STATE() != 0)
			{
				while (*pStr != '\0')
				{
						s[0] = *pStr++;
						position = display_(s, position, val_para->fontSize, 
														(val_para->currentSelect==i++)?(SELECT_BLOCK):(NO_SELECT_BLOCK),
														HORI_DISPLAY);
				}
			}
			else
			{
						display_(pStr, position, val_para->fontSize, NO_SELECT_BLOCK, HORI_DISPLAY);
			}
	}
	
}


/****************************************************************************/
/**
* @brief
*    数值自由参数显示
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_valFreePara_(sGUI * me, uint8_t i)
{
	Val_ParameterAttribute * val_para;
	/* 判断当前是否有参数 ,如果有则显示 */
	if (GUI_INFO_POINT->pFreeParameter[i]->parameterType == VALUE_PARAMETER)
	{
		val_para = (Val_ParameterAttribute *)(GUI_INFO_POINT->pFreeParameter[i]);
		/* 显示参数 */
		displayASC_(
									val_para->parameterStr, 
									val_para->paraPosition,
									val_para->fontSize, NO_SELECT_BLOCK,      //默认状态都不选中
									HORI_DISPLAY
								);
	}
	
}




/*---------------------------------------------------------------------------------------------*/
/*! 数据修改的工具包 */

/****************************************************************************/
/**
* @brief
*    数值转化到字符串
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Val2String(uint8_t * str, uint8_t type, uint8_t dirction, uint8_t bit)
{
		int i;
		int t;
		//assert(bit >= MAX_DATA_BIT);
		//assert(bit == MAX_DATA_BIT);
		if (*(str+bit) == '.')
			return;
		
		if (*(str+bit) == ' ')
		{
			(dirction==ADD_DIR) ? (*(str+bit) = '0') : (*(str+bit) = '9');
		}
		else
		{
			/*增减*/
				if (dirction == ADD_DIR) 
				{
					if (*(str+bit) == '9')
						*(str+bit) = '0';
					else
						(*(str+bit))++;
				}
				else
				{
					if (*(str+bit) == '0')
						*(str+bit) = '9';
					else
						(*(str+bit))--;
				}
		 }
			
		if (*str != ' ')
		{
				/*如果是空白位置增加,其他位置默认增加0来填充*/
				for (i = bit+1; i < DEFAULT_MAX_DATALEN; i++)  //第0位开始
				{
					if (*str == ' ')
						*str++ = '0';
					else
						break;
				}
				
				/*最后检测头是不是全是0，是0隐藏*/
				if ((type == FLOAT) || (type == DOUBLE))
				{
				//	t = DEFAULT_POINT_BIT - 1;
				}
				else
				{
					t = DEFAULT_MAX_DATALEN;
				}
				for (i = 0; i < t; i++)  //第0位开始
				{
					if (*str == ' ')
						*str++ = ' ';
					else
						break;
				}
		}
	
}

