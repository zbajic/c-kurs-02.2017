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
#include <time.h>
#include "Common.h"

pthread_t Array_Thread[8] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
pthread_t Terminator;
pthread_mutex_t Star_Stop = PTHREAD_MUTEX_INITIALIZER;

car arrayOfCars[9];
raceTracks Tracks;

int8_t i;
int8_t j;

short start_thread[9];
parametar ptr_master[9];

int8_t Place[6];
int8_t Number_Of_Position = 0;

void shoot_Thread(raceTracks* Tracks) {
	short n = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			start_thread[n] = Tracks->tracks[i][j];
			n++;
		}
	}
}
void Start_Stop(int Start_Stop, int ID_Car) {
	time_t t = time(NULL);

	struct tm tm = *localtime(&t);
	pthread_mutex_lock(&Star_Stop);
	if (Start_Stop) {
		printf("Start of RACE: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900,
				tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("*----------------------*\n");
		printf("*--------START---------*\n");
		printf("*----------------------*\n");

	} else {
		printf("*----------------------*\n");
		printf("*---Finish for CAR %d---*\n", ID_Car);
		printf("*----------------------*\n");
		printf("End Of RACE: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900,
				tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		Place[Number_Of_Position] = ID_Car;
		Number_Of_Position++;
		if (Number_Of_Position == 5) {
			for (Number_Of_Position = 0; Number_Of_Position < 5;
					Number_Of_Position++) {
				printf("%d place Car ID: %d\n", Number_Of_Position + 1,
						Place[Number_Of_Position]);

			}
			SaveRaceResult();
			abort();
		}
	}
	pthread_mutex_unlock(&Star_Stop);
}

int main(void) {
	Tracks.weatherCondition = setWeatherCondition();
	setStartPosition(&arrayOfCars, &Tracks);
	setGenerator(&Tracks, &arrayOfCars);
	shoot_Thread(&Tracks);
	Start_Stop(1, NULL);

	for (i = 0; i < 6; i++) {
		ptr_master[i].Cars = &arrayOfCars[i];
		ptr_master[i].raceTrack = &Tracks;
	}

	pthread_create(&Array_Thread[0], NULL, move,
			(void*) &ptr_master[start_thread[0]]);
	pthread_create(&Array_Thread[1], NULL, move,
			(void*) &ptr_master[start_thread[1]]);
	pthread_create(&Array_Thread[2], NULL, move,
			(void*) &ptr_master[start_thread[2]]);
	pthread_create(&Array_Thread[3], NULL, move,
			(void*) &ptr_master[start_thread[3]]);
	pthread_create(&Array_Thread[4], NULL, move,
			(void*) &ptr_master[start_thread[4]]);
	//pthread_create(&Array_Thread[5], NULL, move, (void*) &ptr_master[start_thread[5]]);
	pthread_create(&Terminator, NULL, Quit_Game, NULL);

	pthread_join(Array_Thread[0], NULL);
	pthread_join(Array_Thread[1], NULL);
	pthread_join(Array_Thread[2], NULL);
	pthread_join(Array_Thread[3], NULL);
	pthread_join(Array_Thread[4], NULL);
	//pthread_join(Array_Thread[5], NULL);

	return EXIT_SUCCESS;
}
