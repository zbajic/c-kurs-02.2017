#ifndef _KLADIONICA_H
#define _KLADIONICA_H

#include <stdio.h>
#include "CircularBuffer.h"
#include "TipTrka.h"

void parsiranje();
void cutA();
void cutK();
void raceK();
void parsiranjeK();
void parsiranjeA();
void introK();
void raceA();
void introA();
void sort(int*,int*,int);
void printRace(trka*);
void* Punjenje_bafera(void* pParam);
void* Results(void* pParam);

#endif

