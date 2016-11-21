/**
  ******************************************************************************
  * @file    sgui_strpara.h
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
#include "sgui_port.h"

#ifndef   SGUI_STR_PARA_H_
#define   SGUI_STR_PARA_H_



/*************************************************************/
/*! ������������� */		
typedef struct Str_ParameterAttribute
{
		ParameterAttribute    super;                  /*�̳���ֵ���������*/
	  const uint8_t    **   parameterStr;           /*��ʾ���ַ���ָ������,
																										������ñ�֤ÿ������������һ��*/
		uint8_t       const   maxOptionNum;           /*�������ѡ��*/
		int8_t                currOptionNum;          /*��ǰ����˳��*/
		uint8_t       const   fontSize;               /*�����С*/	
		GUIPosition   const   paraPosition;           /*��ǰ����*/	  
	
    /* ����˵�� */
		GUIPosition   const   instructionPositon;      /*����˵����ʾ����ʼλ��*/	
		const uint8_t **      added_instruction;       /*����˵��
																										������ñ�֤ÿ������������һ��*/
																						
}Str_ParameterAttribute;



/*************************************************************/
/*! ��ǰҳ���i��ѡ��Ĳ�������ת��  */	
#define  STR_PARA_POINT_(i_)		    	      ((Str_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para))  


/*************************************************************/
/*! ��ȡ����ָ��,(����Ĭ��ÿ����������һ������) */	
#define  GUI_STR_PARA_POINT				         ((Str_ParameterAttribute *)(GUI_OPTION_POINT->para)) 


/*************************************************************/
/*! �жϲ�������*/
#define  IS_STR_PARAMETER()                (GET_PARA_TYPE == STRING_PARAMETER)

/*************************************************************/
/* ��ʼ����ʾ���ַ��������� */
void  Show_strParameterInit_(sGUI * me, uint8_t i);

/* ������ʾ���ַ��������� */
void  Show_strParameter_(sGUI * me);

/* �����������ɲ�����ʾ */
void  Show_strFreePara_(sGUI * me, uint8_t i);


/*************************************************************/
/*! �ı�����ѡ�����,����Ϊ1  */	
uint8_t  Modify_stringParameter(sGUI * me, uint8_t dir);





#endif

