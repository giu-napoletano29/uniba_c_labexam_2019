/*
 * fileop.h
 *
 *  Created on: 11 mag 2019
 *      Author: Giuseppe Napoletano
 */

//Operazioni su immobili
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "datatypes.h"


int addbuild(){

	int ret = 0;

    FILE *fp_build;

    do{
		fp_build = fopen ("buildings.txt", "a+");
		if (fp_build==NULL){
			printf("\n------------------------ WARNING ------------------------");
			printf("\nBuilding store file does not exist. Creating new one....\n");

			fp_build = fopen ("buildings", "w+");
			if (fp_build==NULL){
				printf("\n------------------------------------ ERROR ------------------------------------");
				printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
			}
			else{
				ret = 1;
				fclose (fp_build);
			}
		}
		else{
			property p;

			printf("Inserisci l'ID dell'immobile: \n");
			scanf("%d",&p.id);
			printf("Inserisci il nome dell'immobile: \n");
			scanf("%s", p.name);
			printf("Inserisci la localita': \n");
			scanf("%s", p.locality);
			printf("Inserisci il prezzo: \n");
			scanf("%d", &p.price);
			printf("Inserisci la data: \n");
			scanf("%hd %hd %hd", &p.reg_date.day, &p.reg_date.month, &p.reg_date.year);


			fprintf(fp_build, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality, p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);
			ret = 0;
			fclose (fp_build);
		}
    }while(ret == 1);
    return -1;
}
int editbuild(){

	int count = 0; //File rows counter
	FILE *fp_build;

	fp_build = fopen ("buildings.txt", "r");
	if (fp_build==NULL){
		printf("\n------------------------ WARNING ------------------------");
		printf("\nBuilding store file does not exist. Create new one first\n");

		/*
		fp_build = fopen ("buildings.txt", "w+");
		if (fp_build==NULL){
			printf("\n------------------------------------ ERROR ------------------------------------");
			printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
		}
		else{
			fclose (fp_build);
		}*/
	}
	else{
	      char line [ 400 ]; /* or other suitable maximum line size */
	      while ( fgets ( line, sizeof line, fp_build ) != NULL ) /* read a line */
	      {
	    	  printf("%d. ", count+1);
	    	  fputs ( line, stdout ); /* write the line */
	    	  count++;
	      }

	      count = 0;
	      fclose (fp_build);
	}
	return -1;
}
int removebuild(){
	return -1;
}
