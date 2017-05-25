/*
 * header.h
 *
 * Created on: May 25, 2017
 * Author: rtrk
 */
#ifndef HEADER_H_
#define HEADER_H_
#define MAXSZ 100
#define NUMBER_OF_LANES 10

typedef struct horse { //struktura vezana za Horse
	float fitness;
	int horse_id;       //horse  id index
	int h_result;
	int h_step;
	short q_factor;    //quit race if q_factor >10
	char name[10];
	struct horse* next;
} horse;



#endif /* HEADER_H_ */
