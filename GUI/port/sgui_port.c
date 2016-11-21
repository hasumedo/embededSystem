/**
  ******************************************************************************
  * @file    sgui_port.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  ����GUI�Ĺ���ͳ�ʼ�������ӿں���
  ******************************************************************************
  * @attention
  *     ��Ϊ�ӿں��������ļ�����ĺ����ǲ��ɻ�ȱ�ģ�����Ҫ���ݿ�ܶ�������޸ġ�
	*		  
	*   
  ******************************************************************************
  */

#include "sgui_port.h"

/****************************************************************************/
/**
* @brief
* 	GUI���캯��
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
void GUI_ctor(sGUI * me, STATE_HANDLE * state_table, STATE_HANDLE initial,
               uint8_t max_sig, uint8_t max_state, uint8_t mode)
{	
		/*����Ķ�����Ը��ݶ���ͬ��sgui_port�н��к궨��*/
		AOBJECT_CTOR(&me->super, (STATE_HANDLE *)state_table,
										(STATE_HANDLE)initial, max_sig, max_state, mode);
		
}



/****************************************************************************/
/**
* @brief
*    ��ʼ����ʾ�����ɲ�������
*
* @param  
*     @arg    me                       ��ǰgui����
*
* @retval 
*          None
*
*/
static void  Show_freeParaInit_(sGUI * me)
{
	  uint8_t i = 0;

		/*��ʾ���ɲ���*/
		if (GUI_INFO_POINT->freeParaNumber != 0)
		{
				for (i = 0; i < GUI_INFO_POINT->freeParaNumber; i++)
				{	
						Show_valFreePara_(me, i);/*��ֵ���ɲ�����ʾ*/
			
						Show_strFreePara_(me, i);/*���������ɲ�����ʾ*/
						
						Show_timeFreePara_(me, i);/*ʱ�������ɲ�����ʾ*/
				}
		}
}




/****************************************************************************/
/**
* @brief
* 	guiĬ�ϳ�ʼ�����غ���
*
* @param  
*     @arg    me                       ��ǰsgui����
*
* @retval None
*
*/
void GUI_loadInitial(sGUI * me)
{
		uint8_t i = 0;
		uint8_t t;

		/* ��ʾѡ�ѡ����� */
		for (i = 0; i < GUI_INFO_POINT->maxOption; i++)
		{
			(GUI_INFO_POINT->currentOption == i) ? (t=SELECT_BLOCK) : (t=NO_SELECT_BLOCK);

			
			/* ��ʾѡ�� */
			display_(
								N_OPT_ATTRIBUTE_(i)->string,
								N_OPT_ATTRIBUTE_(i)->position,
								N_OPT_ATTRIBUTE_(i)->fontSize, t,
								HORI_DISPLAY
							);
			
			
			/* ����в�������ʾ */
			Show_valParameterInit_(me, i);      /*��ʾ��ֵ���ʼ������*/        
			 
			Show_strParameterInit_(me, i);      /*��ʾ�������ʼ������*/
			
			Show_timeParameterInit_(me, i);    /*��ʾʱ�����ʼ������*/
		
		}
		
		Show_directoryInit_(me);/*��ʼ��Ŀ¼*/
	
		Show_freeParaInit_(me);/*��ʼ�����ɲ���*/
}



/****************************************************************************/
/**
* @brief
* 	��ʾ������������ʾѡ�е�λ��
*
* @param  
*     @arg    me                       ��ǰsgui����
*
* @retval None
*
*/
void 	Display_parameter(sGUI * me)
{	

	Show_valParameter_(me);/*��ʾ��ֵ�����*/
	Show_strParameter_(me); /*��ʾ���������*/	
	Show_timeParameter_(me); /*��ʾʱ�������*/	
	

}
	

