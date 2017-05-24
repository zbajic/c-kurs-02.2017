#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>



#define NUMBER_OF_LANES 10        // number of rows in matrix
#define RACE_LENGTH 50   // number of columns in matrix


typedef struct horse
{
    float fitness;
    int horse_id;       //horse id index
    short q_factor;     //quit race if q_factor >10
    char name[10];
}horse;

typedef struct horse_step
{
	short horse_id;
	short step;
}horse_step;

horse race_track[NUMBER_OF_LANES][RACE_LENGTH]; //matrix
horse h_array[NUMBER_OF_LANES];
horse_step hs_array[NUMBER_OF_LANES];
int temp[NUMBER_OF_LANES];
int test[RACE_LENGTH];




int make_step(float fitness) //parameter fitness for making step
{
    int r_number;
    int step;

    r_number = 7 + random() % 3;

    step = roundf(fitness * r_number);



    return step/10;
}



int start_race()  //main condition to start_race if <30
{
    int i;
    int sum = 0;
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        sum += h_array[i].q_factor;
    }
    if (sum > 30)
        return 0;

    return 1;
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



    int step = 0;
    int k=0;

    for(column = 0; column < RACE_LENGTH; column += step)
    {

//    	printf("%d ",data -> horse_id);

        race_track[data -> horse_id][column] = *data; // upisujemo konja u matricu

        test[k]=data->horse_id;
        k++;

        step = make_step(data -> fitness);

        sleep(1);

    }
    pthread_exit(0);


}


int main()
{
    int i,j,k;

    horse horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10;
    horse1.fitness=10;
    horse2.fitness=20;
    horse3.fitness=30;
    horse4.fitness=40;
    horse5.fitness=50;
    horse6.fitness=60;
    horse7.fitness=70;
    horse8.fitness=80;
    horse9.fitness=90;
    horse10.fitness=100;

    //use this array to test
    horse h_array[] = {horse1,horse2,horse3,horse4,horse5,horse6,horse7,horse8,horse9,horse10};


    int thread_counter = 0;

    //threads
    pthread_t workers[NUMBER_OF_LANES];

    for (j = 0; j < NUMBER_OF_LANES; j++){

        h_array[j].horse_id = j;

        pthread_create(&workers[thread_counter], NULL, run, (void*)(h_array + j));
        thread_counter++;
    }

    //join all threads
    for (i = 0; i < NUMBER_OF_LANES; i++){
        pthread_join(workers[i], NULL);
    }

    for (j = 0; j < RACE_LENGTH; j++){

    	printf("%d ",test[j]);
    }

  /*  //print matrix
    for (i = 0; i < NUMBER_OF_LANES; i++)
    {
        for (j = 0; j < RACE_LENGTH; j++)
        {
            printf("%g ",race_track[i][j].fitness);
        }
        printf("\n");
    }
*/


    return 0;
}
