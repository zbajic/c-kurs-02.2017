#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "horceRaceCBuffer.h"
#include "horseRacefileProcess.h"



race race_result;                                         // structure for putting results of race in circular buffer
buffer_struct buf_result;

//void Init(buffer_struct* buf); //preparing circular buffer
//void file_process(); //

pthread_t t_horses[NUMBER_OF_LANES];                  // horse threads
horse race_track[NUMBER_OF_LANES][RACE_LENGTH];      // matrix - race tracks
horse h_array[NUMBER_OF_LANES];                     // horses for race
horse_step h_step_array[NUMBER_OF_LANES];          // saving horse steps - 10 steps for 10 horses


int testID[NUMBER_OF_LANES][RACE_LENGTH];        // horse ID's
short name_index;                               // used in process_result() for index of names
char* race_date;                               // date of current race   RADI SAMO SA FAJLOVIMA TRKA!!!!!!!! INACE JE NULL

int jump_flags[NUMBER_OF_LANES];             // if jumped set flag = 1
int previous_step[NUMBER_OF_LANES];         // save previous step for each horse
int horseID[NUMBER_OF_LANES];              //
int waiting_threads[NUMBER_OF_LANES];     // inactive threads waiting main to terminate race
int end_race = NUMBER_OF_LANES;          // terminate race when all horses have arrived
int end_file_proccess = 0;              // terminate writing in file  when last horse has arrived
int horse_finished_race = 0;           // horse finished race

pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;


// STEP GENERATOR FOR HORSES
int make_step(float fitness)       //parameter fitness for making step
{
    int r_number;
    int step;
    r_number = 7 + random() % 3;
    step = roundf(fitness * r_number);
    return step;
}

// CHECK IF RACE CAN START -  <30
int start_race_check()  //main condition to start_race if <30
{
    int i;
    int sum = 0;
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        sum += h_array[i].q_factor;
    }
    if (sum >= 30)
    {
    	return 0; //race is canceled
    }
    else
    {
    	return 1; //race will start
    }
}

// PRINT CANCELED RACE
void print_canceled_race()
{
	int i = 0;
	int j = 0;

	char f_name[] = "race_";
	char date[12];
	for (i = 0; i < 12; i++)
	{
		date[i] = *(race_date + i);
	}
	strcat(f_name, date);

	FILE* fp = fopen(f_name, "w");

	fprintf(fp, "Date: %s\n", race_date);

	for (i = 0; i < NUMBER_OF_LANES; i++)
	{
		fprintf(fp, "%d - %s\n", i, h_array[i].name);
	}
	fclose(fp);

	printf("Date: %s\n", race_date);
	for (j = 0; j < NUMBER_OF_LANES; j++)
	{
		printf("%d - %s\n" ,j ,h_array[j].name);
	}
}



// SAVING HORSE STEPS FOR ALL HORSES
void process_positions()
{
	int i = 0;
		int j = 0;

		char f_name[] = "race_";
		char date[12];
		for (i = 0; i < 12; i++)
		{
			date[i] = *(race_date + i);
		}
		strcat(f_name, date);

		FILE* fp = fopen(f_name, "a+");

		//FILE* fp = fopen("trenutnaTrka.txt", "a+");

		fprintf(fp, "%s","*" );
		for(i=0;i<10;i++){
			fprintf(fp, "%d,", horseID[i] );
		}
		fprintf(fp, "%s","#" );
		fprintf(fp, "%s","$" );

	fclose(fp);
}

// SAVING FINAL RESULT OF RACE IN BUFFER
void* process_result(void* param)
{

		horse* hs = (horse*)param;

	//	strcpy(race_result.date, race_date);

		race_result.name[name_index++] = hs -> name;
		//race_result.date = race_date;

		put(&buf_result, race_result);
		//dump(&buf_result);

	return NULL;
}


//CHECK IF ALL HORSES JUMPED ONCE
int all_jumped_once(){

    int i = 0;

    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        if (jump_flags[i] != 1)
        {
            return 0; //at least one didn't jumped
        }
    }
    return 1;
}

//RESET ARRAY OF FLAGS
void reset_array(){

    int i = 0;
        for (i = 0; i < NUMBER_OF_LANES; i++)
        {
            jump_flags[i] = 0;

        }


}

// RUNNING HORSES - THREADS
void* run(void* param)
{

    int i;

    pthread_mutex_lock(&mutex); // lock critical section


    horse* data = (horse*)param;

    if (all_jumped_once() == 1) // reset flag array if all 10 horses jumped
    {

        if (end_file_proccess == 0)
        {
        	process_positions();
        }


        reset_array();

    }
    else
    {
        if (previous_step[data -> horse_id] >= RACE_LENGTH){

           // printf("h_id_exit = %d  step=%d \n",data->horse_id, previous_step[data->horse_id]);

            if (waiting_threads[data -> horse_id] == 0)
            {
                end_race--;
                horse_finished_race = 1;
            }

            waiting_threads[data -> horse_id] = 1;


            horseID[data -> horse_id] = previous_step[data -> horse_id];
            jump_flags[data -> horse_id] = 1;

           // printf("otpisani=%d\n", data->horse_id);
           // printf("end=%d\n",end_race);


            if (end_race == 0)
            {
            	if (end_file_proccess == 0)
            	{
            		process_positions();
            	}
            	end_file_proccess = 1;
            }

        }
        else if (jump_flags[data->horse_id] == 1)
        {
        	//do nothing here just pass
        }
        else
        {

            race_track[data -> horse_id][previous_step[data -> horse_id]] = *data;

          //  printf("h_id = %d  step=%d \n",data->horse_id, previous_step[data->horse_id]);


            horseID[data -> horse_id] = previous_step[data -> horse_id];

            previous_step[data -> horse_id] +=  make_step(data -> fitness);

            jump_flags[data -> horse_id] = 1;

        }
    }

    // HORSE THAT FINISHED RACING
    //PUT RESULT IN BUFFER
    if (horse_finished_race == 1)
    {
    	race_result.name[name_index++] = data -> name;
    	race_result.date[0] = race_date;

    	put(&buf_result, race_result);

        horse_finished_race = 0;
    }


    pthread_mutex_unlock(&mutex); //end of critical section


    return NULL;

}


int main()
{
        int i;
	    int j;

	    Init(&buf_result); //preparing circular buffer
	    file_process(); // getting input from files - horses for race and race date

	    if ( start_race_check() == 0)
	    {
	    	print_canceled_race();
	    }
	    else
	    {

	    	while(end_race > 0)
	        {
	            for (j = 0; j < NUMBER_OF_LANES; j++)
	            {
	                h_array[j].horse_id = j;
	                pthread_create(&t_horses[j], NULL, run, (void*)(h_array + j));
	            }
	        }
	    	//join all threads
	    	for (i = 0; i < NUMBER_OF_LANES; i++)
	    	{
	    		pthread_join(t_horses[i], NULL);
	    	}

	    	printf("Print matrix for testing purpose:\n");

	    	//  print matrix -for testing purpose

	    	for (i = 0; i < NUMBER_OF_LANES; i++)
	    	{
	    		for (j = 0; j < RACE_LENGTH; j++)
	    		{
	    			printf("%d ",race_track[i][j].horse_id);
	    		}
	    		printf("\n");
	    	}
	    	printf("\n");

	    	//dump buffer for testing purpose
	    	dump(&buf_result);
	    }
	    return 0;
}




