
#include <stdio.h>
#ifndef _KLADIONICA_H
#define _KLADIONICA_H


 typedef struct trka{
	 char c;				// A ako je konj, B ako je auto
	 char datum[11];		//datum trke
	 char* ime[10];			//imena poredana po pozicijama
 }trka;


 void Race();
 void RaceA();
 void RaceK();
 void ispisKonja();
 void parsiranjeK();
 void parsiranjeA();
 void introK();
 void ispisA();
 void introA();
 void printRace(trka*);
 void sort(int*,int*,int);


#endif



