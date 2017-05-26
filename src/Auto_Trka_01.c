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
#include "Common_01.h"

pthread_t ID_1, ID_2, ID_3, ID_4, ID_5, ID_6, STOP;

car arrayOfCars[9];
raceTracks raceTracks1;

parametar ptr_1;
parametar ptr_2;
parametar ptr_3;
parametar ptr_4;
parametar ptr_5;
parametar ptr_6;



int main(void) {

	raceTracks1.weatherCondition = setWeatherCondition();
	setStartPosition(&arrayOfCars, &raceTracks1);

	ptr_1.car1 = &arrayOfCars[0];
	ptr_1.raceTrack = &raceTracks1;

	ptr_2.car1 = &arrayOfCars[1];
	ptr_2.raceTrack = &raceTracks1;

	ptr_3.car1 = &arrayOfCars[2];
	ptr_3.raceTrack = &raceTracks1;

	ptr_4.car1 = &arrayOfCars[3];
	ptr_4.raceTrack = &raceTracks1;

	ptr_5.car1 = &arrayOfCars[4];
	ptr_5.raceTrack = &raceTracks1;

	ptr_6.car1 = &arrayOfCars[5];
	ptr_6.raceTrack = &raceTracks1;

	setGenerator(&raceTracks1, &arrayOfCars);

	pthread_create(&ID_1, NULL, move, (void*) &ptr_1);
	pthread_create(&ID_2, NULL, move, (void*) &ptr_2);
	pthread_create(&ID_3, NULL, move, (void*) &ptr_3);
	pthread_create(&ID_4, NULL, move, (void*) &ptr_4);
	pthread_create(&ID_5, NULL, move, (void*) &ptr_5);
	pthread_create(&ID_6, NULL, move, (void*) &ptr_6);
	pthread_create(&STOP, NULL, stopProgram, NULL);


	pthread_join(ID_1, NULL);
	pthread_join(ID_2, NULL);
	pthread_join(ID_3, NULL);
	pthread_join(ID_4, NULL);
	pthread_join(ID_5, NULL);
	pthread_join(ID_6, NULL);


	return EXIT_SUCCESS;
}
