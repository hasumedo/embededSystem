/**
  ******************************************************************************
  * @file    sgui.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  
  ******************************************************************************
  * @attention
  *      ���ļ�������sgui�������ֵĺ�����һЩʵ��
	*		  
	*   
  ******************************************************************************
  */

#include "sgui.h"

/****************************************************************************/
/**
* @brief
* 	GUI��ʼ��
*
* @param  
*     @arg    me                       ��ǰ����ָ��
*     @arg    state_table              ָ��״̬��ָ��
*     @arg    initial                  �����ʼ������  
*     @arg    max_sig                  �ź�������
*     @arg    max_state                ״̬������ 
*     @arg    method                   ������Ӧģʽ
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
* 	���õ�ǰҳ��ѡ��״̬
*
* @param  
*     @arg    me                       ��ǰsguiָ��
*     @arg    state                    ����ҳ��ѡ��״̬
*                                       0��ʾδѡ�У�1��ʾѡ��
* @retval 
*          �޸ĳɹ�����1��ʧ�ܷ���0
*
*/
uint8_t Set_selectedState_(sGUI * me, uint8_t state)
{
	if (GET_PARA_NUMBER == 0)                         //��Ҫ������
	{
		return 0;                                       //����ʧ��
	}
	else                                              //������
	{
		GUI_INFO_POINT->selectedState = state;
		return 1;                                       //���سɹ�
	}
}
	
	

	

/****************************************************************************/
/**
* @brief
*    �޸ĵ�ǰѡ��λ��
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    dir                      ��������
*                                      ADD_DIR  �� 
*                                      SUB_DIR  ��
*     @arg    offset                   ƫ��ֵ����Ҫ>0  
*
* @retval None
*          �޸ĳɹ�����1��ʧ�ܷ���0
*
*/
uint8_t  Modify_currentOption(sGUI * me, uint8_t dir, uint8_t offset)
{
	if (((dir==ADD_DIR) || (dir==SUB_DIR)) && 
		   (offset<GUI_INFO_POINT->maxOption))
	{
			if (dir == ADD_DIR)        
			{ /*����*/
				GET_CURRENT_OPTION() += offset;
				if (GET_CURRENT_OPTION() >= GUI_INFO_POINT->maxOption)
				{
					GET_CURRENT_OPTION() = GUI_INFO_POINT->maxOption;
				}
			}
			else  if (dir == SUB_DIR)              
			{ /*����*/
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
*    ��ʼ����ʾ��Ŀ¼����
*
* @param  
*     @arg    me                       ��ǰgui����
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
*    ����Ŀ¼�����ӵ�Ŀ¼��ɾ����Ŀ¼
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    dir                      ��������
*                                      ADD_DIR  �� 
*                                      SUB_DIR  ��
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
				/* ɾ����Ŀ¼ */
				if (i > 0)
				{
					*(directory->pString+i-1) = NULL;
				}
		}	
		else
		{
				/* ��ӵ�Ŀ¼ */
				if (i < MAX_DIRECTORY)
				{
					*(directory->pString+i) = GUI_OPTION_POINT->string;
					i++;
					*(directory->pString+i) = NULL;
				}
		}
}




