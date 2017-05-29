#ifndef HORSERACEFILEPROCESS_H_
#define HORSERACEFILEPROCESS_H_

#define MAXSZ 100
#define NUMBER_OF_LANES 10  //  number of rows in matrix
#define RACE_LENGTH 30   // number of columns in matrix

typedef struct horse { //struktura vezana za Horse
	float fitness;
	int horse_id;       //horse  id index
	int h_result;
	int h_step;
	short q_factor;    //quit race if q_factor >10
	char name[10];
	struct horse* next;
} horse;

typedef struct horse_step
{
	short horse_id;
	short step;
}horse_step;



#endif /* HORSERACEFILEPROCESS_H_ */
