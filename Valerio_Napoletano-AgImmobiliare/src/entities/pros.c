/*
 * pros.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"
#include "../file_utils.h"

void readFilePro(FILE *fp_pro, int rows, professionals *p) {
	int c = 0;
	int arrayc = 0;
	int section = 1; //determinate in which VAR saving stream
	char line[400];
	//for(c = 0; c < rows; c++){
	while (fgets(line, sizeof line, fp_pro) != NULL) /* read a line */
	{
		arrayc = 0;
		//fscanf(fp_pro, "%s %s %s %d", p[c].id, p[c].name, p[c].competence_area, &p[c].n_sold);
		printf("\nTEST ANDIAMOOO: %s\n", line);
		//fgets ( line, sizeof line, fp_pro );
		system("pause");
		for (int tcount = 0; tcount >= 0; tcount++) {

			if (line[tcount] != ',' && line[tcount] != ';') {
				//if(!strcpy(line[tcount], ",")){
				/*printf("\nTCOUNT: %d\n", tcount);
				 printf("\nCHAR: %c\n", line[tcount]);
				 system("pause");*/
				switch (section) {
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
			} else if (line[tcount] == ';') {
				//tcount = -1;	//exit cycle
				printf("\nsec: %d\n", section);
				section = 1;
				printf("\nFINE 2: %s, %s, %s\n", p[c].id, p[c].name,
						p[c].competence_area);
				system("pause");
				break;
			} else {
				printf("\nFINE 1: %d\n", section);
				system("pause");
				arrayc = 0;
				section++;
				if (section > 4) {
					section = 1;
				}
			}

		}
		c++;
	}
	printf("\nPROVA:\n");
	system("pause");
	for (c = 0; c < rows; c++) {

		printf("\n%s %s %s \n", p[c].id, p[c].name, p[c].competence_area);
	}
	system("pause");
}

void infoPro(FILE *fp_pro) {
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

	fprintf(fp_pro, "%s, %s, %s, %d;\n", p.id, p.name, p.competence_area,
			p.n_sold);
}

int loadProFile() {
	int rows = 0;
	FILE *fp_pro;
	fp_pro = fopen("professionals.dat", "rb");
	checkFile(fp_pro);
	if (fp_pro != NULL) {
		rows = countRows(fp_pro);
		rewind(fp_pro);
		professionals p[rows];
		readFilePro(fp_pro, rows, p);
	}

	fclose(fp_pro);
	return -1;
}

int updProFile() {
	FILE *fp_pro;
	fp_pro = fopen("professionals.dat", "ab+");

	checkFile(fp_pro);
	if (fp_pro != NULL) {
		infoPro(fp_pro);
	}

	fclose(fp_pro);
	return -1;
}

int addPro() {
	short int choice;
	bool error = false;

	do {
		clearScr();

		newLine();

		if (error) {
			puts("Scelta non valida, per favore riprova. \n");
		}

		puts("--- PROFESSIONISTI ---");
		newLine();

		puts("Scegli un'operazione:");
		puts("1. Carica nuovo file professionisti");
		puts("2. Aggiorna file esistente");
		puts("3. Torna indietro");

		newLine();

		printf("Operazione: ");
		scanf("%hu", &choice);

		switch (choice) {
		case 1:
			choice = loadProFile();
			break;
		case 2:
			choice = updProFile();
			break;
		case 3:
			// This is used as a flag for the "go back" choice
			// It's not that likely that an user will manually insert -1 as a choice.
			choice = -2;
			error = false;
			break;
		default:
			error = true;
			break;
		}

	} while (error == true);
	return choice;
}

int editPro() {

	return -1;
}
