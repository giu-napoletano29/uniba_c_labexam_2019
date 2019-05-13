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

void checkFile(FILE *fp_build){

	if (fp_build==NULL){
		printf("\n------------------------ WARNING ------------------------");
		printf("\nBuilding store file does not exist. Creating new one....\n");

		fp_build = fopen ("buildings.dat", "w+b");
		if (fp_build==NULL){
			printf("\n------------------------------------ ERROR ------------------------------------");
			printf("\nAn error as occured while creating the file. Check your file system and retry.\n");
		}
	}
}

void infoBuild(FILE *fp_build){
	//FILE *fp_build;
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

	//fp_build = openFile();
	fprintf(fp_build, "%d, %s, %s, %d, %hd/%hd/%hd\n", p.id, p.name, p.locality, p.price, p.reg_date.day, p.reg_date.month, p.reg_date.year);
	fclose(fp_build);
}
