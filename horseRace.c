#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "N1.h"



#define NUMBER_OF_LANES 10        //  number of rows in matrix
#define RACE_LENGTH 500   // number of columns in matrix


typedef struct horse_step
{
	short horse_id;
	short step;
}horse_step;

/*
typedef struct race
{
	char c = 'K';
	char* datum[1];
	char* ime[NUMBER_OF_LANES];
}race;
*/

race race_result;
buffer_struct buf_result;



//char* race_date[1];
pthread_t workers[NUMBER_OF_LANES];
horse race_track[NUMBER_OF_LANES][RACE_LENGTH]; //matrix
horse h_array[NUMBER_OF_LANES];
horse_step hs_array[NUMBER_OF_LANES];
int temp[NUMBER_OF_LANES];
int test[10][RACE_LENGTH];
short name_index;
char* race_date;




int make_step(float fitness) //parameter fitness for making step
{
    int r_number;
    int step;

    r_number = 7 + random() % 3;

    step = roundf(fitness * r_number);



    return step/10;
}



int start_race_check(horse h_arr)  //main condition to start_race if <30
{
    int i;
    int sum = 0;
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        sum += h_arr.q_factor;
    }
    if (sum >= 30)
        return 0; //race is canceled

    return 1; //race will start
}

void print_canceled_race(horse h_arr[])
{
	char* f_name = strcat(strcat("race_", race_date), ".txt");

	FILE* fp=fopen(f_name,"w+");
	fprintf(fp, "Date: %s\n",race_date);
	int i=0;
	for(i=0;i<NUMBER_OF_LANES; i++)
	{
		fprintf(fp, "%d - %s\n",i, h_arr[i].name);
	}
	fclose(fp);
	printf("Date: %s/n", race_date);
	int j=0;
	for( j=0;j<NUMBER_OF_LANES; j++)
		{
			printf("%d - %s\n",j, h_arr[j].name);
		}

}



int check_horse(horse* q_horse)
{

    if (q_horse -> q_factor < 10)
        return 1;

    return 0;
}

void* process_positions(void* param)
{
	horse_step* hs = (horse_step*)param;


//	hs_array[hs -> horse_id] = hs -> step;

return NULL;

}


void* process_result(void* param)
{
	if(name_index < NUMBER_OF_LANES	)
	{
		horse* hs = (horse*)param;
		/*
		 *FILE* fp=fopen("nesto.txt","a+");
		fprintf(fp, "%d(%d)",hs->h_result,hs->h_step);
		fclose(fp);
		 */
		strcpy(race_result.date, race_date);

		race_result.name[name_index++] = hs -> name;
	}
	else
	{
		//filling circular buffer with race results
		// or writing into files if circular buffer is full

		put(&buf_result, race_result);
		dump(&buf_result);


	}

	return NULL;
}




void* run(void* param)
{
    /*

    ovo je sad uspjelo da svaku nit tj svakog konja kojeg identifikujem
    preko horse_id pomjeri za neki korak koji se dobije primjenom funkcije
    make_step()

    konj se nakon pomjeraja smjesta na odgovarajucu poziciju u matrici

    */

    horse* data = (horse*)param;

    int column;


    int j=0;
    int step = 0;
    int k=0;


    for(column = 0; column < RACE_LENGTH; column += step)
    {
        race_track[data -> horse_id][column] = *data; // writing horse into matrix
        data -> h_result = column;
        test[data -> horse_id][column]=data->horse_id;
        k++;
        step = make_step(data -> fitness);
    //	printf("%d(%d)[%d] ",data -> horse_id,column,step);
       if (column + step >= RACE_LENGTH)
       {
    	    printf("%d ",data -> horse_id);
    	    data->h_result = data ->horse_id;
    	    data->h_step = step;
        	pthread_t res_thread;
        	pthread_create(&res_thread, NULL, process_result, (void *)data);
        }

        sleep(1);
    }

   // pthread_exit(0);

    return NULL;
}


int main()
{
    int i,j,k;

 /*   horse horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10;
    horse1.fitness=50;
    horse2.fitness=20;
    horse3.fitness=30;
    horse4.fitness=40;
    horse5.fitness=60;
    horse6.fitness=23;
    horse7.fitness=40;
    horse8.fitness=80;
    horse9.fitness=10;
    horse10.fitness=20;

    //use this array to test
    horse h_array[] = {horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10};*/

    // TO DO  - getting horses for race from race-files  FUNCTION



    Init(&buf_result); //preparing circular buffer
    file_process();




/*if(!(start_race_check(&h_arr))
	{
		print_canceled_race(&h_arr);
	}
//else;
*/
    //threads
   // pthread_t workers[NUMBER_OF_LANES];
    for (j = 0; j < NUMBER_OF_LANES; j++){

        h_array[j].horse_id = j;

        pthread_create(&workers[j], NULL, run, (void*)(h_array + j));

    }

    //join all threads
    for (i = 0; i < NUMBER_OF_LANES; i++){
        pthread_join(workers[i], NULL);
    }

    printf("\n");
  /*  //print matrix
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        for (j = 0; j < RACE_LENGTH; j++)
        {
            printf("%d ",test[i][j]);
        }
        printf("\n");
    }
*/
    return 0;
}
