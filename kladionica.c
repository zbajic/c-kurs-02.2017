/*
 * kladionica.c
 *
 *  Created on: May 23, 2017
 *      Author: rtrk
 */
#include"kladionica.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//////////////////////
static char niz[42];//22
static char nizA[38];
/////////////////////

static int skok;        //21   skok u fajlu za podatke o pozicijama konja prilikom citanja frejma
static int skokA = 37;  //  skok u fajlu za podatke o pozicijama auta prilikom citanja frejma
/////////////////////

//static int br_skokova;
static int br_skokova;
static int br_skokovaA; // koliko se puta izvrsio skok u fajlu za auta, prilikom citanja
/////////////////////

//pomaci konja i auta u odnosu na start
int konj_pomak[11];
int auta_pomak[10];

// F-ja isjeca frejm iz fajla za konje
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
		fseek(fp, skok, SEEK_CUR);             //pomjera pointer u fajlu za skok*br_skokova
		fgets(niz,42,fp);                       //citanje niza karaktera u niz
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

//F-ja konvertuje primljeni frejm i graficki prikaz trke konja

void ispisK()
{
	int niz_pomaka[11];
	int ukupan_broj=0;//broj kakaktera od * do prvog karaktera #
    char niz_br[4];//karakteri izmedju dva karaktera ,
    int brc=0;      //br karaktera izmedju dava karaktera ','
    int br=0;
    int i=1;
    int j=0;
    int k=0;
    int t = 0;

while(niz[0]=='*' && niz[i]!='#')
	{
	ukupan_broj++;

		if(niz[i]!=',' && niz[i]!='*')
		{
			niz_br[brc] = niz[i];
			//printf("%d",niz_br[brc]);
			brc++;
			i++;
		}
		else
		{
			niz_br[brc] = '\0';
			niz_pomaka[br] = atoi(niz_br);
			//printf("%d ",niz_pomaka[br]);
			brc = 0;
			br++;
			i++;
		}

	}
niz_pomaka[br]='\0';
skok += ukupan_broj+2;
for(t=0;t<10;t++){
	konj_pomak[t]=niz_pomaka[t];
	//printf("%d ",konj_pomak[t]);
}
for(j = 0;j<10;j++)
{
	for(k=0;k<niz_pomaka[j];k++)
	{
		printf("-");
	}
	printf("*");
	            printf("\n");
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

char niz_traka[10];      // broj trake u kojoj je auto, niz_traka[0] je traka za prvo auto itd
char niz_poz[10];        //
char pomak;
char ch = '1';
int t = 0;
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

	for(t = 0;t<9;t++)
	{
		auta_pomak[t] = niz_poz[t]-48;
	//	printf("%d",auta_pomak[t]);

	}

	//printf("\n");
			//j=niz[i]-48;
			for( k =0; k<9;k++)
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
											for(pomak = 0;pomak<niz_poz[k]-48;pomak++)
											{
										    printf("-");
											}
											printf("%d",k+1);
											printf("\n");
										}
									}
						printf("==================================\n");


		}


void printRace(trka* t){			//ispis trke u arhivu

			   FILE *fptr;
			   fptr = fopen("test.txt","a+");
			   int i;

			   if(fptr == NULL)
			   {
			      printf("Error!");
			   }
			   if(t->c == 'A'){
			   fprintf(fptr,"Trka konja(%s), rezultati:", t->datum);
			   for(i = 0;i < 10; i++){
				   fprintf(fptr," %d.%s", i+1, t->ime[i]);
			   }
			   fprintf(fptr,"\n");
			   fclose(fptr);
			   }
				if(t->c == 'B'){
				   fprintf(fptr,"Trka auta(%s), rezultati:", t->datum);
				   for(i = 0;i < 9; i++){
					   fprintf(fptr,"%d. %s", i+1, t->ime[i]);
				   }
				   fprintf(fptr,"\n");
				   fclose(fptr);
		}
}









