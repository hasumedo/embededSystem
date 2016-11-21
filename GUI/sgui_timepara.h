/**
  ******************************************************************************
  * @file    sgui_timepara.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  �򵥵Ĳ˵�GUI ʱ���������
  ******************************************************************************
  * @attention
  *     
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SGUI_TIME_PARA_H_
#define   SGUI_TIME_PARA_H_


/*************************************************************/
/*! ʱ����������� */		
typedef struct Time
{
		ParameterAttribute    super;                  /*�̳���ֵ���������*/		
	  int8_t                currentSelect;          /*��ǰ������ʱ����ѡ��*/ 
		int8_t                currentbit;             /*��ǰѡ��λ��*/
		uint8_t       const   paraFontSize;           /*���������С*/	
		uint16_t              time[6];                /*ʱ��*/
		GUIPosition const * const  paraPosition;		  /*ʱ���ַ���ʾλ��*/
}Time_ParameterAttribute;


/*************************************************************/
/*! ��ǰҳ���i��ѡ��Ĳ�������ת��  */	
#define  TIME_PARA_POINT_(i_)		    	      ((Time_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para)) 


/*************************************************************/
/*! ��ȡ����ָ��,(����Ĭ��ÿ����������һ������) */	
#define  GUI_TIME_PARA_POINT				       ((Time_ParameterAttribute *)(GUI_OPTION_POINT->para)) 


/*************************************************************/
/*! �жϲ�������*/
#define  IS_TIME_PARAMETER()               (GET_PARA_TYPE == TIME_PARAMETER)


/*************************************************************/
/*! ��ʼ����ʾ��ʱ���������*/	
void  Show_timeParameterInit_(sGUI * me, uint8_t i);

/*! �ı�ʱ�䵱ǰѡ��λ */	
void  Modify_timeCurrentBit(sGUI * me, uint8_t dir);

/*! ����ʱ�� */	
void  Modify_timeParameter(sGUI * me, uint8_t dir);

/*! ʱ���������ɲ�����ʾ  */	
void  Show_timeFreePara_(sGUI * me, uint8_t i);


/*************************************************************/
/*! ������ʾ�����ֲ�������  */	
void  Show_timeParameter_(sGUI * me);


#endif

