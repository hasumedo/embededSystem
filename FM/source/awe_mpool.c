/**
  ******************************************************************************
  * @file    awe_mpool.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  ԭ���ڴ��
  ******************************************************************************
  * @attention
  *    ��������͹����ڴ�أ����ڴ��Ϊԭ���ڴ��
	*		�ڳ�ʼ����ʱ��ͷ���������ݿ顣����ȥ��ֱ��ʹ�á�
	*
  ******************************************************************************
  */
#include  "awe_mpool.h"

	
/*! �ڴ�س�ʼ������ */	
void AMPool_init(AMPool *me, void *poolSto,
									uint32_t poolSize, AMPoolSize blockSize)
{
		AFreeBlock *fb;
		uint32_t corr;
		uint32_t nblocks;
	
		/* �洢������Ч
		* �صĴ�С�������һ�����п��С
		* ���С���벻��̫������̬��Χ�Ķ���
		*/
// 		Q_REQUIRE((poolSto != (void *)0)
// 		&& (poolSize >= (uint32_t)sizeof(QFreeBlock))
// 		&& ((QMPoolSize)(blockSize + (QMPoolSize)sizeof(QFreeBlock)) > blockSize));	
	
		/* ����ָ���Ƿ���� */	
		corr = ((uint32_t)poolSto & ((uint32_t)sizeof(AFreeBlock) - (uint32_t)1));
		if (corr != (uint32_t)0) 
		{ /* δ������� */
				corr = (uint32_t)sizeof(AFreeBlock) - corr;/*�������ָ�� */
				poolSize -= corr; /* ������Ч�صĴ�С */
		}
		
		/*��ͷָ��ŵ�������еı߽���*/
		me->free = (void *)((uint8_t *)poolSto - corr); //Դ������Ǽӣ��о����
		
		/* ʵ�����п�Ķ��� */
		me->blockSize = (AMPoolSize)sizeof(AFreeBlock);
		nblocks = (uint32_t)1; /*���п�ռһ���ڴ��*/
		while (me->blockSize < blockSize) 
		{
				me->blockSize += (AMPoolSize)sizeof(AFreeBlock);
				++nblocks;
		}
		blockSize = me->blockSize; 
		
		/*�����������Ӧһ�������Ŀ� */
// 		Q_ASSERT(poolSize >= (uint32_t)blockSize);
		/* ��һ�������������������ɿ�. */
		poolSize -= (uint32_t)blockSize;/*���һ�����Next������ */
		me->nTot = (AMPoolCtr)1; /*���һ���ڴ���Ѿ��ڳ���*/
		fb = (AFreeBlock *)me->free;/*�Կ����б�ͷ��ʼ */
		while (poolSize >= (uint32_t)blockSize) 
		{ /* �ܷ���Ӧ��һ���� */
				fb->next = &fb[nblocks]; /* ָ�����ӵ���һ���� */
				fb = fb->next; 
				poolSize -= (uint32_t)blockSize; /* ������Ч�صĳߴ� */
				++me->nTot; /*���ӿ������ */
		}		
		
		fb->next = (AFreeBlock *)0; /* ���һ������ָ��ָ��NULL */
		me->nFree = me->nTot; /* ���п鶼�ǿ��е� */
		me->start = poolSto; /* �ػ������ʼ */
		me->end = fb; /* �������µ�һ���� */
	
		
}
		



/*! ���ڴ���еõ�һ���ڴ� */
/* �ڴ�������˷���NULL*/
void *AMPool_get(AMPool *me) 
{
		AFreeBlock *fb;
		AWE_INT_LOCK_KEY_
		AWE_INT_LOCK_();    /* �������� */
		fb = (AFreeBlock *)me->free; /* �õ�һ�����п���ָ�� */
		if (fb != (AFreeBlock *)0) 
		{ /* ���п� */
			me->free = fb->next; 
			--me->nFree;
		}
		AWE_INT_UNLOCK_(); /* ���� */
		return fb; /* �Żؿ�ָ����ָ�� */
		
}	




		
/*! ���յ��ڴ�� */
void AMPool_gc(AMPool *me, void *b) 
{
	AWE_INT_LOCK_KEY_
	//Q_REQUIRE((me->start <= b) && (b <= me->end) /* ��֤���ݵ���Ч�� */
	//		&& (me->nFree <= me->nTot));
	AWE_INT_LOCK_();    /* �������� */
	((AFreeBlock *)b)->next = (AFreeBlock *)me->free;/* ���ӵ���һ��ָ�� */
	me->free = b; /* Ϊ�����б�����һ����ͷ */
	++me->nFree; /* ����һ�����п���� */
	AWE_INT_UNLOCK_(); /* ���� */
	
}	
		
		
		



