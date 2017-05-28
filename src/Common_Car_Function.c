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
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "Common.h"
#define DEBUG 1

pthread_mutex_t Mutex_Upis_Matrica = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Mutex_Grafika = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Write_In_File = PTHREAD_MUTEX_INITIALIZER;

int8_t Number_of = 0;

void setStartPosition(car* array_of_cars, raceTracks* race_track) {
	int8_t set = 0;
	char line[1024];
	FILE *fp = fopen("Start_Position_File.txt", "r");
	for (set = 0; set < 6; set++) {
		fgets(line, 50, fp);
		char ID_Car = line[4];
		array_of_cars[set].IDCar = ID_Car - '0';
		char Row = line[10];
		array_of_cars[set].row = Row - '0';
		char Column = line[19];
		array_of_cars[set].column = Column - '0';
		race_track->tracks[array_of_cars[set].row][array_of_cars[set].column] =
				array_of_cars[set].IDCar;
		char Tires = line[27];
		array_of_cars[set].tires = Tires - '0';
	}
	fclose(fp);
}

int setWeatherCondition() {
	srand(time(NULL));
	int8_t weatherCondition = rand() % 2;
	return weatherCondition;
}

void setGenerator(raceTracks* raceTrack1, car* array) {
	int8_t generator;
	int8_t i;
	double step;
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

void Grafika(raceTracks* race_track, int proces_terminated) {
	int8_t i, j;
	pthread_mutex_lock(&Mutex_Grafika);
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 3; j++) {
			if (race_track->tracks[j][i] == 0) {
				printf("|\t");
			} else {
				printf("|    %d  ", race_track->tracks[j][i]);
			}
		}
		printf("\n");
	}
	printf("----START_POSITON--------\n");
	pthread_mutex_unlock(&Mutex_Grafika);
	if (proces_terminated) {
		sleep(6000);
	}
}

void* Quit_Game(){
	char end;
	scanf("%c",&end);
	if(end == 'q'){
		abort();
	}
}

void* move(void* input) {
	parametar* Struct_of_Pointers = (parametar*) input;
	car* Cars = Struct_of_Pointers->Cars;
	raceTracks* Race_Track = Struct_of_Pointers->raceTrack;
	int8_t proces_terminated = 0;
	while (1) {
		int8_t x = Cars->column;
		int8_t y = Cars->row;
		int currentStep = Cars->step;
		int z = (y + currentStep);
		pthread_mutex_lock(&Mutex_Upis_Matrica);
		if (Race_Track->tracks[x][z] == 0) {
			Race_Track->tracks[x][y] = 0;
			if ((z >= 99) && (Race_Track->tracks[x][z] == 0)) {
				Race_Track->tracks[x][99] = Cars->IDCar;
				Start_Stop(0, Cars->IDCar);
				proces_terminated = 1;
			} else {
				Race_Track->tracks[x][z] = Cars->IDCar;
				Cars->row += currentStep;
			}
		} else if ((z >= 99) && (Race_Track->tracks[x][z] != 0)) {
			if ((Race_Track->tracks[x][99] != 0)) {
				Race_Track->tracks[x][98] = Cars->IDCar;
				Start_Stop(0, Cars->IDCar);
				proces_terminated = 1;
			} else {
				Race_Track->tracks[x][z - 1] = Cars->IDCar;
				Race_Track->tracks[x][y] = 0;
				Cars->row += (currentStep - 1);
			}
		}

		pthread_mutex_unlock(&Mutex_Upis_Matrica);
		Grafika(Race_Track->tracks, proces_terminated);
		sleep(2);
	}
}

void SaveRaceResult() {
	int8_t number;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	FILE *f;
	f = fopen("Save.txt", "a");
	pthread_mutex_lock(&Write_In_File);
	fprintf(f, "Race DATE: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900,
			tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	for (number = 0; number < 5; number++) {
		fprintf(f, "%d place Car ID: %d\n", number + 1, Place[number]);
	}
	pthread_mutex_unlock(&Write_In_File);
	fclose(f);
}
