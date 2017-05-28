#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "kladionica.h"
#include "CircularBuffer.h"

buffer_struct buffer;

pthread_mutex_t pristup_baferu;

sem_t br_slobodnih_mjesta;
sem_t br_popunjenih_mjesta;



int main(void) {

	Init(&buffer);


	pthread_t Proizvodjac, Potrosac;

	//Formiranje semafora

	sem_init(&br_slobodnih_mjesta, 0, BUFFER_SIZE );
	sem_init(&br_popunjenih_mjesta, 0, 0 );


	pthread_mutex_init(&pristup_baferu, NULL);

	//formiranje niti Proizvodjac i Potrosac

	pthread_create(&Proizvodjac, NULL, Punjenje_bafera, 0);
	pthread_create(&Potrosac, NULL, Results, 0);

	pthread_join(Potrosac, NULL);
	pthread_join(Proizvodjac, NULL);

	sem_destroy(&br_slobodnih_mjesta);
	sem_destroy(&br_popunjenih_mjesta);

	pthread_mutex_destroy(&pristup_baferu);


	return 0;
}
