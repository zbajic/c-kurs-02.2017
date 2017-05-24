/*
 ============================================================================
 Name        : Common_Car_Function.c
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Bojan Mikerevic
 Description : RACE in C
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Common.h"
#define DEBUG 1


void setStartPosition(car* array, raceTracks* rt) {
	int i;

	char line[1024];
	FILE *fp = fopen("Start_Position_File.txt", "r");

	for (i = 0; i < 9; i++) {
		fgets(line, 30, fp);
		char a = line[4];
		array[i].IDCar = a - '0';

		char b = line[10];
		array[i].row = b - '0';
		char c = line[19];
		array[i].column = c - '0';
		rt->tracks[array[i].column][array[i].row] = array[i].IDCar;
		char d = line[27];
		array[i].tires = d - '0';

	}
}
/*
 ============================================================================
 Name        : Common_Car_Function.c
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Vanja Prpos
 Description : RACE in C
 ============================================================================
 */
int setWeatherCondition() {
	srand(time(NULL));
	int weatherCondition = rand() % 2;
	return weatherCondition;
}

void setGenerator(raceTracks* raceTrack1, car* array) {
	int generator;
	double step;
	int i;
	for (i = 0; i < 9; i++) {
		if (raceTrack1->weatherCondition == 0) {
			srand(time(NULL));
			generator = 7 + rand() % 3;
			if (array[i].tires == 0) {
				step = generator;
				array[i].step = step;
			} else {
				step = generator * 0.8;
				array[i].step = step;
			}
		} else {
			srand(time(NULL));
			generator = 3 + rand() % 3;

			if (array[i].tires == 0) {
				step = generator * 0.7;
				array[i].step = step;
			} else {
				step = generator;
				array[i].step = step;
			}
		}
	}
}


void ispisMatrice(raceTracks* rt) {
	int i;
	int j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d\t", rt->tracks[j][i]);
		}
		printf("\n");
	}
}

