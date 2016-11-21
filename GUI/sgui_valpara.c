  /******************************************************************************
  * @file    sgui_valpara.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  �򵥵Ĳ˵�GUI ��ֵ��������
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
*    �޸���ʾ����ֵ����
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
uint8_t  Modify_valueCurrentSelected(sGUI * me, uint8_t dir, uint8_t offset)
{
		if (IS_VAL_PARAMETER())
		{
				if (dir == ADD_DIR)        //��
				{
						GUI_VLA_PARA_POINT->currentSelect += offset;
						if (GET_VAL_PARA_SELECTION() > DEFAULT_MAX_DATALEN)
						{
							GUI_VLA_PARA_POINT->currentSelect = 0;
						}
				}
				else if (dir == SUB_DIR)                //��
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
*    ��ʼ����ʾ����ֵ��������
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    i                        ��i������
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
				/* ��ʾ���� */
				displayASC_(
											val_para->parameterStr, 
											val_para->paraPosition,
											val_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
											HORI_DISPLAY
										);
			}
	
}
	
	
	
/****************************************************************************/
/**
* @brief
*    ������ʾ����ֵ��������
*
* @param  
*     @arg    me                       ��ǰgui����
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
*    ��ֵ���ɲ�����ʾ
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    i                        ��i������
*
* @retval 
*          None
*
*/
void  Show_valFreePara_(sGUI * me, uint8_t i)
{
	Val_ParameterAttribute * val_para;
	/* �жϵ�ǰ�Ƿ��в��� ,���������ʾ */
	if (GUI_INFO_POINT->pFreeParameter[i]->parameterType == VALUE_PARAMETER)
	{
		val_para = (Val_ParameterAttribute *)(GUI_INFO_POINT->pFreeParameter[i]);
		/* ��ʾ���� */
		displayASC_(
									val_para->parameterStr, 
									val_para->paraPosition,
									val_para->fontSize, NO_SELECT_BLOCK,      //Ĭ��״̬����ѡ��
									HORI_DISPLAY
								);
	}
	
}




/*---------------------------------------------------------------------------------------------*/
/*! �����޸ĵĹ��߰� */

/****************************************************************************/
/**
* @brief
*    ��ֵת�����ַ���
*
* @param  
*     @arg    me                       ��ǰgui����
*     @arg    i                        ��i������
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
			/*����*/
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
				/*����ǿհ�λ������,����λ��Ĭ������0�����*/
				for (i = bit+1; i < DEFAULT_MAX_DATALEN; i++)  //��0λ��ʼ
				{
					if (*str == ' ')
						*str++ = '0';
					else
						break;
				}
				
				/*�����ͷ�ǲ���ȫ��0����0����*/
				if ((type == FLOAT) || (type == DOUBLE))
				{
				//	t = DEFAULT_POINT_BIT - 1;
				}
				else
				{
					t = DEFAULT_MAX_DATALEN;
				}
				for (i = 0; i < t; i++)  //��0λ��ʼ
				{
					if (*str == ' ')
						*str++ = ' ';
					else
						break;
				}
		}
	
}

