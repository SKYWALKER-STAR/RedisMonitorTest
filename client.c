/*
 * **********************************************************************************************************
 * Connect client functions
 * **********************************************************************************************************
 */

#include "main.h"
#include "client.h"

int connectToRedis(char *host,int port)

{
	redisContext *c = redisConnect(host,port);
	if (c != NULL && c->err) {
		fprintf(stderr,"Error:%s\n",c->errstr);
		return 1;
	}

	printf("Connected to Redis:%s:%d\n",host,port);
	return 0;
}
