/**
  ******************************************************************************
  * @file    sgui.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  �򵥵Ĳ˵�GUI���
  ******************************************************************************
  * @attention
  *     ����GUI���ص㣺
	*        ҳ���Ǿ�̬�ģ��̶�����ģ�,����ͼ�ν��治����ڸ���,��ʾ��ɫ
	*        �Ҳ�֧�ִ�����ֻ֧�ְ���
	*     ��ϸ������ϼ��ĵ�
	*			
	*
  ******************************************************************************
  */
#include "sgui_port.h"

#ifndef   SAMPLE_GUI_H
#define   SAMPLE_GUI_H

/**********************************************************/
/**
 * @description
 *	 GUI�����ṹ
 * @usage
 *   �����̳еĶ�����
 *	 ����״̬��Ϣ
 *   Ŀ¼�ṹ
 */
typedef struct GUITag 
{
		GUI_OBJ super;
		GUI_INFO * state_info;             /* ״̬�Դ���Ϣ*/
	
}sGUI;




/*************************************************************/
/**
 * @description
 *      λ������
 * @usage
 * 		GUIλ�����������
 *
 */
typedef struct GUIPosition
{
	uint16_t  x;
	uint16_t  y;
	
}GUIPosition;



/*************************************************************/
/**
 * @description
 *      ��������
 * @usage
 * 		
 *
 */	
typedef struct ParameterAttribute
{
	  uint8_t      const    parameterType;          /*��ǰ��������, 
	                                                 1��ʾ��ֵ������2��ʾ���ֲ�����3��ʾʱ����Ϣ*/  
}ParameterAttribute;





/*************************************************************/
/**
 * @description
 *      ѡ������
 * @usage
 * 		
 *
 */	
typedef struct OptionAttribute
{
		/* ���䲿����Ϣ */
		const uint8_t         fontSize;               /*�����С*/	
		const uint8_t * const string;                 /*��ʾ�ַ���*/
		const uint8_t         reserved;               /*�������Ҫ�����Ŀ¼����ָ��*/
		const GUIPosition     position;               /*��ʾ�ַ�λ��*/	
		
		/*ѡ������������Ϣ*/
	  const uint8_t         para_num;               /*ѡ����������������0Ϊ��������*/	
		const ParameterAttribute *  const  para;      /*ѡ���Ӧ��ָ�����ָ��,
	                                                   ������ָ����ΪNULLָ��*/   
           
}OptionAttribute;
	




/*************************************************************/
/**
 * @description
 *    Ŀ¼�ṹ
 * @usage
 * 		
 *
 */
typedef struct GUIDirectory
{
		const uint8_t  *      pString[MAX_DIRECTORY];          /*Ŀ¼����,�����β�����MAX_DIRECTORY*/
		const uint8_t         fontSize;                        /*�����С*/	
		const GUIPosition     position;                        /*��ʾ�ַ�λ��*/	
		const GUIPosition     outRangePosition;                /*����Χ�ַ�λ�ã�������...����*/	 
	
}GUIDirectory;




/*************************************************************/
/**
 * @description
 *    Sample GUI״̬�������ԵĶ���
 * @usage
 * 		ÿ��ҳ�涼��Ҫ��һ��GUIStateInfo���͵Ĳ�����Ϊ��ҳ������
 *
 */
typedef struct GUIStateInfo
{
		const GUI_INFO         super;                            /*״̬�������Լ̳�*/
		const uint8_t          maxOption;                        /*��ǰҳ�棨״̬��������ѡ��*/
		int8_t                 currentOption;                    /*��ǰѡ��ѡ��λ��  0 ��ʾδѡ�У���һ��Ĭ�� NULL
	                                                               1 ��ʾѡ���߼�˳���ϵĵ�һ��  */	
		uint8_t                selectedState;                    /*�Ƿ���ѡ��״̬, 0��ʾδѡ�У�1��ʾѡ��*/ 
		const OptionAttribute * const  pContent;                 /*Ϊÿ��ѡ���ж�Ӧ�����ݣ�ָ��ָ�����飬
	                                                              �ڴ���ʱ�Զ��󶨵�����*/
		GUIDirectory     *     pGUIDirectory;                    /*ҳ���Դ�Ŀ¼*/               
		const ParameterAttribute **   pFreeParameter;            /*ҳ���Դ������ɲ���*/
		const uint8_t          freeParaNumber;                   /*���ɲ�������*/	 
	 
}GUIStateInfo; 


/*************************************************************/
/*! ��������  */
#define  ADD_DIR                            1
#define  SUB_DIR                            0


/*************************************************************/
/*! ��ȡ��ǰҳ����Ϣָ��  */	
#define  GUI_INFO_POINT          	         ((GUIStateInfo *)(me->state_info))

/*! ��ȡ��ǰѡ��ָ��*/	
#define  GUI_OPTION_POINT                  (N_OPT_ATTRIBUTE_(GUI_INFO_POINT->currentOption))

/*! ��ȡ�������� 0Ϊ�������� */	
#define  GET_PARA_NUMBER                   (GUI_OPTION_POINT->para_num)

/*! ��ȡ��ǰҳ�浱ǰѡ��ѡ��Ĳ�������*/ 
#define  GET_PARA_TYPE                  	 (GUI_OPTION_POINT->para->parameterType)	


/*************************************************************/																		
/*! ��ȡ��ǰҳ���i��ѡ�������ָ�룬��0��Ĭ��ΪNULL */	
#define  N_OPT_ATTRIBUTE_(i_)               (GUI_INFO_POINT->pContent+i_)


/*! ��ȡ��ǰҳ���i��ѡ���ѡ��ѡ��Ĳ������ͣ� 
   1��ʾ��ֵ������2��ʾ���ֲ���*/	
#define  GET_N_PARA_TYPE_(i_)            	  (N_OPT_ATTRIBUTE_(i_)->para->parameterType)					


/*************************************************************/
/*! ���õ�ǰҳ����Ϣָ��,�ɹ�����1�����ɹ�����0  */	
uint8_t  Set_selectedState_(sGUI * me, uint8_t state);



/*************************************************************/
/*! �л���ҳ�� */	
#define  TRANS_PAGE(target_)              (me->state_info = (GUI_INFO *)GUI_Infomation[target_],\
                                            GUI_INFO_POINT->selectedState = 0,\
																						PAGE_TRANS(target_))

/*!  ���ı�ҳ��*/
#define  HANDLED_PAGE()                    PAGE_HANDLED()


/*************************************************************/
/*! ��ȡ��ǰ�Ƿ���ѡ��ѡ��״̬ 
   �������в����ģ����޲����򷵻صĶ���0��δѡ�У�*/	
#define  GET_SELECTED_STATE()              (GUI_INFO_POINT->selectedState)

/*! ���õ�ǰѡ��������ò���״̬,����ֵ�ǳɹ�Ϊ1�����ɹ�Ϊ0  */	 
#define  ENTER_SET_PARAMETER()             (Set_selectedState_(me, (uint8_t)1)) 

/*! ���õ�ǰѡ���˳����ò���״̬,����ֵ�ǳɹ�Ϊ1�����ɹ�Ϊ0  */	 
#define  EXIT_SET_PARAMETER()              (Set_selectedState_(me, (uint8_t)0))



/*************************************************************/
/*! ��С��ֵѡ���Ĭ��Ϊ1 */
#define  MIN_OPTION                              1 

/*! ��ȡ��ǰѡ��λ��  */	
#define  GET_CURRENT_OPTION()              (GUI_INFO_POINT->currentOption)

/*! ��ȡ���ѡ���� */
#define  GET_MAX_OPTION()                  (GUI_INFO_POINT->maxOption-(uint8_t)1)

/*! �޸ĵ�ǰѡ��λ�ã� �޸ĳɹ�����1��ʧ�ܷ���0  */	
uint8_t  Modify_currentOption(sGUI * me, uint8_t dir, uint8_t offset);
		


/*************************************************************/
/*!    GUI��ʼ��    */
void GUI_initial(sGUI * me, AEvt const *e);



/*************************************************************/
/*! ����Ŀ¼������ǰ·�����ӵ�Ŀ¼��ɾ����Ŀ¼ */
void Updata_directory(sGUI * me, uint8_t dir);



/*************************************************************/
/*! ��ʼ����ʾ��Ŀ¼����*/
void  Show_directoryInit_(sGUI * me);





#endif
	
	
	
	
	
	
	
	
	
