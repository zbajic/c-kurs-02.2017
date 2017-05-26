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
#include "Common_01.h"
#define DEBUG 1

void setStartPosition(car* array, raceTracks* rt) {
	int i;

	char line[1024];
	FILE *fp = fopen("Start_Position_File.txt", "r");
	for (i = 0; i < 6; i++) {
		fgets(line, 50, fp);
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
	for (i = 0; i < 6; i++) {
		if (raceTrack1->weatherCondition == 0) {
			srand(time(NULL));
			generator = 7 + rand() % 4;
			if (array[i].tires == 0) {
				step = generator;
				array[i].step = step;
			} else {
				step = generator * 0.8;
				array[i].step = step;
			}
		} else {
			srand(time(NULL));
			generator = 3 + rand() % 4;

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
pthread_mutex_t mutex1;
void ispisMatrice(raceTracks* rt) {
	int i;
	int j;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 3; j++) {
			pthread_mutex_lock(&mutex1);
			printf("%d\t", rt->tracks[j][i]);
			pthread_mutex_unlock(&mutex1);
		}
		printf("\n");
	}
}
/*
 ============================================================================
 Name        : Common_Car_Function.c
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Vesna Malic
 Description : RACE in C
 ============================================================================
 */
int v;
int noOfLaps = 0;
pthread_mutex_t mutex0;
pthread_mutex_t mutex4;

int pom = 0;
int numberOfLaps = 2;
int currentLap = 0;


char ch = ' ';

void* stopProgram(void* param) {
	while (ch != 'q') {
		ch = getchar();
	}
}

int numOfLaps = 0;
void* move(void* param1) {
	parametar* rt = (parametar*) param1;
	car* car1 = rt->car1;
	raceTracks* racetrack = rt->raceTrack;

	while (1) {
		int x = car1->column;
		int y = car1->row;
		int currentStep = car1->step;

		pthread_mutex_lock(&mutex0);
		printf("\nkorak %d , auto: %d\n", currentStep, car1->IDCar);
		pthread_mutex_unlock(&mutex0);

		pthread_mutex_lock(&mutex4);
		int z = (y + currentStep);
//		if (z > 99) {
//			z -= 100;
//			numOfLaps++;
//			printf("br kr:%d", numOfLaps);
//
//		}

		if (racetrack->tracks[x][z] == 0) {
			racetrack->tracks[x][y] = 0;
			printf("\nnema\n");
			racetrack->tracks[x][z] = car1->IDCar;
			car1->row += currentStep;
		}

		else if (racetrack->tracks[x][z] != 0) {
			printf("\nima");
			racetrack->tracks[x][z - 1] = car1->IDCar;
			racetrack->tracks[x][y] = 0;
			car1->row += (currentStep - 1);
		}

		int i;
		int j;
		for (i = 0; i < 100; i++) {
			for (j = 0; j < 3; j++) {
				printf("%d\t", racetrack->tracks[j][i]);
			}
			printf("\n");
		}
		pthread_mutex_unlock(&mutex4);

		if (ch == 'q') {
			exit(0);
		}
		sleep(2);

	}

	return NULL;
}
