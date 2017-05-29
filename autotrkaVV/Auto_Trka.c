/*
 ============================================================================
 Name        : Common.h
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Bojan Mikerevic
 Description : RACE in C
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Common.h"

pthread_t ID_1;
pthread_t ID_2;
pthread_t ID_3;
pthread_t ID_4;
pthread_t ID_5;
pthread_t ID_6;
pthread_t STOP;

car arrayOfCars[6];
raceTracks raceTrack;
trka trenutnaTrka;
buffer_struct buffer;

parametar ptr_1;
parametar ptr_2;
parametar ptr_3;
parametar ptr_4;
parametar ptr_5;
parametar ptr_6;
parametar ptr_7;
parametar ptr_8;
parametar ptr_9;

FILE * fp;

int main(void)
{

	Init(&buffer);

	raceTrack.weatherCondition = setWeatherCondition();
	setStartPosition(&arrayOfCars, &raceTrack);

	ptr_1.car1 = &arrayOfCars[0];
	ptr_1.raceTrack = &raceTrack;

	ptr_2.car1 = &arrayOfCars[1];
	ptr_2.raceTrack = &raceTrack;

	ptr_3.car1 = &arrayOfCars[2];
	ptr_3.raceTrack = &raceTrack;

	ptr_4.car1 = &arrayOfCars[3];
	ptr_4.raceTrack = &raceTrack;

	ptr_5.car1 = &arrayOfCars[4];
	ptr_5.raceTrack = &raceTrack;

	ptr_6.car1 = &arrayOfCars[5];
	ptr_6.raceTrack = &raceTrack;

	setGenerator(&raceTrack, &arrayOfCars);

	fp = fopen(trenutnaTrka.datum, "a");

	pthread_create(&ID_1, NULL, move, (void*) &ptr_1);
	pthread_create(&ID_2, NULL, move, (void*) &ptr_2);
	pthread_create(&ID_3, NULL, move, (void*) &ptr_3);
	pthread_create(&ID_4, NULL, move, (void*) &ptr_4);
	pthread_create(&ID_5, NULL, move, (void*) &ptr_5);
	pthread_create(&ID_6, NULL, move, (void*) &ptr_6);
	pthread_create(&STOP, NULL, stopProgram, 0);

	pthread_join(ID_1, NULL);
	pthread_join(ID_2, NULL);
	pthread_join(ID_3, NULL);
	pthread_join(ID_4, NULL);
	pthread_join(ID_5, NULL);
	pthread_join(ID_6, NULL);
	//pthread_join(STOP, NULL);

	fclose(fp);

}
