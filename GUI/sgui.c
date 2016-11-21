/**
  ******************************************************************************
  * @file    sgui.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  
  ******************************************************************************
  * @attention
  *      该文件包括了sgui基础部分的函数的一些实现
	*		  
	*   
  ******************************************************************************
  */

#include "sgui.h"

/****************************************************************************/
/**
* @brief
* 	GUI初始化
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
void GUI_initial(sGUI * me, AEvt const *e)
{
		(void)e;
		(void)me;
}




/****************************************************************************/
/**
* @brief
* 	设置当前页面选中状态
*
* @param  
*     @arg    me                       当前sgui指针
*     @arg    state                    设置页面选中状态
*                                       0表示未选中，1表示选中
* @retval 
*          修改成功返回1，失败返回0
*
*/
uint8_t Set_selectedState_(sGUI * me, uint8_t state)
{
	if (GET_PARA_NUMBER == 0)                         //不要带参数
	{
		return 0;                                       //返回失败
	}
	else                                              //带参数
	{
		GUI_INFO_POINT->selectedState = state;
		return 1;                                       //返回成功
	}
}
	
	

	

/****************************************************************************/
/**
* @brief
*    修改当前选项位置
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    dir                      增减方向
*                                      ADD_DIR  增 
*                                      SUB_DIR  减
*     @arg    offset                   偏移值，需要>0  
*
* @retval None
*          修改成功返回1，失败返回0
*
*/
uint8_t  Modify_currentOption(sGUI * me, uint8_t dir, uint8_t offset)
{
	if (((dir==ADD_DIR) || (dir==SUB_DIR)) && 
		   (offset<GUI_INFO_POINT->maxOption))
	{
			if (dir == ADD_DIR)        
			{ /*增加*/
				GET_CURRENT_OPTION() += offset;
				if (GET_CURRENT_OPTION() >= GUI_INFO_POINT->maxOption)
				{
					GET_CURRENT_OPTION() = GUI_INFO_POINT->maxOption;
				}
			}
			else  if (dir == SUB_DIR)              
			{ /*减少*/
				GET_CURRENT_OPTION() -= offset;
				if (GET_CURRENT_OPTION() <= MIN_OPTION)
				{
					GUI_INFO_POINT->currentOption = MIN_OPTION;
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
*    初始化显示的目录部分
*
* @param  
*     @arg    me                       当前gui对象
*
* @retval 
*          None
*
*/
void  Show_directoryInit_(sGUI * me)
{
	GUIPosition p, p1;	
	const uint8_t ** pstring; 
	uint8_t i;
	p = GUI_INFO_POINT->pGUIDirectory->position;
	if (GUI_INFO_POINT->pGUIDirectory != NULL)
	{	
			i = 0;
			p1 = GUI_INFO_POINT->pGUIDirectory->outRangePosition;
			//tmp = GUI_INFO_POINT->pGUIDirectory->strNumber;
			pstring = GUI_INFO_POINT->pGUIDirectory->pString;
			p = display_(">", p, GUI_INFO_POINT->pGUIDirectory->fontSize,
												NO_SELECT_BLOCK, HORI_DISPLAY);
			while ((*(pstring+i)!=NULL) && (i<MAX_DIRECTORY)) 
			//while ((*(pstring+i)!=NULL) && (i<MAX_DIRECTORY) && (*(tmp+i)!=0))    
			{			
				p = display_(*(pstring+i), p, GUI_INFO_POINT->pGUIDirectory->fontSize, 
													NO_SELECT_BLOCK,HORI_DISPLAY);	
				if ((p.x > p1.x))
				{
					(p.y == p1.y) ? (p1.x -= 24):(p1.y -= 12);
					p1 = display_("...>", p1, GUI_INFO_POINT->pGUIDirectory->fontSize,
												NO_SELECT_BLOCK, HORI_DISPLAY);
					while ((p.x >= p1.x))
					{
						p1 = display_(" ", p1, GUI_INFO_POINT->pGUIDirectory->fontSize,
												NO_SELECT_BLOCK, HORI_DISPLAY);
					}
					break;
				}	
				p = display_(">", p, GUI_INFO_POINT->pGUIDirectory->fontSize,
												NO_SELECT_BLOCK, HORI_DISPLAY);
				i++;
			}
	}
	else
	{
		p = display_(">", p, GUI_INFO_POINT->pGUIDirectory->fontSize,
												NO_SELECT_BLOCK, HORI_DISPLAY);
	}
}



/****************************************************************************/
/**
* @brief
*    更新目录：增加到目录或删除于目录
*
* @param  
*     @arg    me                       当前gui对象
*     @arg    dir                      增减方向
*                                      ADD_DIR  增 
*                                      SUB_DIR  减
*
* @retval None
*
*/
void Updata_directory(sGUI * me, uint8_t dir)
{
		int i = 0;
		GUIDirectory *  directory = GUI_INFO_POINT->pGUIDirectory;
		for (i = 0; i < MAX_DIRECTORY; i++)
			if (*(directory->pString+i)==NULL)
				break;
		if (dir == SUB_DIR)
		{
				/* 删除于目录 */
				if (i > 0)
				{
					*(directory->pString+i-1) = NULL;
				}
		}	
		else
		{
				/* 添加到目录 */
				if (i < MAX_DIRECTORY)
				{
					*(directory->pString+i) = GUI_OPTION_POINT->string;
					i++;
					*(directory->pString+i) = NULL;
				}
		}
}




