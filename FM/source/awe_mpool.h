/**
  ******************************************************************************
  * @file    awe_mpool.h
  * @author  
  * @version V1.0
  * @date    
  * @brief  原生内存池
  ******************************************************************************
  * @attention
  *    用来分配和管理内存池，该内存池为原生内存池
	*		
	*
  ******************************************************************************
  */

#include "awe_ep.h"	
#include "awe_pal.h"	

#ifndef   AWE_MPOOL_H
#define   AWE_MPOOL_H

/**********************************************************/
/*! 内存池的尺寸大小（字节单位），范围值是1,2,4个字节，默认值是2*/	
/**
* @description
* 该宏指令可以在port文件中（）配置 
*/
#ifndef      AMPOOL_SIZE
	#define    AMPOOL_SIZE      2	         /*如果没有定义，默认定义为2个字节*/	
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
/*! 内存池的数量大小，范围值是1,2,4个字节，默认值是2*/	
/**
* @description
* 该宏指令可以在port文件中（）配置 
*/
#ifndef      AMPOOL_CRT
	#define    AMPOOL_CRT      2	         /*如果没有定义，默认定义为2个字节*/	
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
/*! 内存池基本结构  */	
typedef struct AMPoolTag
{
	void * free;        			  /*当前空的内存块*/
	void * start;      			    /*最初始的内存块,主要用来追踪*/
	void * end;        			    /*最后的内存块,主要用来追踪*/
	
	AMPoolSize blockSize; 	    /* 内存块的大小*/
	AMPoolCtr nTot;     		    /* 所有的内存块数量*/
	AMPoolCtr nFree;        		/* 空闲内存块*/
	
}AMPool;
	


/**********************************************************/
/*! 内存块结构  */	
typedef struct AFreeBlockTag 
{
	struct AFreeBlockTag *next; /* 连接到下一个空闲块 */
}AFreeBlock;
	



/*! 内存池初始化函数 */
void AMPool_init(AMPool *me, void *poolSto,uint32_t poolSize, AMPoolSize blockSize);


/*! 从内存池中得到一块内存 */
void *AMPool_get(AMPool *me) ;


/*! 回收到内存池 */
void AMPool_gc(AMPool *me, void *b);





#endif

