#include "main.h"

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
	connectToRedis("127.0.0.1",7001);
	while(1)
		;
	return ((void *)0);
}

void
create_connections(int number,char *hostname,int port)
{
	int i,err;
	pthread_t *pidpool;

	pidpool = (pthread_t*)malloc(sizeof(pthread_t) * number);
	if (pidpool == NULL) {
		fprintf(stderr,"malloc failed\n");
		exit(-1);
	}
	
	
	for (i = 0;i < number;i++){
		err = pthread_create(&(pidpool[i]),NULL,thr_fn,NULL);
		if (err != 0)
			fprintf(stderr,"can't creat thread:%d\n",i);
		if (i == number - 1)
			printf("%d connection created!\n",number + 1);
	}
	
}

int main(int argc,char **argv)
{
	int err,i;
	int opt;
	const char *optstring = "c:C:";
	
	if (argc == 1) {
		fprintf(stderr,"Usage: %s [-c total connections] [-C] Command\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	while ((opt = getopt(argc,argv,optstring)) != -1) {
		switch(opt) {
		case 'c':
			/* Create n connections */
			create_connections(atoi(argv[optind - 1]),"127.0.0.1",6379);
			break;
		case 'C':
			/* Create commands */
			break;
		default:/* ? */
			fprintf(stderr,"Usage: %s [-c total connections] \
					[-C] Command\n",argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}

	printf("%d\n",opt);
	printids("main thread:");
	while(1)
		;
	return 0;
}
