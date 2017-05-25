/*
 * kladionica.h
 *
 *  Created on: May 24, 2017
 *      Author: rtrk
 */


/*
 * kladionica.h

 *
 *  Created on: May 23, 2017
 *      Author: rtrk
 */
#include <stdio.h>
#ifndef _KLADIONICA_H
#define _KLADIONICA_H


 typedef struct trka{
	 char c;				// A ako je konj, B ako je auto
	 char datum[11];		//datum trke
	 char* ime[10];			//imena poredana po pozicijama
 }trka;


void Rase();
void RaseA();
void ispisK();
void introK();
void ispisA();
void introA();
void printRace(trka*);


#endif

