#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%l1x)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}
void *thr_fn(void *arg)
{
    printids("new threads: "); 
    return ((void *)0);
}
int main(void)
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
    {
        err_exit(err, "can't create threads");
    }
    printids("main threads: ");
    sleep(1);
    exit(0);    
    
}