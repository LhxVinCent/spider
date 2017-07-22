#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>

struct job{
void* (*CallBack_Function)(void* arg);
struct job* next;
};


struct threadpool{
int thread_num;//线程中开启的线程个数
int queue_max_num;//队列中最大job的个数
struct job *head;//指向job的头指针
struct job *tail;//指向job的尾指针
pthread_t *pthreads;//线程池中所有线程的pthread_t
pthread_mutex_t mutex;//互斥信号量
pthread_cond_t queue_empty;//队列为空的条件变量
pthread_cond_t queue_not_full;//队列为满的条件变量
pthread_cond_t queue_not_empty;//队列中非满的条件变量

int queue_cur_num;//当前队列中的job个数
int queue_close;//队列是否已经关闭
int thread_pool_close;//线程池中所有线程的

};

struct threadpool* ThreadPool_Init(int thread_num,int queue_max_num)
{
    struct threadpool* pool=NULL;
   do
   { pool=(struct threadpool*)malloc(sizeof(struct threadpool));
	if(pool==NULL)
	{
       printf("failed to malloc threadpool!\n");
	}
    
	pool->thread_num=thread_num;
	pool->queue_max_num=queue_max_num;
	pool->queue_cur_num=0;
    pool->head=NULL;
	pool->tail=NULL;
	if(pthread_mutex_init(&(pool->mutex),NULL))
	{
        printf("failed to init mutex!\n");
	    break;
	}

    if(pthread_cond_init(&(pool->queue_empty),NULL))
	{
     printf("failed to init queue_empty!\n");
	 break;
	}
	if(pthread_cond_init(&(pool->queue_not_empty),NULL))
	{
     printf("failed to init queue_not_empty!\n");
	 break;
	}
	if(pthread_cond_init(&(pool->queue_not_full),NULL))
	{
      printf("failed to init queue_not_full!\n");
	  break;
	}
	pool->pthreads=(pthread_t*)malloc(sizeof(pthread_t)*thread_num);
	if(pool->pthreads==NULL)
	{
      printf("failed to malloc phreads!\n");
	  break;
	}
	pool->queue_close=0;
	pool->thread_pool_close=0;
	{

       int i;
	   for(i=0;i<pool->thread_num;++i)
	   {
         pthread_create(&(pool->pthreads[i]),NULL,threadpool_function,(void*)pool);


	   }
	   return pool;
	}
   }while(0);
   return NULL;

}


void* threadpool_function(void* arg)
{
   struct threadpool* pool=(struct threadpool*)arg;

   struct job* pjob=NULL;
   while(1)
   {
     pthread_mutex_lock(&(pool->mutex));
	 while((pool->queue_cur_num==0)&&!pool->thread_pool_close)
	 {
        pthread_cond_wait(&(pool->queue_not_empty),&(pool->mutex));

	 }

	 if(pool->thread_pool_close)
	 {
       pthread_mutex_unlock(&(pool->mutex));
	   pthread_exit(NULL);

	 }

	 pool->queue_cur_num--;
	 pjob=pool->head;
	 if(pool->queue_cur_num==0)
	 {
       pool->head=pool->tail=NULL;
	 }else
	 {
       pool->head=pjob->next;`
	 }
	 if(pool->queue_cur_num==0)
	 {
      pthread_cond_signal(&(pool->queue_empty));//队列为空,通知threadpool_destroy函数,销毁线程函数
	 }

	 if(pool->queue_cur_num==pool->queue_max_num-1)
       {
          pthread_cond_broadcast(&(pool->queue_not_full));//队列非满,通知threadpool_add_job函数添加新任务

	   }
	 pthread_mutex_unlock(&(pool->mutex));
	 (*(pjob->CallBack_Function))(pjob->arg);
	 free(pjob);
	 pjob=NULL;
     
   }
}

int threadpool_add_job(struct threadpool* pool,void* (*CallBack_Function)(void*arg),void* arg)
{
  assert(pool!=NULL);
  assert(CallBack_Function!=NULL);
  assert(arg!=NULL);
  pthread_mutex_lock(&(pool->mutex));
  while((pool->queue_cur_num==pool->queue_max_num)&&!(pool->queue_close||pool->thread_pool_close))
  {
   pthread_cond_wait(&(pool->queue_not_full),&(pool->mutex)); 
  }
if(pool->queue_close || pool->thread_pool_close)
{
  pthread_mutex_unlock(&(pool->mutex));
  return -1;

}

struct job* pjob=(struct job*)malloc(sizeof(struct job));
if(pjob==NULL)
{
  pthread_mutex_unlock(&(pool->mutex));
  return -1;

}

pjob->CallBack_Function=CallBack_Function;
pjob->arg=arg;
pjob->next=NULL;
if(pool->head==NULL)
{
  pool->head=pool->tail=NULL;
  pthread_cond_broadcast(&(pool->queue_not_empty));

}else
{
  pool->tail->next=pjob;
  pool->tail=pjob;
}

pool->queue_cur_num++;
pthread_mutex_unlock(&(pool->mutex));
return 0;
}


int threadpool_destroy(struct threadpool* pool)
{
   assert(pool!=NULL);
   pthread_mutex_lock(&(pool->mutex));

   if(pool->queue_close || pool->thread_pool_close)
   {
      pthread_mutex_unlock(&(pool->mutex));
	  return -1;
   }

   pool->queue_close=1;
   while(pool->queue_cur_num!=0)
   {
     pthread_cond_wait(&(pool->queue_empty),&(pool->mutex));
   }
   pool->thread_pool_close=1;

   pthread_mutex_unlock(&(pool->mutex));
   pthread_cond_broadcast(&(pool->queue_not_empty));//唤醒线程池中正在阻塞的线程
   pthread_cond_broadcast(&(pool->queue_not_full));
   //唤醒添加任务的threadpool_add_job函数
   int i;
   for(i=0;i<pool->thread_num;++i)
   {
     pthread_join(pool->pthreads[i],NULL);//等待线程池的所有线程执行完毕

   }
   pthread_mutex_destroy(&(pool->mutex));
   pthread_cond_destroy(&(pool->queue_empty));
   pthread_cond_destroy(&(pool->queue_not_empty));
   pthread_cond_destroy(&(pool->queue_not_full));
   free(pool->threads);

   struct job* p;
   while(pool->head!=NULL)
   {
   p=pool->head;
   pool->head=p->next;
   free(p);
   }
   free(pool);
   return 0;








}












