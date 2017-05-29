/*
 ============================================================================
 Name        : Common.h
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Bojan Mikerevic
 Description : RACE in C
 ============================================================================
 */
#define BUFFER_SIZE 11

void* move(void* param1);
void* stopProgram(void* param);
typedef struct raceTracks
{
	int tracks[3][100];
	int weatherCondition;
} raceTracks;

typedef struct car
{
	int IDCar;
	int row;
	int column;
	int tires;
	int step;
} car;

typedef struct parametar
{
	car* car1;
	raceTracks* raceTrack;
} parametar;

typedef struct trka
{
	char c;
	char datum[11];
	int nizAuta[6];
} trka;

typedef trka buffer_type;

typedef struct buffer_struct {
	buffer_type buffer[BUFFER_SIZE];
	buffer_type *front;
	buffer_type *rear;
} buffer_struct;
