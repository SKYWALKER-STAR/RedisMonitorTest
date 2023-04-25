#include <hiredis/hiredis.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t ntid;

void
printids(const char *s)
{
	pid_t pid;
	pthread_t tid;
	
	pid = getpid();
	tid = pthread_self();

	printf("%s pid %lu tid (0x%lx)\n",s,(unsigned long)pid,
		(unsigned long)tid,(unsigned long)tid);
}

void *
thr_fn(void *arg)
{
	printids("new thread:");
	return ((void *)0);
}	

void connectTest(char *host,int port)
{
	redisContext *c = redisConnect(host,port);
	if (c != NULL && c->err) {
		printf("Error:%s\n",c->errstr);
	} else {
		printf("Connected to Redis\n");
	}

}


void doTheConnection()
{
	char *str = "127.0.0.1";
	int port = 6379;
	connectTest(str,port);
	while(1)
		;
}

int main(int argc,char *argv[])
{
	int err;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	if (err != 0)
		fprintf(stderr,"can't create thread");
	printids("main thread:");
	sleep(1);
	exit(0);
}	
