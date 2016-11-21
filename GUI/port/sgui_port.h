/**
  ******************************************************************************
  * @file    sgui_port.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ����GUI�Ľӿ�ͷ�ļ�
  ******************************************************************************
  * @attention
  *     
	*		  
	*   
  ******************************************************************************
  */
	
#ifndef   SGUI_PORT_H
#define   SGUI_PORT_H


/*************************************************************/
/*! GUI������Ϣƫ��ID */	
#define       GUI_INFOID       200

/*************************************************************/
/*! ������Ŀ¼�� */
#define  MAX_DIRECTORY                           5

/*************************************************************/
/*! Ĭ���������λ�� */
#define   DEFAULT_MAX_DATALEN                    7     

/*************************************************************/
/*! ���еĲ������� */
enum 
{
	VALUE_PARAMETER = 1,
	STRING_PARAMETER,
	TIME_PARAMETER       
};

/*************************************************************/
/*! �̳ж����  */
#define   GUI_OBJ                                        AObj        
#define   STATE_HANDLE                                   AStateHandler
#define   GUI_INFO                                       AInfo
#define   PAGE_TRANS(target_)                            A_TRANS(target_)
#define   PAGE_HANDLED()                                 A_HANDLED()



/*************************************************************/
/*! �����������Ӷ����ܺ� */
#define   AOBJECT_CTOR(me, state_table, initial,              \
					max_sig, max_state, method)                         \
																	                       Aobj_ctor(me, state_table, initial,\
																	                       max_sig, max_state, method)
		

/*************************************************************/
/*! ����GUI�Ĵ�����ͳ�ʼ���� */
#define   SGUI_initial(me, e)      Interface_intial(me, e)
#define   SGUI_ctor(me)            Interface_ctor(me)      



/*************************************************************/
/* �������ͷ�ļ�*/
#include "awe_fm_port.h"


/*! ����sguiͷ�ļ� */
#include  "sgui.h"


/*! ����sgui�е�һЩ�������ͷ�ļ� */
#include  "sgui_valpara.h"
#include  "sgui_timepara.h"
#include  "sgui_strpara.h"


/*! BSPҺ����ʾͷ�ļ� */
#include "BSP_display.h"


/*************************************************************/
/*! BSP�ӿ� */
/*! ��ʾ�ַ��ͺ��ֻ�ϵ���ʾ�ӿ� */
#define  display_(str_, p_, size_, selBlock_, dir_)        \
														       	BSP_display(str_, p_, size_, selBlock_, dir_)


/*! ֻ��ʾASCII����ʾ�ӿ� */
#define  displayASC_(str_, p_, size_, selBlock_, dir_)        \
														       	BSP_ASCDisplay(str_, p_, size_, selBlock_, dir_)


/*************************************************************/
/*!    �ӿ�����    */
/*!    GUI���캯��    */
void GUI_ctor(sGUI * me,  STATE_HANDLE *state_table, STATE_HANDLE GUI_initial,
               uint8_t max_sig, uint8_t max_state, uint8_t mode);


/*!  guiĬ�ϳ�ʼ�����غ��� */
void GUI_loadInitial(sGUI * me);


/*! ��ʾ������������ʾѡ�е�λ��*/
void 	Display_parameter(sGUI * me);




#endif





