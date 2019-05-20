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

void infoPro(FILE *fp_pro){
	professionals p;
	//TODO: need to handle escape characters
	printf("Inserisci il codice fiscale del professionista: \n");
	scanf("%s", p.id);
	printf("Inserisci il nome del professionista: \n");
	scanf("%s", p.name);
	printf("Inserisci l'area di competenza: \n");
	scanf("%s", p.competence_area);
	printf("Inserisci il numero di immobili venduti: \n");
	scanf("%d", &p.n_sold);

	fprintf(fp_pro, "%s, %s, %s, %d;\n", p.id, p.name, p.competence_area, p.n_sold);
}

void readFilePro(FILE *fp_pro, int rows, professionals *p){
	int c = 0;
	int arrayc = 0;
	int section = 1; //determinate in which VAR saving stream
	char line [ 400 ];
	//for(c = 0; c < rows; c++){
    while ( fgets ( line, sizeof line, fp_pro ) != NULL ) /* read a line */
    {
    	arrayc = 0;
		//fscanf(fp_pro, "%s %s %s %d", p[c].id, p[c].name, p[c].competence_area, &p[c].n_sold);
		printf("\nTEST ANDIAMOOO: %s\n", line);
		//fgets ( line, sizeof line, fp_pro );
		system("pause");
		for(int tcount = 0; tcount >= 0; tcount++){

			if(line[tcount] != ',' && line[tcount] != ';'){
			//if(!strcpy(line[tcount], ",")){
				/*printf("\nTCOUNT: %d\n", tcount);
				printf("\nCHAR: %c\n", line[tcount]);
				system("pause");*/
				switch(section){
					case 1:
						p[c].id[arrayc] = line[tcount];
						printf("\nID: %c, \n", p[c].id[arrayc]);
						printf("\nID: %s, \n", p[c].id);
						break;
					case 2:
						p[c].name[arrayc] = line[tcount];
						printf("\nNAME: %c, \n", p[c].name[arrayc]);
						printf("\nNAME: %s, \n", p[c].name);
						break;
					case 3:
						p[c].competence_area[arrayc] = line[tcount];
						printf("\nCOMP: %c\n", p[c].competence_area[arrayc]);
						printf("\nCOMP: %s\n", p[c].competence_area);
						break;
					case 4:
						//p[c].n_sold[tcount] = line[tcount];
						break;
				}
				arrayc++;
			}
			else if(line[tcount] == ';'){
				//tcount = -1;	//exit cycle
				printf("\nsec: %d\n", section);
				section = 1;
				printf("\nFINE 2: %s, %s, %s\n", p[c].id, p[c].name, p[c].competence_area);
				system("pause");
				break;
			}
			else{
				printf("\nFINE 1: %d\n", section);
				system("pause");
				arrayc=0;
				section++;
				if(section > 4){
					section = 1;
				}
			}

		}
		c++;
	}
	printf("\nPROVA:\n");
	system("pause");
	for(c = 0; c < rows; c++){

		printf("\n%s %s %s \n", p[c].id, p[c].name, p[c].competence_area);
	}
	system("pause");
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
