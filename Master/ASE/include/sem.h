#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#define SIZE_SEM_CTX_WAITING 10

#include "context.h"

typedef struct sem_s{
	int count;
	ctx_s contexts_waiting[SIZE_SEM_CTX_WAITING];
}sem_s;

void sem_init(sem_s *sem, int value);

void sem_down(sem_s *sem);

void sem_up(sem_s *sem);

#endif // !_