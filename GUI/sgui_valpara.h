/**
  ******************************************************************************
  * @file    sgui_valpara.h
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
#include "sgui_port.h"

#ifndef   SGUI_VAL_PARA_H_
#define   SGUI_VAL_PARA_H_

/*************************************************************/
/*! ���ͺ� */	
enum 
{
	BOOL,
	CHAR,
	UNSIGNED_CHAR,
	INT,
	UNSIGNED_INT,
	FLOAT,
	DOUBLE
};


/*************************************************************/
/*! ��ֵ��������� */		
typedef struct Val_ParameterAttribute
{
		ParameterAttribute    super;                  /*�̳���ֵ���������*/		
	  int8_t                currentSelect;          /*��ǰѡ�в�����λ��*/  
		uint8_t *     const   parameterStr;           /*�����ַ���*/
		uint8_t       const   storeType;              /*�洢����*/
		uint8_t       const   fontSize;               /*�����С*/	
		GUIPosition   const   paraPosition;           /*��ǰ����*/
}Val_ParameterAttribute;





/*************************************************************/
/*! ��ǰҳ���i��ѡ��Ĳ�������ת��  */	
#define  VLA_PARA_POINT_(i_)                ((Val_ParameterAttribute *)(N_OPT_ATTRIBUTE_(i_)->para))



/*************************************************************/
/*! ��ȡ����ָ��,(����Ĭ��ÿ����������һ������) */	
#define  GUI_VLA_PARA_POINT                 ((Val_ParameterAttribute *)(GUI_OPTION_POINT->para))



/*************************************************************/
/*! �жϲ�������*/
#define  IS_VAL_PARAMETER()                 (GET_PARA_TYPE == VALUE_PARAMETER)



/*************************************************************/
/*! ��ȡ��ǰѡ����ֵ�Ͳ���λ��  */	
#define  GET_VAL_PARA_SELECTION()           (GUI_VLA_PARA_POINT->currentSelect)



/*************************************************************/
/*! ��ȡ�洢����  */	
#define  GET_VAL_PARA_TYPE()                (GUI_VLA_PARA_POINT->storeType)



/*************************************************************/
/*! ��ȡ�����ַ���  */	
#define  GET_VAL_PARA_STRING()              (GUI_VLA_PARA_POINT->parameterStr)



/*************************************************************/
/*! ��ʼ����ʾ����ֵ�������� */
void  Show_valParameterInit_(sGUI * me, uint8_t i);


/*! ������ʾ����ֵ�������� */
void  Show_valParameter_(sGUI * me);

/*! ���ɲ�����ʾ */
void  Show_valFreePara_(sGUI * me, uint8_t i);

/*************************************************************/
/*!	�޸ĵ�ǰѡ�в���λ�� �޸ĳɹ�����1��ʧ�ܷ���0   */	
uint8_t  Modify_valueCurrentSelected(sGUI * me, uint8_t dir, uint8_t offset);




/*---------------------------------------------------------------------------------------------*/
/*************************************************************/
/*! �����޸ĵĹ��߰� */
/*!	��ֵת�����ַ���  */	
void  Val2String(uint8_t * str, uint8_t type, uint8_t dirction, uint8_t bit);





#endif



