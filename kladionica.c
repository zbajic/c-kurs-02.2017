/*
 * kladionica.c
 *
 *  Created on: May 24, 2017
 *      Author: rtrk
 */


/*
 * kladionica.c
 *
 *  Created on: May 24, 2017
 *      Author: rtrk
 */


/*
 * kladionica.c
 *
 *  Created on: May 23, 2017
 *      Author: rtrk
 */
#include"kladionica.h"
#include <stdio.h>
#include <string.h>

static char niz[22];
static char nizA[38];



static int skok = 21;
static int skokA = 37;

static int br_skokova;
static int br_skokovaA;




void Rase(){

int fleg=1;

FILE *fp;
FILE* novi;

introK();
sleep(5);

	while(1)
	{
	if ( (fp = fopen( "live.dat" , "r" )) != NULL )
	{
		if(fleg){
		fseek(fp, skok*br_skokova, SEEK_CUR);   //pomjera pointer u fajlu za skok*br_skokova
		fgets(niz,22,fp);                       //citanje niza karaktera u niz
if(niz[0]=='$')
{
	fleg=0;                                    //fleg koji onemoguci citanje iz fajla kada se dodje do karaktera'$'
}
else{
		fclose(fp);
		ispisK();
		sleep(1);
		br_skokova++;
		}
		}
		else
			fclose(fp);

	}
	}
}

//F-ja za graficki prikaz trke konja

void ispisK()
{
int i=0;
int j=0;
int k=0;
for(i=0;i<20;i++)
{
	if((niz[i]!='#' && niz[i]!=',' && niz[i]!='*'))
	{
		j=niz[i]-48;
		for( k =0; k<j;k++)
		{
			printf("-");
		}
		printf("*");
		printf("\n");
	}
}
printf("==================================\n");
}

void introK(){
	printf("==================================\n");
	printf("      ___   ||");
	printf("\n");
	//for(i=0;i<10;i++){
	printf("*_|| |___   ||");
	printf("\n");
	printf("*_||  ___|  ||");
	printf("\n");
	printf("  || _____  ||");

	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("*_||   |    ||");

	printf("\n");
	printf("  ||  ___   ||");
	printf("\n");
	printf("*_|| | __ | ||");
	printf("\n");
	printf("*_|| |    | ||");
	printf("\n");
	printf("  ||  ___   ||");
	printf("\n");
	printf("*_|| | __ | ||");
	printf("\n");
	printf("*_|| |    \\ ||");
	printf("\n");
	printf("  || _____  ||");

	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("*_||   |    ||");
	printf("\n");
	printf("==================================\n");


}



void RaseA(){

int fleg=1;

FILE *fp;
FILE* novi;

//fseek(fp, skokA*br_skokovaA, SEEK_CUR);   //pomjera pointer u fajlu za skok*br_skokova
/*fp = fopen( "liveA.dat" , "r" );
		fgets(nizA,38,fp);                       //citanje niza karaktera u niz
		printf("%s",nizA);*/
//sleep(5);

	while(1)
	{
	if ( (fp = fopen( "liveA.dat" , "r" )) != NULL )
	{
		if(fleg){
		fseek(fp, skokA*br_skokovaA, SEEK_CUR);   //pomjera pointer u fajlu za skok*br_skokova
		fgets(nizA,38,fp);                       //citanje niza karaktera u niz

if(nizA[0]=='$')
{
	fleg=0;                                    //fleg koji onemoguci citanje iz fajla kada se dodje do karaktera'$'
}
else{
		fclose(fp);
		ispisA();
		sleep(5);
		br_skokovaA++;
		}
		}
		else
			fclose(fp);

	}
	}
}



void ispisA(){
char niz_traka[10];      // broj trake u kojoj je auto, niz_traka[0] je traa za prvo auto itd
char niz_poz[10];        //
char pomak;
char ch = '1';
	int i=0;
	int j=0;
	int k=0;
	int br_tr = 0;
	int br_p = 0;
	int fleg_p=1;


	/*

	for(i=0;i<37;i++){
	printf("%c",nizA[i]);
			printf("\n");
	}

	*/


	for(i=0;i<strlen(nizA);i++)
	{

		if((nizA[i]!='#' && nizA[i]!=',' && nizA[i]!='*'))
		{
			/*printf("%c",nizA[0]);
		printf("\n");
		printf("%s",nizA);
		printf("\n");*/

			if(fleg_p==1)
			{
			niz_traka[br_tr]=nizA[i];


		//	printf("%c",niz_traka[br_tr]);
			//printf("\n");
			br_tr++;
			fleg_p=0;
			}
			else if(fleg_p==0){
				niz_poz[br_p]=nizA[i];
				//printf("%c",niz_poz[br_p]);
					//		printf("\n");
							br_p++;
							fleg_p=1;
			}
		}
	}



			//j=niz[i]-48;
			for( k =0; k<10;k++)
			{
				if(niz_traka[k]=='1')
				{
					for(pomak = 0;pomak<niz_poz[k]-48;pomak++)
					{
				printf("-");
					}
					printf("%d",k+1);
								printf("\n");
				}



			}
			printf("==================================\n");



			for( k =0; k<9;k++)
						{
							if(niz_traka[k]=='2')
							{
								for(pomak = 0;pomak<niz_poz[k]-48;pomak++)
								{
							printf("-");
								}
								printf("%d",k+1);
											printf("\n");
							}



						}
			printf("==================================\n");


			for( k =0; k<9;k++)
									{
										if(niz_traka[k]=='3')
										{
											for(pomak = 0;pomak <niz_poz[k]-48;pomak++)
											{
										printf("-");
											}
											printf("%d",k+1);
												  		 printf("\n");
										}



									}
						printf("==================================\n");


		}




