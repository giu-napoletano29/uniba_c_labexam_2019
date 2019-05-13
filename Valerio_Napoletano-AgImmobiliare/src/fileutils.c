/*
 * fileutils.c
 *
 *  Created on: 13 mag 2019
 *      Author: Giuseppe Napoletano
 */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "datatypes.h"

int checkFile(FILE *fp_build){
	int res = 0;

	if (fp_build==NULL){
		printf("\n------------------------ WARNING ------------------------");
		perror("\nError: ");
		printf("\nCheck your file system and retry.\n");
		/*
		printf("\nBuilding store file does not exist. Creating new one....\n");

		fp_build = fopen ("buildings.dat", "a+b");
		if (fp_build==NULL){
			printf("\n------------------------------------ ERROR ------------------------------------");
			printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
		}*/
		res = 1;
		fclose(fp_build);
	}
	return res;
}

void infoBuild(FILE *fp_build){
	property p;
	//TODO: need to handle escape characters
	printf("Inserisci l'ID dell'immobile: \n");
	scanf("%d",&p.id);
	printf("Inserisci il nome dell'immobile: \n");
	scanf("%s", p.name);
	printf("Inserisci la localita': \n");
	scanf("%s", p.locality);
	printf("Inserisci il prezzo: \n");
	scanf("%d", &p.price);
	printf("Inserisci la data: \n");
	scanf("%hd %hd %hd", &p.reg_date.day, &p.reg_date.month, &p.reg_date.year);	//TODO: Inserire controllo data

	fprintf(fp_build, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality, p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);
}

int countRows(FILE *fp_build){
	int count = 0;
    char line [ 400 ];
    while ( fgets ( line, sizeof line, fp_build ) != NULL ) /* read a line */
    {
  	  printf("%d. ", count+1);
  	  fputs ( line, stdout ); /* write the line */
  	  count++;
    }
	return count;
}

void copyFile(FILE *fp_from, FILE *fp_to, int choice){
	char line [ 400 ];
	unsigned int Uchoice = -choice;
	int count = 0;
    while ( fgets ( line, sizeof line, fp_from ) != NULL ) /* read a line */
    {
    	count++;
    	if(choice==0){
    		fputs( line, fp_to);
    	}
    	else if(choice > 0){
        	if(choice == count){
        		infoBuild(fp_to);
        	}
        	else{
        		fputs( line, fp_to);
        	}
    	}
    	else{
        	if(Uchoice != count){
        		fputs( line, fp_to);
        	}
    	}
    }
}
