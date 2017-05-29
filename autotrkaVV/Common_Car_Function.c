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
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Common.h"
#define DEBUG 1
trka trenutnaTrka;
buffer_struct buffer;
extern FILE * fp;

void setStartPosition(car* array, raceTracks* rt)
{
	int i;
	char line[1024];
	FILE *fp = fopen("Start_Position_File.txt", "r");
	for (i = 0; i < 6; i++)
	{
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
	fgets(line, 11, fp);
	for (i = 0; i<11; i++)
	{
		trenutnaTrka.datum[i] = line[i];
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
int setWeatherCondition()
{
	srand(time(NULL));
	int weatherCondition = rand() % 2;
	return weatherCondition;
}

void setGenerator(raceTracks* raceTrack1, car* array)
{
	int generator;
	double step;
	int i;
	for (i = 0; i < 6; i++)
	{
		if (raceTrack1->weatherCondition == 0)
		{
			srand(time(NULL));
			generator = 7 + rand() % 4;
			if (array[i].tires == 0)
			{
				step = generator;
				array[i].step = step;
			} else
			{
				step = generator * 0.8;
				array[i].step = step;
			}
		} else
		{
			srand(time(NULL));
			generator = 3 + rand() % 4;

			if (array[i].tires == 0)
			{
				step = generator * 0.7;
				array[i].step = step;
			} else
			{
				step = generator;
				array[i].step = step;
			}
		}
	}
}
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
void printMatrix(raceTracks* rt)
{
	int i;
	int j;
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 3; j++)
		{
			pthread_mutex_lock(&mutex1);
			if (rt->tracks[j][i] == 0)
			{
				printf("*\t");
			} else
			{
				printf("%d\t", rt->tracks[j][i]);
			}
			pthread_mutex_unlock(&mutex1);
		}
		printf("\n");
	}
}
pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;



char ch = ' ';

void* stopProgram(void* param)
{
	while (ch != 'q')
	{
		ch = getchar();
	}
}

int position = 0;

int IsInArray(int id)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (trenutnaTrka.nizAuta[i] == id)
		{
			return 1;
		}
	}
	return 0;
}

void logFile(int x, int y, int z, car* car)
{
	fprintf(fp, "auto: %d bio  traka:  %d mjesto: %d\n", car->IDCar,
			(x + 1), y);
	fprintf(fp, "auto:%d dosao  traka:  %d mjesto: %d\n", car->IDCar,
			(x + 1), z);
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
void* move(void* param1)
{
	while (1)
	{

		pthread_mutex_lock(&mutex4);
		parametar* rt = (parametar*) param1;
		car* currentCar = rt->car1;
		raceTracks* racetrack = rt->raceTrack;

		int x = currentCar->column;
		int y = currentCar->row;
		int currentStep = currentCar->step;
		int z = (y + currentStep);

		if (z > 99)
		{
			printf("Stiglo je %d na cilj\n", currentCar->IDCar);
			if (!IsInArray(currentCar->IDCar))
			{
				trenutnaTrka.nizAuta[position] = currentCar->IDCar;
				trenutnaTrka.nizAuta[position] = currentCar->IDCar;
				position++;
			}

			//usleep(300);
		} else
		{
			if (racetrack->tracks[x][z] == 0)
			{
				racetrack->tracks[x][y] = 0;
				racetrack->tracks[x][z] = currentCar->IDCar;
				currentCar->row += currentStep;
				pthread_mutex_lock(&mutex0);
				logFile(x, y, z, currentCar);
				pthread_mutex_unlock(&mutex0);
			}

			else if (racetrack->tracks[x][z] != 0)
			{
				racetrack->tracks[x][z - 1] = currentCar->IDCar;
				racetrack->tracks[x][y] = 0;
				currentCar->row += (currentStep - 1);
				pthread_mutex_lock(&mutex0);
				logFile(x, y, z-1, currentCar);
				pthread_mutex_unlock(&mutex0);
			}
		}

		printMatrix(racetrack->tracks);
		if (position == 6)
		{
			printf("kraj\n");
			int i;
			for (i = 0; i < 6; i++)
			{
				printf("%d. mjesto-auto %d \n",(i+1), trenutnaTrka.nizAuta[i]);

			}
			put(&buffer, trenutnaTrka);
			//dump(&buffer);
			pthread_mutex_unlock(&mutex4);
			break;

		}
		pthread_mutex_unlock(&mutex4);

		if (ch == 'q')
		{
			exit(0);
		}
	//	usleep(300);
		sleep(1);

	}

	return NULL;
}

