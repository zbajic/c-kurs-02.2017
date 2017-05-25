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
	//fclose(fp);
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
/*
 ============================================================================
 Name        : Common_Car_Function.c
 Author      : RT-RK
 Version     : 1.00.000
 Copyright   : Vesna Malic
 Description : RACE in C
 ============================================================================
 */
pthread_mutex_t count_mutex0;
pthread_mutex_t count_mutex1;
pthread_mutex_t count_mutex2;
pthread_mutex_t count_mutex4;
int pom = 0;
void* move(void* param1) {
	parametar* rt = (parametar*) param1;
	car* car1 = rt->car1;
	raceTracks* racetrack = rt->raceTrack;
	while (1) {
		int y = car1->row;
		int x = car1->column;

		int currentStep = car1->step;

		while (currentStep > 0) {

			//ako je auto u 0. koloni
			if (x == 0) {
		//		pthread_mutex_lock(&count_mutex0);
				if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x][y + 1] == 0)) {
					int condition = 1;
					while (condition) {
						if ((racetrack->tracks[x + 1][y + 1] == 0)) {
							racetrack->tracks[x][y + 1] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column += 1;
							x++;
							currentStep--;
							condition = 0;
						} else if ((racetrack->tracks[x + 1][y + 2] == 0)
								&& (racetrack->tracks[x][y + 2] == 0)) {
							racetrack->tracks[x][y + 2] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column += 2;
							x += 2;
							currentStep -= 2;
							condition = 0;
						} else {
							condition = 0;
						}
					}
				} else if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x][y + 1] != 0)) {
					currentStep = 0;
			//		pthread_mutex_unlock(&count_mutex0);
					break;
				}
				else {
					racetrack->tracks[x][y + 1] = car1->IDCar;
					racetrack->tracks[x][y] = 0;
					car1->row++;
					y++;
					currentStep--;
				}
			//	pthread_mutex_unlock(&count_mutex0);
			}

			//ako je auto u 1.koloni
			else if (x == 1) {
	//			pthread_mutex_lock(&count_mutex1);
				if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x - 1][y] == 0) && (racetrack->tracks[x + 1][y] == 0))  {
					int condition = 1;
					while (condition) {
						if ((racetrack->tracks[x + 1][y - 1] == 0)
								&& (racetrack->tracks[x][y - 1] == 0)) {
							racetrack->tracks[x][y - 1] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column -= 1;
							x--;
							currentStep -= 1;
							condition = 0;
						} else if ((racetrack->tracks[x + 1][y + 1] == 0)
								&& (racetrack->tracks[x][y + 1] == 0)
								&& (racetrack->tracks[x][y - 2] == 0)) {
							racetrack->tracks[x][y + 1] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column += 1;
							x++;
							currentStep--;
							condition = 0;
						} else {
							condition = 0;
						}
					}
				} else  if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x - 1][y] != 0) && (racetrack->tracks[x + 1][y] != 0)) {
					currentStep = 0;
	//				pthread_mutex_unlock(&count_mutex1);
					break;
				}
				else {
					racetrack->tracks[x][y + 1] = car1->IDCar;
					racetrack->tracks[x][y] = 0;
					car1->row++;
					y++;
					currentStep--;
				}
				pthread_mutex_unlock(&count_mutex1);
			}

			//ako je u 2. kolini
			else if (x == 2) {
//				pthread_mutex_unlock(&count_mutex2);
				if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x - 1][y] == 0)) {
					int condition = 1;
					while (condition) {
						if ((racetrack->tracks[x + 1][y - 1] == 0)
								&& (racetrack->tracks[x][y - 1] == 0)) {
							racetrack->tracks[x][y - 1] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column -= 1;
							x--;
							currentStep--;
							condition = 0;
						} else if ((racetrack->tracks[x + 1][y - 2] == 0)
								&& (racetrack->tracks[x][y - 1] == 0)
								&& (racetrack->tracks[x][y - 2] == 0)) {
							racetrack->tracks[x][y - 2] = car1->IDCar;
							racetrack->tracks[x][y] = 0;
							car1->column -= 2;
							x -= 2;
							currentStep -= 2;
							condition = 0;
						} else {
							condition = 0;
						}
					}
				} else if ((racetrack->tracks[x][y + 1] != 0) && (racetrack->tracks[x - 1][y] != 0)) {
					currentStep = 0;
	//				pthread_mutex_unlock(&count_mutex2);
					break;
				}
				else {
					racetrack->tracks[x][y + 1] = car1->IDCar;
					racetrack->tracks[x][y] = 0;
					car1->row++;
					y++;
					currentStep--;
				}
	//			pthread_mutex_unlock(&count_mutex2);
			}

		}

		ispisMatrice(racetrack->tracks);
		printf("--------------\n");
		pthread_mutex_lock(&count_mutex4);
		++pom;
		pthread_mutex_unlock(&count_mutex4);
		if(pom < 9){
        return NULL;
		}
		sleep(1);
		//pthread_mutex_unlock(&count_mutex4);
	}
}

