#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "horceRaceCBuffer.h"
#include "horseRacefileProcess.h"

/*
typedef struct race // structure for circular buffer
{
	char c = 'K';
	char* datum[1];
	char* ime[NUMBER_OF_LANES];
}race;
*/

race race_result;// structure for putting results of race in circular buffer
buffer_struct buf_result;

//void Init(buffer_struct* buf); //preparing circular buffer
//void file_process(); //

pthread_t t_horses[NUMBER_OF_LANES]; //horse threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;

horse race_track[NUMBER_OF_LANES][RACE_LENGTH]; //matrix - race tracks
horse h_array[NUMBER_OF_LANES]; //horses for race
horse_step h_step_array[NUMBER_OF_LANES]; // saving horse steps - 10 steps for 10 horses

int testID[NUMBER_OF_LANES][RACE_LENGTH]; // horse ID's

short name_index;// used in process_result() for index of names

char* race_date; // date of current race   WORKS ONLY WITH FILE INPUT!

int horse_step_flags[10]; // counter for one step of all horses
int total_step[10]; //
int total_step_horsesID[10]; // sum of previous steps for each horse
int finished_racing[10]; //horses who finished_racing - finished_racing[horse_ID] ==1
int* theStatus[10];
int racers_counter=10;// counter for horses that have not finished racing - work on pthred_cancel for faster cancellation of thread
int t[10];

//STEP GENERATOR FOR HORSES
int make_step(short fitness) //rand() gives: 7,8,9 or 10   >>TESTED OK<<
{
   short r_number;
   short low = 6;
   short high = 11;

   srand (time(NULL));

   r_number = high + rand() / (RAND_MAX / (low - high + 1) + 1); //between 7 and 10
   r_number *= fitness; //horse step

   return r_number / 10; //for smaller steps
}

// CHECK IF RACE CAN START
int start_race_check()  //condition to start race - if SUM OF HORSE Q_FACTOR < RACE_LENGTH
{
    int i;
    int sum = 0;
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        sum += h_array[i].q_factor;
    }
    if (sum >= QUIT_RACE)
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
	int i;
	FILE* fp = fopen("currentRace.txt", "a+");
	fprintf(fp, "%s","*" );
		for(i=0;i<10;i++)
		{
			fprintf(fp, "%d,", total_step_horsesID[i] );
		}
	fprintf(fp, "%s","#" );
	fprintf(fp, "%s","$" );
/*
		if(racers_counter == -1)
		{
			fprintf(fp, "%s","*" );
		 //adding last step for horse/horses that finished race last
			for(i=0;i<10;i++)
			{
				fprintf(fp, "%d,", total_step_horsesID[i]);
			}
			fprintf(fp, "%s","#" );
			fprintf(fp, "%s","$" );

		}
*/
	fclose(fp);
}

// SAVING FINAL RESULT OF RACE IN CIRCULAR BUFFER
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

int all_make_step() // all horses made step
{
	int i=0;
	for(i=0;i<10;i++)
	{
		if(horse_step_flags[i]!=1)
		{
			return 0;//at least one horse made step
		}
	}
	return 1;
}

void reset_hs_flags() // reset all horse_step_flags to 0
{
	int i=0;
	for(i=0;i<10;i++)
	{
		horse_step_flags[i]=0;
	}
}


// RUNNING HORSES - THREADS
void* run(void* param)
{

    while(racers_counter>0)
    {
    	pthread_mutex_lock(&mutex);
    	int i;
    	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    	horse* data = (horse*)param;

    	if(all_make_step()==1)
    	{
    		for(i=0;i<10;i++)
    		{
    			printf("%d ", total_step_horsesID[i]);
    		}
    		printf("\n");

    		process_positions();
    		reset_hs_flags();

    		pthread_cond_broadcast(&cond);// release all threads

    	}
    	else if(horse_step_flags[data->horse_id]==1) //if  horse_id (thread) already make one step, (flag[horse_id]==1, then he waits
    	{
    		pthread_cond_wait(&cond,&mutex);
    	}
    	else // if NOT then continues
    	{
    		if(total_step[data->horse_id]>=RACE_LENGTH) // if he finished race, 30 is length (actually it's 1000)
    		{
    			printf("h_id_exit = %d  step=%d \n",data->horse_id, total_step[data->horse_id]);

    				if(finished_racing[data->horse_id]==0)
    				{
    					racers_counter--;
    				}/*
    				if(racers_counter == 0) //upis za poslednjeg koji je presao cilj .. iz nekog razloga ne radi
    				{
    					process_positions();
    				}*/

    			finished_racing[data->horse_id] = 1;
    			total_step_horsesID[data->horse_id] = total_step[data->horse_id];
    			horse_step_flags[data -> horse_id]=1;

    			printf("finished racing=%d\n", data->horse_id);
    			printf("racers counter=%d\n",racers_counter);

    			t[data->horse_id]=1;

    			pthread_mutex_unlock(&mutex);
    			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    			sleep(2);
    			pthread_mutex_lock(&mutex);
    		}
    	    else
    	    {
    	    	race_track[data -> horse_id][total_step[data->horse_id]] = *data; //write horse into his current position on race track

    	    	printf("horse id = %d  step=%d \n",data->horse_id, total_step[data->horse_id]);

    	    	total_step_horsesID[data->horse_id] = total_step[data->horse_id];
    	    	total_step[data -> horse_id] +=  make_step(data->fitness);
    	    	horse_step_flags[data -> horse_id] = 1; // setting flag means that current horse made step and waits for others
    	    }						                    // to do the same
    	}


    	pthread_mutex_unlock(&mutex);

   }//end of while(racers_counter<0)

    printf("\n");
    return NULL;
}//end of run()


int main()
{
    int i;
	int j;
/*
	horse horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10;
	horse1.fitness=1;
	horse2.fitness=1;
	horse3.fitness=2;
	horse4.fitness=3;
	horse5.fitness=3;
	horse6.fitness=2;
	horse7.fitness=5;
	horse8.fitness=4;
	horse9.fitness=2;
	horse10.fitness=1;

	horse h_array[]={horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10};
*/

    Init(&buf_result); //preparing circular buffer
    file_process(); // getting input from files - horses for race and race date

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

/*	 // send cancel signal to thread who finished race
	for (i = 0; i < NUMBER_OF_LANES; i++)
    {
    	pthread_cancel(&t_horses[i]);
   	}
*/
    //join all threads with main
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
    	//pthread_join(t_horses[i], &t_finished[i]);
    	//pthread_join(t_horses[i],(void**)&theStatus[i]);
    	pthread_join(t_horses[i], NULL);

    }

     // send cancel signal to thread who finished race
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
    	pthread_cancel(&t_horses[i]);
    }

    //print tracks with horse steps -for testing purpose
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        for (j = 0; j < RACE_LENGTH; j++)
        {
            printf("%d ",race_track[i][j].horse_id);
        }
        printf("\n");
     }

    int kk=0;
    for(kk=0;kk<10;kk++) //last step for all horses, after finish line
    {
    	printf("%d,", total_step_horsesID[kk] );
    }
    }//end of else
    return 0;
}
