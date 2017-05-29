/*

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "horceRaceCBuffer.h"
#include "horseRacefileProcess.h"





race race_result;// structure for putting results of race in circular buffer
buffer_struct buf_result;

//void Init(buffer_struct* buf); //preparing circular buffer
//void file_process(); //

pthread_t t_horses[NUMBER_OF_LANES]; //horse threads
horse race_track[NUMBER_OF_LANES][RACE_LENGTH]; //matrix - race tracks
horse h_array[NUMBER_OF_LANES]; //horses for race
horse_step h_step_array[NUMBER_OF_LANES]; // saving horse steps - 10 steps for 10 horses
//int temp[NUMBER_OF_LANES];
int testID[NUMBER_OF_LANES][RACE_LENGTH]; // horse ID's
short name_index;// used in process_result() for index of names
char* race_date; // date of current race

// STEP GENERATOR FOR HORSES
int make_step(float fitness) //parameter fitness for making step
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
void* process_positions(void* param)
{
	horse_step* hs = (horse_step*)param;
    //hs_array[hs -> horse_id] = hs -> step;
	return NULL;
}

// SAVING FINAL RESULT OF RACE IN BUFFER
void* process_result(void* param)
{
	if(name_index < NUMBER_OF_LANES	)
	{
		horse* hs = (horse*)param;

		FILE* fp=fopen("nesto.txt","a+");
		fprintf(fp, "%d(%d)",hs->h_result,hs->h_step);
		fclose(fp);

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



// RUNNING HORSES - THREADS
void* run(void* param)
{



    horse* data = (horse*)param;
    int column;
    int j = 0;
    int step = 0;

    for(column = 0; column < RACE_LENGTH; column += step)
    {
        race_track[data -> horse_id][column] = *data; // writing horse into matrix - each step
        data -> h_result = column;
        testID[data -> horse_id][column] = data->horse_id;

        step = make_step(data -> fitness);
    //	printf("%d(%d)[%d] ",data -> horse_id,column,step);
        // HORSE THAT FINISHED RACING
       if (column + step >= RACE_LENGTH) // creating thread for storing result of the race
       {
    	    printf("%d ",data -> horse_id);
    	    data->h_result = data ->horse_id;
    	    data->h_step = step;
        	pthread_t res_thread;
        	pthread_create(&res_thread, NULL, process_result, (void *)data);
        }
        sleep(1);
    }

    return NULL;
}


int main()
{
    int i;
	int j;

    Init(&buf_result); //preparing circular buffer
    file_process(); // getting input from files - horses for race and race date

    printf ("%s \n",h_array[5].name);

    if ( start_race_check() == 0)
    {
    	print_canceled_race();
    }
    else
    {
    	for (j = 0; j < NUMBER_OF_LANES; j++)
    	{
    		h_array[j].horse_id = j;
    		pthread_create(&t_horses[j], NULL, run, (void*)(h_array + j));
    	}

    //join all threads
    	for (i = 0; i < NUMBER_OF_LANES; i++)
    	{
    		pthread_join(t_horses[i], NULL);
    	}

        printf("\n");


    //print matrix -for testing purpose
   /* for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        for (j = 0; j < RACE_LENGTH; j++)
        {
            printf("%d ",test[i][j]);
        }
        printf("\n");
    }

    }

    return 0;

}



*/
