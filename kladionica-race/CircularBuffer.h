/*
 * CircularBuffer.h
 *
 *  Created on: May 16, 2017
 *      Author: rtrk
 */


#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 11
#define BUFFER_GET_ERROR -1111111111


typedef struct trka{
	 char c;				// prvi karakter oznacava da li se radi o hipodromu ili autotrci
	 char datum[12];		// datum trke
	 char* ime[10];			// pozicija ucesnika
 }trka;

typedef trka buffer_type;

typedef struct buffer_struct {
	buffer_type buffer[BUFFER_SIZE];
	buffer_type *front;
	buffer_type *rear;
} buffer_struct;

void Init(buffer_struct* buf);

int isEmpty(buffer_struct* buf);

int isFull(buffer_struct* buf);

int put(buffer_struct* buf, buffer_type x);

buffer_type get(buffer_struct* buf);

void empty(buffer_struct* buf);

void dump(buffer_struct* buf);

#endif /*CIRCULARBUFFER_H_*/