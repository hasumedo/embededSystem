/**
  ******************************************************************************
  * @file    awe_mpool.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  ԭ���ڴ��
  ******************************************************************************
  * @attention
  *    ��������͹����ڴ�أ����ڴ��Ϊԭ���ڴ��
	*		
	*
  ******************************************************************************
  */

#include "awe_ep.h"	
#include "awe_pal.h"	

#ifndef   AWE_MPOOL_H
#define   AWE_MPOOL_H

/**********************************************************/
/*! �ڴ�صĳߴ��С���ֽڵ�λ������Χֵ��1,2,4���ֽڣ�Ĭ��ֵ��2*/	
/**
* @description
* �ú�ָ�������port�ļ��У������� 
*/
#ifndef      AMPOOL_SIZE
	#define    AMPOOL_SIZE      2	         /*���û�ж��壬Ĭ�϶���Ϊ2���ֽ�*/	
#endif 	
	
#if (AMPOOL_SIZE == 1)
	typedef    uint8_t         AMPoolSize;       
#elif  (AMPOOL_SIZE == 2)
	typedef    uint16_t        AMPoolSize;
#elif  (AMPOOL_SIZE == 4)
	typedef    uint32_t        AMPoolSize;
#else
  #error  "memory pool size is outof range!"
#endif



/**********************************************************/
/*! �ڴ�ص�������С����Χֵ��1,2,4���ֽڣ�Ĭ��ֵ��2*/	
/**
* @description
* �ú�ָ�������port�ļ��У������� 
*/
#ifndef      AMPOOL_CRT
	#define    AMPOOL_CRT      2	         /*���û�ж��壬Ĭ�϶���Ϊ2���ֽ�*/	
#endif 	

#if (AMPOOL_CRT == 1)
	typedef    uint8_t         AMPoolCtr;       
#elif  (AMPOOL_CRT == 2)
	typedef    uint16_t        AMPoolCtr;
#elif  (AMPOOL_CRT == 4)
	typedef    uint32_t        AMPoolCtr;
#else
  #error  "memory pool number is outof range!"
#endif



/**********************************************************/
/*! �ڴ�ػ����ṹ  */	
typedef struct AMPoolTag
{
	void * free;        			  /*��ǰ�յ��ڴ��*/
	void * start;      			    /*���ʼ���ڴ��,��Ҫ����׷��*/
	void * end;        			    /*�����ڴ��,��Ҫ����׷��*/
	
	AMPoolSize blockSize; 	    /* �ڴ��Ĵ�С*/
	AMPoolCtr nTot;     		    /* ���е��ڴ������*/
	AMPoolCtr nFree;        		/* �����ڴ��*/
	
}AMPool;
	


/**********************************************************/
/*! �ڴ��ṹ  */	
typedef struct AFreeBlockTag 
{
	struct AFreeBlockTag *next; /* ���ӵ���һ�����п� */
}AFreeBlock;
	



/*! �ڴ�س�ʼ������ */
void AMPool_init(AMPool *me, void *poolSto,uint32_t poolSize, AMPoolSize blockSize);


/*! ���ڴ���еõ�һ���ڴ� */
void *AMPool_get(AMPool *me) ;


/*! ���յ��ڴ�� */
void AMPool_gc(AMPool *me, void *b);





#endif

