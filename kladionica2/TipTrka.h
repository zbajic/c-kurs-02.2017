#ifndef TIPTRKA_H_
#define TIPTRKA_H_



/* Struktura u koju se upisuju podaci o jednoj trci */

typedef struct _trka
{
	 char c;				/* prvi karakter oznacava da li se radi o hipodromu ili autotrci*/
	 char datum[12];		/* datum trke */
	 char* ime[10];			/* pozicija  ucesnika */
 }trka;


#endif //TIPTRKA_H_
