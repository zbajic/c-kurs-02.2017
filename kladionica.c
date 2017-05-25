/*
 * kladionica.c
 *
 *  Created on: May 23, 2017
 *      Author: rtrk
 */
#include"kladionica.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CircularBuffer.h"

//////////////////////
static char niz[42]; //22
static char nizA[38];
/////////////////////

static int skok; //21   skok u fajlu za podatke o pozicijama konja prilikom citanja frejma
static int skokA = 37; //  skok u fajlu za podatke o pozicijama auta prilikom citanja frejma
/////////////////////

//static int br_skokova;
static int br_skokova;
static int br_skokovaA; // koliko se puta izvrsio skok u fajlu za auta, prilikom citanja
/////////////////////

int konj_pomak[11]; //pomaci konja u odnosu na start

int auta_pomak[10]; //pomaci auta u odnosu na start

char* auta[] = { "Car1", "Car2", "Car3", "Car4", "Car5", "Car6", "Car7", "Car8",
		"Car9" };
char* konji[] = { "Horse1", "Horse2", "Horse3", "Horse4", "Horse5", "Horse6",
		"Horse7", "Horse8", "Horse9", "Horse10" };
int niz_pomaka[11];
char niz_poz[10];
char niz_traka[10];

// F-ja isjeca frejm iz fajla za konje
void RaceK() {

	int fleg = 1;

	FILE *fp;
	FILE* novi;

//introK();
	sleep(1);

	if ((fp = fopen("live.dat", "r")) != NULL) {
		if (fleg) {
			fseek(fp, skok, SEEK_CUR); //pomjera pointer u fajlu za skok*br_skokova
			fgets(niz, 42, fp);                   //citanje niza karaktera u niz
			if (niz[0] == '$') {
				fleg = 0; //fleg koji onemoguci citanje iz fajla kada se dodje do karaktera'$'
			}
			else {
				fclose(fp);
				//parsiranjeK();
				sleep(1);
				br_skokova++;
			}
		}
		else
			fclose(fp);
	}
}

//F-ja konvertuje primljeni frejm i graficki prikaz trke konja

void parsiranjeK() {

	int ukupan_broj = 0;              //broj kakaktera od * do prvog karaktera #
	char niz_br[4];                          //karakteri izmedju dva karaktera ,
	int brc = 0;      //br karaktera izmedju dava karaktera ','
	int br = 0;
	int i = 1;
	int t = 0;
	//  printf("==================================\n");
	while (niz[0] == '*' && niz[i] != '#') {
		ukupan_broj++;

		if (niz[i] != ',' && niz[i] != '*') {
			niz_br[brc] = niz[i];
			//printf("%d",niz_br[brc]);
			brc++;
			i++;
		} else {
			niz_br[brc] = '\0';
			niz_pomaka[br] = atoi(niz_br);
			//printf("%d ",niz_pomaka[br]);
			brc = 0;
			br++;
			i++;
		}

	}
	niz_pomaka[br] = '\0';
	skok += ukupan_broj + 2;
	for (t = 0; t < 10; t++) {
		konj_pomak[t] = niz_pomaka[t];
//		printf("%d ", konj_pomak[t]);
	}
//ispisKonja();
}

void ispisKonja() {
	int j = 0;
	int k = 0;
	for (j = 0; j < 10; j++) {
		for (k = 0; k < niz_pomaka[j]; k++) {
			printf("-");
		}
		printf("*");
		printf("\n");
	}

	printf("==================================\n");

}

void introK() {
	printf("==================================\n");
	printf("      ___   ||");
	printf("\n");
	//for(i=0;i<10;i++){
	printf("*_|| |___   ||");
	printf("\n");
	printf("*_||  ___|  ||");
	printf("\n");
	printf("  || _____  ||");

	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("*_||   |    ||");

	printf("\n");
	printf("  ||  ___   ||");
	printf("\n");
	printf("*_|| | __ | ||");
	printf("\n");
	printf("*_|| |    | ||");
	printf("\n");
	printf("  ||  ___   ||");
	printf("\n");
	printf("*_|| | __ | ||");
	printf("\n");
	printf("*_|| |    \\ ||");
	printf("\n");
	printf("  || _____  ||");

	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("==================================\n");

}

void RaceA() {

	int fleg = 1;

	FILE *fp;
	FILE* novi;

	if ((fp = fopen("liveA.dat", "r")) != NULL) {
		if (fleg) {
			fseek(fp, skokA * br_skokovaA, SEEK_CUR); //pomjera pointer u fajlu za skok*br_skokova
			fgets(nizA, 38, fp);                  //citanje niza karaktera u niz

			if (nizA[0] == '$') {
				fleg = 0; //fleg koji onemoguci citanje iz fajla kada se dodje do karaktera'$'
			} else {
				fclose(fp);
//		parsiranjeA();
				sleep(5);
				br_skokovaA++;
			}
		} else
			fclose(fp);
	}
}

void Race() {
	RaceA();
	RaceK();
}

void parsiranjeA() {
	int t = 0;
	int i = 0;
	int j = 0;
	int br_tr = 0;
	int br_p = 0;
	int fleg_p = 1;

	for (i = 0; i < strlen(nizA); i++) {

		if ((nizA[i] != '#' && nizA[i] != ',' && nizA[i] != '*')) {
			if (fleg_p == 1) {
				niz_traka[br_tr] = nizA[i];
				br_tr++;
				fleg_p = 0;
			} else if (fleg_p == 0) {
				niz_poz[br_p] = nizA[i];
				br_p++;
				fleg_p = 1;
			}
		}
	}

	for (t = 0; t < 9; t++) {
		auta_pomak[t] = niz_poz[t] - 48;
		printf("%d ", auta_pomak[t]);
	}

}

void ispisA() {

	 // broj trake u kojoj je auto, niz_traka[0] je traka za prvo auto itd
       //
	char pomak;
	int k;

	for (k = 0; k < 9; k++) {
		if (niz_traka[k] == '1') {
			for (pomak = 0; pomak < niz_poz[k] - 48; pomak++) {
				printf("-");
			}
			printf("%d", k + 1);
			printf("\n");
		}

	}
	printf("==================================\n");

	for (k = 0; k < 9; k++) {
		if (niz_traka[k] == '2') {
			for (pomak = 0; pomak < niz_poz[k] - 48; pomak++) {
				printf("-");
			}
			printf("%d", k + 1);
			printf("\n");
		}

	}
	printf("==================================\n");

	for (k = 0; k < 9; k++) {
		if (niz_traka[k] == '3') {
			for (pomak = 0; pomak < niz_poz[k] - 48; pomak++) {
				printf("-");
			}
			printf("%d", k + 1);
			printf("\n");
		}
	}
	printf("==================================\n");

}

void printRace(trka* t) {			//ispis trke u arhivu

	FILE *fptr;
	fptr = fopen("test.txt", "a+");
	int i;

	if (fptr == NULL) {
		printf("Error!");
	}
	if (t->c == 'A') {
		fprintf(fptr, "Trka konja(%s), rezultati:", t->datum);
		for (i = 0; i < 10; i++) {
			fprintf(fptr, " %d.%s", i + 1, t->ime[i]);
		}
		fprintf(fptr, "\n");
		fclose(fptr);
	}
	if (t->c == 'B') {
		fprintf(fptr, "Trka auta(%s), rezultati:", t->datum);
		for (i = 0; i < 9; i++) {
			fprintf(fptr, "%d. %s", i + 1, t->ime[i]);
		}
		fprintf(fptr, "\n");
		fclose(fptr);
	}
}

void sort(int* array,int* indexes, int n) { //potrebna za sortiranje niza pomaka u odnosu na start zbog prikaza livescora-a
	int i;
	int j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (array[i] < array[j]) {
				int tmp;
				int tmp1;

				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;

				tmp1 = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = tmp1;
			}
		}
	}
}

void liveScore() {
	int i;
	int index1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int index2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	sort(konj_pomak, index1, 11);

	printf("------------------------\n");
	printf("****** Trka konja ******\n");
	printf("------------------------\n");
	printf("Trenutno stanje:\n");
	for (i = 0; i < 11; i++) {
		printf("%d. %s\n", i + 1, konji[index1[i]]);
	}
	printf("\n");

	sort(auta_pomak, index2, 10);
	printf("------------------------\n");
	printf("****** Trka auta ******\n");
	printf("------------------------\n");
	printf("Trenutno stanje:\n");
	for (i = 0; i < 10; i++) {
		printf("%d. %s\n", i + 1, auta[index2[i]]);
	}
}


// Ispis konacnih rezultata iz bafera
void Results()
{
	buffer_struct buffer; //naknadno ce biti definisano u glavnoj niti a ne ovdje
	buffer_struct buffer1;

	int i;
	trka memorija, datoteka;

	// simulacija sadrzaja  bafera

	trka a = { 'A', "10.05.2017", { "auto 1", "auto 2", "auto 7", "auto 4",
			"auto 8", "auto 3", "auto 5", "auto 9", "auto 6", "auto 10" } };
	trka b = { 'H', "11.03.2017", { "konj 5", "konj 3", "konj 7", "konj 1",
			"konj 10", "konj 4", "konj 5", "konj 6", "konj 8", "konj 9" } };
	trka c = { 'A', "2.09.2017", { "auto 3", "auto 9", "auto 5", "auto 1",
			"auto 2", "auto 4", "auto 8", "auto 6", "auto 7", "auto 10" } };

	Init(&buffer);  //naknadno ce biti inicijalizovano u glavnoj niti a ne ovdje
	Init(&buffer1);

	printf("\n");
	printf("************************\n");
	put(&buffer, a);
	memorija = get(&buffer);
	put(&buffer1, memorija);
	dump(&buffer1);
	printf("*************************\n");
	sleep(3);

	printf("\n");
	put(&buffer, b);
	memorija = get(&buffer);
	put(&buffer1, memorija);
	dump(&buffer1);
	printf("*************************\n");
	sleep(3);

	put(&buffer, c);
	memorija = get(&buffer);
	put(&buffer1, memorija);
	dump(&buffer1);
	printf("*************************\n");
	sleep(3);

	if (isFull(&buffer1)) {

		datoteka = get(&buffer1);
		printRace(&datoteka); /*upis zastarjelih rezultata u tekstualnu datoteku*/

	}
	printf("Bafer pun\n");
	dump(&buffer1);
	printf("*************************\n");

}



