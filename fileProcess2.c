/*
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "horceRaceCBuffer.h"
#include "horseRacefileProcess.h"

horse h_array[10];
char* race_date;

horse_array file_process() {
	DIR* race;
	FILE* race1;
	struct dirent* ent;
	char line[MAXSZ], dat[MAXSZ], name[MAXSZ];
	short fitness;
	int qfact;
	int r_number;
		horse* node;
		int i = 0;
		horse* first = NULL;
		horse* last = NULL;
		char* date;


	int i = 0;
	Horse* first = NULL;
	Horse* last = NULL;
	char* date;
	if ((race = opendir("/home/rtrk/workspace/proba1/Race/")) != NULL) {
		while ((ent = readdir(race)) != NULL) {  ispisivanje svih fajlova iz direktorijuma
			if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
			} else {
				race1 = fopen(ent->d_name, "r"); //otvaranje fajla
				if (race1 == NULL) {
					printf("Cannot open file\n");
// return 1;
				}
				while (fgets(line, sizeof(line), race1) != NULL) { // Parsiranje svakog reda
					sscanf(line, "%s %s %d %d", dat, name, &fitness, &qfact);
					node = malloc(sizeof(Horse));
//Alociranje novog noda za cuvanje podataka
					if (node == NULL) {
						printf("Ran out of memory\n");
// return 1;
					}
					date = strdup(dat);
					node->name = strdup(name);
					node->fitness = fitness;
					if (qfact == 10) {
						node->qfact = 1 + random() % 8;
					} else {
						node->qfact = qfact;
					}
					node->next = NULL;
					if (first != NULL) {
						last->next = node;
						last = node;
					} else {
						first = node;
						last = node;
					}
				}
				fclose(race1);
				node = first; // Testiranje izlaza
				while (node != NULL) {
					printf("%s %s %d %d \n", date, node->name, node->fitness,
							node->qfact);
					h_arr.h_array[i] = *node;
					 h_arr.date = date;
					 i++;
					node = node->next;
				}
			}
		}
	}
	closedir(race);
}

*/
