/*
 * procesiranje.c
 *
 *  Created on: May 25, 2017
 *      Author: rtrk
 */


#include <stdio.h>
#include <string.h>


#define MAXSZ 100

typedef struct _Horse {  //struktura vezana za Horse
    char* name;
    int fitness;
    int qfact;
    struct  _Horse* next;
} Horse;
	char* date;
	Horse* first = NULL;
	Horse* last = NULL;

int main () {
    char line[MAXSZ], dat[MAXSZ], name[MAXSZ];
    int fitness, qfact;

    FILE* fp;
    Horse* node;

    fp = fopen ("file.txt", "r"); //otvaranje fajla
    if (fp == NULL) {
        printf ("Cannot open file\n");
        return 1;
    }

    // Parsiranje svakog reda

    while (fgets (line, sizeof(line), fp) != NULL) {
    	sscanf (line, "%s %s %d %d", dat, name, &fitness, &qfact);

        // Allocate a new node to hold data.

        node = malloc (sizeof (Horse));
        if (node == NULL) {
            printf ("Ran out of memory\n");
            return 1;
        }

        date = strdup (dat);
        node->name = strdup (name);
        node->fitness = fitness;
        node->qfact = qfact;

        node->next = NULL;
        if (first != NULL) {
            last->next = node;
            last = node;
        } else {
            first = node;
            last = node;
        }
    }

    fclose (fp);

    // Testiranje izlaza

    node = first;
    while (node != NULL) {
        printf ("%s %s %d %d \n",
            date, node->name, node->fitness, node->qfact);
        node = node->next;
    }
    return 0;

}
