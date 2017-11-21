#include "test_pthread.h"

pthread_mutex_t mutex;//锁
typedef pthread_t pt_t;

int * handleCreate(char * arg)
{
    for(int i = 0;i<10;i++)
    {
        LOGD("test====%s %d",(char *)arg,i);
        sleep(1);
    }
    int result = -1;
    return &result;
}
pt_t create()
{
    pt_t pid;
    const char * str = "xxxxx";
    int tid;
    tid = pthread_create(&pid,NULL,(void *)&handleCreate,(void *)str);
    if(tid) {
        LOGD("test");
        return pid;
    }
    return pid;
}

struct thread_args
{
    int  thread_id;
    char * message;
}targs;
//多参数
void * handleCreateMultiArgs(void * threadarg)
{
    struct thread_args * args;
    args = (struct thread_data *) threadarg;
    LOGD("test sss %s %d ",args->message,args->thread_id);
}


pt_t createMultiArgs(struct thread_args args)
{
    pt_t pid;
    int tid;
    tid = pthread_create(&pid,NULL,handleCreateMultiArgs,(void *)&args);
    if(tid) {
        return -1;
    }
    return pid;
}



struct thread_args args[4] = {
        {0,"test1"},{1,"test2"},{2,"test3"},{3,"test4"}
};

void runThread(const char * name)
{
    //1、创建线程
////    pid1 = create();
//
    LOGD("test pthread ==== %s",name);
    pt_t pids[4];
    for(int i=0;i<4;i++)
    {
        pt_t id = pthread_create(&pids[i],NULL,handleCreateMultiArgs,(void *)&args[i]);
        if(id) {
            continue;
        }
    }

//
    LOGD("test run in mainThread ====end ");

}

