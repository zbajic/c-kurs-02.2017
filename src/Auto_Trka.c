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

pthread_t Array_Thread[8] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int ID;

car arrayOfCars[9];
raceTracks raceTracks1;

short i;
short j;
short start_thread[8];
int s = 0;
int b = 0;
parametar ptr_master[8];
pthread_mutex_t count_mutex0;
void shoot_Thread(raceTracks* raceTracks1){
    short n = 0;
	for(i = 2;i>=0;i--){
		for(j = 2;j>=0;j--){
		  start_thread[n] = raceTracks1->tracks[j][i];
		  n++;
		}
	}
}

int main(void) {
	raceTracks1.weatherCondition = setWeatherCondition();
	setStartPosition(&arrayOfCars, &raceTracks1);
	setGenerator(&raceTracks1, &arrayOfCars);
	shoot_Thread(&raceTracks1);

	for(i = 0;i<9;i++){
		ptr_master[i].car1 = &arrayOfCars[i];
		ptr_master[i].raceTrack =  &raceTracks1;
	}

while(1){
	for(s;s<9;s++){
		//pthread_mutex_lock(&count_mutex0);
		pthread_create(&Array_Thread[s], NULL, move, (void*) &ptr_master[start_thread[s]-1]);
		pthread_join(Array_Thread[s], NULL);
		sleep(1);
		//pthread_mutex_unlock(&count_mutex0);
	}
	sleep(100);
}


	return EXIT_SUCCESS;
}
