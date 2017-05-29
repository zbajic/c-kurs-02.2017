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
	pthread_t thread_parsiranje;

	//Formiranje semafora

	sem_init(&br_slobodnih_mjesta, 0, BUFFER_SIZE );
	sem_init(&br_popunjenih_mjesta, 0, 0 );


	pthread_mutex_init(&pristup_baferu, NULL);

	//formiranje niti Proizvodjac i Potrosac

	pthread_create(&Proizvodjac, NULL, Punjenje_bafera, 0);
	pthread_create(&Potrosac, NULL, Results, 0);
	pthread_create(&thread_parsiranje, NULL, parsiranje, NULL);

	printf("Unesite zeljeni metod rada:\");
		printf("1 za live score, 2 za rezultate, 3 za prikaz trenutne trke\n");
		scanf("%d",&c);
		switch(c){
	    case 1:
	        liveScore();
	        break;
	    case 2:
	        Results();
	        break;
	    case 3:
	        printf("Unesite 3 za prikaz trke auta a 4 za prikaz trke auta.\n");
	        scanf("%d",&d);
	        if(c == 3)
	            raceA();
	        if(c == 4)
	            raceK();
	        else
	            printf("Pogresan unos.\n");
	    default:
	        printf("Pogresan unos.\n");
		}

	pthread_join(Potrosac, NULL);
	pthread_join(Proizvodjac, NULL);

	sem_destroy(&br_slobodnih_mjesta);
	sem_destroy(&br_popunjenih_mjesta);

	pthread_mutex_destroy(&pristup_baferu);


	return 0;
}
