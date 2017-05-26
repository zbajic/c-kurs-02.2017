/*
 ============================================================================
 Name        : Common.h
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Bojan Mikerevic
 Description : RACE in C
 ============================================================================
 */

void* move(void* param1);
void* stopProgram(void* param);
typedef struct raceTracks {
	int tracks[3][100];
	int weatherCondition;
} raceTracks;

typedef struct car {
	int IDCar;
	int row;
	int column;
	int tires;
	int step;
} car;

typedef struct parametar {
	car* car1;
	raceTracks* raceTrack;
} parametar;

typedef struct race {
	char* date;
	int numberOfLaps;
} race;


typedef struct trka {
	char c;
	char datum[11];
	char* nizAuta;
} trka;
