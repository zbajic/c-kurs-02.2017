/*
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "horseRacefileProcess.h"

horse h_array[10];
char* race_date;

void file_process() {
	char line[MAXSZ], dat[MAXSZ], name[MAXSZ];
	short fitness;
	int qfact;
	int r_number;
	FILE* race1;
	DIR* race;
	struct dirent* ent;
	horse* node;
	int i = 0;
	horse* first = NULL;
	horse* last = NULL;
	char* date;
	race1 = fopen("race1.txt", "r"); // otvaranje fajla
	if (race1 == NULL) {
		printf("Cannot open file\n");
// return 1;
	///home/rtrk/git/c-kurs-02.2017/
//}

	if ((race = opendir("home/rtrk/workspace/nesto/Race")) != NULL) {
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
					node = malloc(sizeof(horse)); //Alociranje novog noda za cuvanje podataka
					if (node == NULL) {
						printf("Ran out of memory\n");

					}
					race_date = strdup(dat);
					strcpy(node->name, strdup(name));
					//	node->name = strdup(name);
					node->fitness = fitness;
					if (qfact == 10) {
						node->q_factor = 1 + random() % 8;
					} else {
						node->q_factor = qfact;
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
					 printf ("%s %s %d %d \n",
					 date, node->name, node->fitness, node->qfact);
					h_array[i] = *node;
					//race_date = date;
					i++;
					node = node->next;
				}
			}
		}
	}
	closedir(race);
}
*/
