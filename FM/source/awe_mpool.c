/**
  ******************************************************************************
  * @file    awe_mpool.c
  * @author  
  * @version V1.0
  * @date    
  * @brief  原生内存池
  ******************************************************************************
  * @attention
  *    用来分配和管理内存池，该内存池为原生内存池
	*		在初始化的时候就分配好了数据块。接下去可直接使用。
	*
  ******************************************************************************
  */
#include  "awe_mpool.h"

	
/*! 内存池初始化函数 */	
void AMPool_init(AMPool *me, void *poolSto,
									uint32_t poolSize, AMPoolSize blockSize)
{
		AFreeBlock *fb;
		uint32_t corr;
		uint32_t nblocks;
	
		/* 存储必须有效
		* 池的大小必须大于一个空闲块大小
		* 块大小必须不能太靠近动态范围的顶端
		*/
// 		Q_REQUIRE((poolSto != (void *)0)
// 		&& (poolSize >= (uint32_t)sizeof(QFreeBlock))
// 		&& ((QMPoolSize)(blockSize + (QMPoolSize)sizeof(QFreeBlock)) > blockSize));	
	
		/* 计算指针是否对齐 */	
		corr = ((uint32_t)poolSto & ((uint32_t)sizeof(AFreeBlock) - (uint32_t)1));
		if (corr != (uint32_t)0) 
		{ /* 未对齐情况 */
				corr = (uint32_t)sizeof(AFreeBlock) - corr;/*计算对齐指针 */
				poolSize -= corr; /* 减少有效池的大小 */
		}
		
		/*把头指针放到最近空闲的边界上*/
		me->free = (void *)((uint8_t *)poolSto - corr); //源码这块是加，感觉像减
		
		/* 实现所有块的对齐 */
		me->blockSize = (AMPoolSize)sizeof(AFreeBlock);
		nblocks = (uint32_t)1; /*空闲块占一个内存块*/
		while (me->blockSize < blockSize) 
		{
				me->blockSize += (AMPoolSize)sizeof(AFreeBlock);
				++nblocks;
		}
		blockSize = me->blockSize; 
		
		/*缓冲池至少适应一个完整的块 */
// 		Q_ASSERT(poolSize >= (uint32_t)blockSize);
		/* 在一个自由链表中连接自由块. */
		poolSize -= (uint32_t)blockSize;/*最后一个块的Next不连接 */
		me->nTot = (AMPoolCtr)1; /*最后一个内存块已经在池中*/
		fb = (AFreeBlock *)me->free;/*以空闲列表头开始 */
		while (poolSize >= (uint32_t)blockSize) 
		{ /* 能否适应另一个块 */
				fb->next = &fb[nblocks]; /* 指向连接的下一个块 */
				fb = fb->next; 
				poolSize -= (uint32_t)blockSize; /* 减少有效池的尺寸 */
				++me->nTot; /*增加块的数量 */
		}		
		
		fb->next = (AFreeBlock *)0; /* 最后一个连接指针指向NULL */
		me->nFree = me->nTot; /* 所有块都是空闲的 */
		me->start = poolSto; /* 池缓冲的起始 */
		me->end = fb; /* 池中最新的一个块 */
	
		
}
		



/*! 从内存池中得到一块内存 */
/* 内存池用完了返回NULL*/
void *AMPool_get(AMPool *me) 
{
		AFreeBlock *fb;
		AWE_INT_LOCK_KEY_
		AWE_INT_LOCK_();    /* 加锁保护 */
		fb = (AFreeBlock *)me->free; /* 得到一个空闲块或空指针 */
		if (fb != (AFreeBlock *)0) 
		{ /* 空闲块 */
			me->free = fb->next; 
			--me->nFree;
		}
		AWE_INT_UNLOCK_(); /* 解锁 */
		return fb; /* 放回块指针或空指针 */
		
}	




		
/*! 回收到内存池 */
void AMPool_gc(AMPool *me, void *b) 
{
	AWE_INT_LOCK_KEY_
	//Q_REQUIRE((me->start <= b) && (b <= me->end) /* 保证数据的有效性 */
	//		&& (me->nFree <= me->nTot));
	AWE_INT_LOCK_();    /* 加锁保护 */
	((AFreeBlock *)b)->next = (AFreeBlock *)me->free;/* 链接到下一个指针 */
	me->free = b; /* 为空闲列表设置一个新头 */
	++me->nFree; /* 增加一个空闲块计数 */
	AWE_INT_UNLOCK_(); /* 解锁 */
	
}	
		
		
		



