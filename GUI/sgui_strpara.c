/**
  ******************************************************************************
  * @file    sgui_strpara.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  �򵥵Ĳ˵�GUI ���ֲ�������
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
*    �޸���ʾ���ַ�����
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    dir                      ��������
*                                      ADD_DIR  �� 
*                                      SUB_DIR  ��
*
* @retval 
*          �޸ĳɹ�����1��ʧ�ܷ���0
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
*    ��ʼ����ʾ���ַ���������
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    i                        ��i������
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
					/* ��ʾ���� */
					display_(
												str_para->parameterStr[str_para->currOptionNum], 
												str_para->paraPosition,
												str_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
												HORI_DISPLAY
											);
					
					/* ��ʾ���Ӳ��� */
					if (str_para->added_instruction != NULL)
					{		
						display_(
											str_para->added_instruction[str_para->currOptionNum],
											str_para->instructionPositon,
											str_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
											HORI_DISPLAY
										);
					}			
			}		
}




/****************************************************************************/
/**
* @brief
*    ������ʾ���ַ���������
*
* @param  
*     @arg    me                       ��ǰgui����
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
			
			/* ������Ϣ*/
			if (str_para->added_instruction != NULL)
			{		
				display_(
									str_para->added_instruction[str_para->currOptionNum], 
									str_para->instructionPositon,
									str_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
									HORI_DISPLAY
								);
			}
	}		



}
	

/****************************************************************************/
/**
* @brief
*    �����������ɲ�����ʾ
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    i                        ��i������
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
			/* ��ʾ���� */
			display_(
								str_para->parameterStr[str_para->currOptionNum],
								str_para->paraPosition,
								str_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
								HORI_DISPLAY
							);
			
			/* ��ʾ���Ӳ��� */
			if (str_para->added_instruction != NULL)
			{		
				display_(
									str_para->added_instruction[str_para->currOptionNum], 
									str_para->instructionPositon,
									str_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
									HORI_DISPLAY
								);
			}			
	}		
	
}






