#include "sem.h"

extern ctx_s *current_ctx;

void sem_init(struct sem_s *sem, int value){
	if(value < 0){
		value = 0;
	}else if(value > SIZE_SEM_CTX_WAITING){
		value = SIZE_SEM_CTX_WAITING;
	}
	// sem->contexts_wainting[];
	sem->count = value;
}

void sem_down(struct sem_s *sem){
	sem->count -=1;
	if(sem->count <= 0){
		// contexte appelant se bloque dans la file d'attente
		sem->contexts_waiting[sem->count] = *current_ctx;
	}
}

void sem_up(struct sem_s *sem){
	sem->count += 1;
	if(sem->count <= 0){
		// contexte choisie dans la file d'attente devient actif
		*current_ctx = sem->contexts_waiting[0];	
	}
}