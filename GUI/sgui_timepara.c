/**
  ******************************************************************************
  * @file    sgui_timepara.c
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
	
#include "sgui_timepara.h"	


/****************************************************************************/
/**
* @brief
*    将时间数值转化为字符串
*
* @param  
*     @arg     val                      当前时间值
*     @arg     str                      修改时间对象数组头指针
*     @arg     currentSelect            对应选中位
*
* @retval 
*          None
*
*/
static void ValueToString_(uint16_t val, uint8_t* str, uint8_t currentSelect)
{
	int i = 0, j;
	uint8_t str1[5]={0};
	if (val == 0)
	{
		if (currentSelect != 0)
		{
			*str++ = ' ';
			*str++ = '0';
			*str = '\0';
		}
		else
		{
			*str++ = ' ';*str++ = ' ';*str++ = ' ';
			*str++ = '0';
			*str = '\0';
		}
		return;
	}
	
	while (val != 0)
	{
		*(str1+i++) = (val % 10) + 48;
		val /= 10;
	}
	(currentSelect==0) ? (j=4-i) : (j=2-i);
	while (j--)
	{
		*str++ = ' ';
	}
	while (i--)
	{
		*str++ = *(str1+i);
	}
	*str = '\0';
}






/****************************************************************************/
/**
* @brief
*    改变时间选项参数,步进为1
*
* @param  
*     @arg    me                       当前gui对象
*     @arg     dir                      增减方向
*                                      ADD_DIR  增 
*                                      SUB_DIR  减
*
* @retval 
*          None
*
*/
void  Modify_timeParameter(sGUI * me, uint8_t dir)
{
	uint8_t t, day, month, tmp; 
	if (IS_TIME_PARAMETER())
	{	
		t = GUI_TIME_PARA_POINT->currentbit;
		if (dir == ADD_DIR) 
		{   /*增加*/
				switch (t)
				{
					case 2: /*月份*/
					{
							if (GUI_TIME_PARA_POINT->time[1] == 12)
							{
								GUI_TIME_PARA_POINT->time[1] = 1;
							}
							else
							{
								GUI_TIME_PARA_POINT->time[1]++;
							}
							
							day = GUI_TIME_PARA_POINT->time[2];
							month = GUI_TIME_PARA_POINT->time[1];	
							
							if ((day > 28) && (month == 2))
							{
								GUI_TIME_PARA_POINT->time[2] = 28;
							}
							else if ((day == 31) && ((month == 4) || (month == 6) || 
														(month == 9) || (month == 11)))
							{
								GUI_TIME_PARA_POINT->time[2] = 30;
							}
							break;
					}
					case 3:/*日期*/
					{
							day = GUI_TIME_PARA_POINT->time[2];
							month = GUI_TIME_PARA_POINT->time[1];
							GUI_TIME_PARA_POINT->time[2]++;
							if ((month == 2) && (day > 27)) /*2月最大不超过28天，这里懒得计算闰年了*/
							{
									GUI_TIME_PARA_POINT->time[2] = 1;
							}
							else if((day > 29) && ((month == 4) || (month == 6) || 
																(month == 9) || (month == 11)))
							{
									 GUI_TIME_PARA_POINT->time[2] = 1;
							}else if (day > 30)
							{
								 GUI_TIME_PARA_POINT->time[2] = 1;
							}
							break;
					}
					case 4:/*小时*/
					{
						(GUI_TIME_PARA_POINT->time[3] == 23) ? (GUI_TIME_PARA_POINT->time[3] = 0) 
																								: GUI_TIME_PARA_POINT->time[3]++;
						break;
					}
					case 5:tmp = 4;goto TimeLb1;/*分秒十位*/
					case 7:tmp = 5;
					{
TimeLb1:		GUI_TIME_PARA_POINT->time[tmp] += 10;
						if (GUI_TIME_PARA_POINT->time[tmp] > 59)
							GUI_TIME_PARA_POINT->time[tmp] = 0;
						break;
					}
					case 6:tmp = 4;goto TimeLb2;/*分秒个位*/
					case 8:tmp = 5;
					{
TimeLb2:		GUI_TIME_PARA_POINT->time[tmp]++;
						if (GUI_TIME_PARA_POINT->time[tmp] > 59)
							GUI_TIME_PARA_POINT->time[tmp] = 0;
						break;
					}
					case 0:/*年份个位*/
					{						
						GUI_TIME_PARA_POINT->time[0] += 10;
						if (GUI_TIME_PARA_POINT->time[0]<1500)
							GUI_TIME_PARA_POINT->time[0] = 1500 ;
						if (GUI_TIME_PARA_POINT->time[0]>2500)
							GUI_TIME_PARA_POINT->time[0] = 2500 ;
						break;
					}
					case 1:/*年份十位*/
					{
						GUI_TIME_PARA_POINT->time[0]++;
						if (GUI_TIME_PARA_POINT->time[0]<1500)
							GUI_TIME_PARA_POINT->time[0] = 1500 ;
						if (GUI_TIME_PARA_POINT->time[0]>2500)
							GUI_TIME_PARA_POINT->time[0] = 2500 ;
						break;
					}
					
				}
		}
		else
		{ /*减小*/
				switch (t)
				{
					case 2: /*月份*/
					{
							if (GUI_TIME_PARA_POINT->time[1] == 1)
							{
								GUI_TIME_PARA_POINT->time[1] = 12;
							}
							else
							{
								GUI_TIME_PARA_POINT->time[1]--;
							}
							
							day = GUI_TIME_PARA_POINT->time[2];
							month = GUI_TIME_PARA_POINT->time[1];	
							
							if ((day > 28) && (month == 2))
							{
								GUI_TIME_PARA_POINT->time[2] = 28;
							}
							else if ((day == 31) && ((month == 4) || (month == 6) || 
														(month == 9) || (month == 11)))
							{
								GUI_TIME_PARA_POINT->time[2] = 30;
							}
							break;
					}
					case 3:/*日期*/
					{
							day = GUI_TIME_PARA_POINT->time[2];
							month = GUI_TIME_PARA_POINT->time[1];
							GUI_TIME_PARA_POINT->time[2]--;
							if (day == 1)
							{
								if (month == 2) /*2月最大不超过28天，这里懒得计算闰年了*/
								{
										GUI_TIME_PARA_POINT->time[2] = 28;
								}
								else if((month == 4) || (month == 6) || 
																	(month == 9) || (month == 11))
								{
										 GUI_TIME_PARA_POINT->time[2] = 30;
								}else
								{
									 GUI_TIME_PARA_POINT->time[2] = 31;
								}
							}
							break;
					}
					case 4:/*小时*/
					{
						(GUI_TIME_PARA_POINT->time[3] == 0) ? (GUI_TIME_PARA_POINT->time[3] = 23) 
																								: GUI_TIME_PARA_POINT->time[3]--;
						break;
					}
					case 5:tmp = 4;goto TimeLb3;/*分秒十位*/
					case 7:tmp = 5;
					{
TimeLb3:		GUI_TIME_PARA_POINT->time[tmp] -= 10;
						if (GUI_TIME_PARA_POINT->time[tmp] > 59)
							GUI_TIME_PARA_POINT->time[tmp] = 59;
						break;
					}
					case 6:tmp = 4;goto TimeLb4;/*分秒个位*/
					case 8:tmp = 5;
					{
TimeLb4:		GUI_TIME_PARA_POINT->time[tmp]--;
						if (GUI_TIME_PARA_POINT->time[tmp] > 59)
							GUI_TIME_PARA_POINT->time[tmp] = 59;
						break;
					}
					case 0:/*年份个位*/
					{						
						GUI_TIME_PARA_POINT->time[0] -= 10;
						if (GUI_TIME_PARA_POINT->time[0]<1500)
							GUI_TIME_PARA_POINT->time[0] = 1500 ;
						if (GUI_TIME_PARA_POINT->time[0]>2500)
							GUI_TIME_PARA_POINT->time[0] = 2500 ;
						break;
					}
					case 1:/*年份十位*/
					{
						GUI_TIME_PARA_POINT->time[0]--;
						if (GUI_TIME_PARA_POINT->time[0]<1500)
							GUI_TIME_PARA_POINT->time[0] = 1500 ;
						if (GUI_TIME_PARA_POINT->time[0]>2500)
							GUI_TIME_PARA_POINT->time[0] = 2500 ;
						break;
					}
					
				}
			
		}
		
		/*更新显示*/
		Show_timeParameter_(me);
	}
}





/****************************************************************************/
/**
* @brief
*    改变时间当前选中位
*
* @param  
*     @arg    me                       当前gui对象
*     @arg     dir                      增减方向
*                                      ADD_DIR  增 
*                                      SUB_DIR  减
*
* @retval 
*          None
*
*/
void  Modify_timeCurrentBit(sGUI * me, uint8_t dir)
{
	if (IS_TIME_PARAMETER())
	{	
				if (dir == ADD_DIR) 
				{
						GUI_TIME_PARA_POINT->currentbit++;
						if (GUI_TIME_PARA_POINT->currentbit > 8)
						{
							GUI_TIME_PARA_POINT->currentbit = 0;
						}
				}
				else
				{
						GUI_TIME_PARA_POINT->currentbit--;
						if (GUI_TIME_PARA_POINT->currentbit < 0)
						{
							GUI_TIME_PARA_POINT->currentbit = 8;
						}		
				}
	}

}
	
	
		
/****************************************************************************/
/**
* @brief
*    初始化显示的时间参数部分
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_timeParameterInit_(sGUI * me, uint8_t i)
{	
	uint8_t n = 0;
	GUIPosition p;
	uint8_t str1[5] = {0};
	Time_ParameterAttribute * time_para;

	if (GET_N_PARA_TYPE_(i) == TIME_PARAMETER)
	{
			time_para = TIME_PARA_POINT_(i);
			for (n = 0; n < 6; n++)
			{
				p = time_para->paraPosition[n];
					ValueToString_(time_para->time[n], str1, n);//转化成字符串
				//显示数组字符串
				displayASC_(str1, p, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);
			}
	
	}

}
	


/****************************************************************************/
/**
* @brief
*    更新显示的文字参数部分
*
* @param  
*     @arg    me                       当前gui对象
*
* @retval 
*          None
*
*/
void  Show_timeParameter_(sGUI * me)
{
	uint8_t i = 0, n = 0;
	Time_ParameterAttribute * time_para;
	uint8_t tmp, offset, time_bit = 0;
	GUIPosition position;
	uint8_t str1[5] = {0};	
	uint8_t s[2] = {0};
	
	if (IS_TIME_PARAMETER())
	{
			time_para = GUI_TIME_PARA_POINT;	
			/* 显示时间数据 */
			if (GET_SELECTED_STATE() != 0)
			{	/*处于设置状态*/
				tmp = time_para->currentbit;
				if(tmp < 2)
				{
					time_bit = 0;
					(tmp == 0) ? (offset = 2) : (offset = 3);
					
				}else if (tmp == 2)
				{
					offset = 1;
					time_bit = 1;
				}else if (tmp == 3)
				{
					offset = 1;
					time_bit = 2;
				}else if (tmp == 4)
				{
					offset = 1;
					time_bit = 3;
				}else if (tmp < 7)
				{
					(tmp == 5) ? (offset = 0) : (offset = 1);
					time_bit = 4;
				}else 
				{
					(tmp == 8) ? (offset = 1) : (offset = 0);
					time_bit = 5;
				}
				
				/*取出中间的偏移位，并且取反*/	
					for (i = 0; i < 6; i++)
					{					
							position = time_para->paraPosition[i];
								ValueToString_(time_para->time[i], str1, i);//转化成字符串
							//显示数组字符串				
							if (i == time_bit)
							{
								while (str1[n] != '\0')
								{
									 s[0] = str1[n]; 
									if (offset != n)
									{
										position = displayASC_(s, position, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);
									}
									else
									{
										position = displayASC_(s, position, time_para->paraFontSize, SELECT_BLOCK, HORI_DISPLAY);
									}
									n++;
								}
							}
							else
							{
								displayASC_(str1, position, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);							
							}
					}
			}
			else
			{/*未处于设置状态*/
					for (i = 0; i < 6; i++)
					{					
						position = time_para->paraPosition[i];
							ValueToString_(time_para->time[i], str1, i);//转化成字符串
						display_(str1, position, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);	
					}
			}		
	}
}



/****************************************************************************/
/**
* @brief
*    时间类型自由参数显示
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    i                        第i个参数
*
* @retval 
*          None
*
*/
void  Show_timeFreePara_(sGUI * me, uint8_t i)
{	
		Time_ParameterAttribute * time_para;
		GUIPosition p;
		uint8_t n = 0;
		uint8_t str1[5] = {0};
		if (GUI_INFO_POINT->pFreeParameter[i]->parameterType == TIME_PARAMETER)
		{
				time_para = (Time_ParameterAttribute *)GUI_INFO_POINT->pFreeParameter[i];
				p = *(time_para->paraPosition);
				for (n = 0; n < 6; n++)
				{
						ValueToString_(time_para->time[n], str1, n);//转化成字符串
					//显示数组字符串
					p = displayASC_(str1, p, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);
					p = displayASC_("/", p, time_para->paraFontSize, NO_SELECT_BLOCK, HORI_DISPLAY);
				}
		}	
}



