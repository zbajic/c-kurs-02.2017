/*
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "horceRaceCBuffer.h"
#include "horseRacefileProcess.h"


typedef struct race
{
	char c = 'K';
	char* datum[1];
	char* ime[NUMBER_OF_LANES];
}race;


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
char* race_date; // date of current race   RADI SAMO SA FAJLOVIMA TRKA!!!!!!!! INACE JE NULL

int flags[10]; // provjera da li je skocio
int koraci[10]; // pamtimo korake
int ukupno[10];
int var=0;
int posalji[10];
int horseID[10];
int otpisani[10];


pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;


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
void process_positions()
{
	int i;
	char f_name[] = "race_";
	char date[12];
	//char write_steps[22];
	for (i = 0; i < 12; i++)
		{
			date[i] = *(race_date + i);
		}
		strcat(f_name, date);
	//
	//for(i=0;i<10;i++){
	//	write_steps


	//}
		FILE* fp = fopen("trenutnaTrka.txt", "a+");

		fprintf(fp, "%s","*" );
		for(i=0;i<10;i++){
			fprintf(fp, "%d,", horseID[i] );
		}
		fprintf(fp, "%s","#" );
		fprintf(fp, "%s","$" );

	fclose(fp);
}
 make_string(int niz[]){
	char*


}

// SAVING FINAL RESULT OF RACE IN BUFFER
void* process_result(void* param)
{
	if(name_index < NUMBER_OF_LANES	)
	{
		horse* hs = (horse*)param;

		 *FILE* fp=fopen("nesto.txt","a+");
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


int sviSkocili(){
	int i=0;
	for(i=0;i<10;i++){
		if(flags[i]!=1){
			return 0;//bar jedan nije skocio
		}
	}
	return 1;
}


void reset(){
	int i=0;
		for(i=0;i<10;i++){
			flags[i]=0;

		}


}

int end=10;
int izadji;
int t[10];
// RUNNING HORSES - THREADS
void* run(void* param)
{


    ovo je sad uspjelo da svaku nit tj svakog konja kojeg identifikujem
    preko horse_id pomjeri za neki korak koji se dobije primjenom funkcije
    make_step()

    konj se nakon pomjeraja smjesta na odgovarajucu poziciju u matrici


    while(end>=0){
int i;
	pthread_mutex_lock(&mutex);
    horse* data = (horse*)param;
	//printf("%d\n", data->horse_id);

    if(sviSkocili()==1){
    //	printf("svi =%d\n ", data->horse_id);
    	for(i=0;i<10;i++){
    		printf("%d ", horseID[i]);
    		}
    	printf("\n");
    	process_positions();
    	reset();
    	pthread_cond_broadcast(&cond);

    }else if(flags[data->horse_id]==1){
    	// printf("wait {%d}",data->horse_id);
    	 pthread_cond_wait(&cond,&mutex);

    }else //(flags[data->horse_id]==0)
   {
   // for(column = 0; column < RACE_LENGTH; column += step)
   // {
  // while(1){
    	if(ukupno[data->horse_id]>=30){

    		//printf("Stigao: %d ",data->horse_id);
    		printf("h_id_exit = %d  step=%d \n",data->horse_id, ukupno[data->horse_id]);

    		if(otpisani[data->horse_id]==0){
    		end--;
    	}

    	otpisani[data->horse_id] = 1;

    		izadji=200;
    		horseID[data->horse_id] = ukupno[data->horse_id];
    		flags[data -> horse_id]=1;
    		 //pthread_setcancelstate(t_horses[data->horse_id]);
    		 //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
            //pthread_cancel(t_horses[data->horse_id]);
    	sleep(1);
    	printf("otpisani=%d\n", data->horse_id);
    	printf("end=%d\n",end);
    	t[data->horse_id]=1;

    	}else{

    		race_track[data -> horse_id][ukupno[data->horse_id]] = *data;

    		printf("h_id = %d  step=%d \n",data->horse_id, ukupno[data->horse_id]);


    		horseID[data->horse_id] = ukupno[data->horse_id];

    		ukupno[data -> horse_id] +=  make_step(data->fitness);

            flags[data -> horse_id] = 1;

  }
    	}

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
   // }
  // }
   pthread_mutex_unlock(&mutex);
    //   sleep(1);
   }
    printf("\n");
    return NULL;
}


int main()
{
    int i;
	int j;

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
	//    process_positions();


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

    //join all threads
    	for (i = 0; i < NUMBER_OF_LANES; i++)
    	{
    		pthread_join(t_horses[i], NULL);
    	}

        printf("\n");



  //  print matrix -for testing purpose
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        for (j = 0; j < RACE_LENGTH; j++)
        {
            printf("%d ",race_track[i][j].horse_id);
        }
        printf("\n");
   }




    return 0;

}
*/
