/*
 * pros.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"
#include "../file_utils.h"

void readFilePro(FILE *fp_pro, professionals *pro) {
	char line[400];
	char *token;

	int field;
	// Professional nums counter
	int p_num = 0;

	while (fgets(line, sizeof line, fp_pro) != NULL) /* read a line */
	{
		// Fields counter (ID, name, etc..)
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
			case 0:
				strcpy(pro[p_num].id, token);
				break;
			case 1:
				strcpy(pro[p_num].name, token);
				break;
			case 2:
				strcpy(pro[p_num].competence_area, token);
				break;
			case 3:
				pro[p_num].buildings_sold = atoi(token);
				break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		printf("\n--- UTENTE %d ---\n", p_num + 1);
		printf("\nID: %s\n", pro[p_num].id);
		printf("\nNAME: %s\n", pro[p_num].name);
		printf("\nCOMP: %s\n", pro[p_num].competence_area);
		printf("\nSOLD: %d\n", pro[p_num].buildings_sold);

		p_num++;

		newLine();
		system("pause");
	}
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
	scanf("%d", &p.buildings_sold);

	fprintf(fp_pro, "%s,%s,%s,%d\n", p.id, p.name, p.competence_area, p.buildings_sold);
}

int loadProFile() {
	int rows = 0;
	int result = 0; //detects the failure or success of the function
	FILE *fp_pro;
	fp_pro = fopen("professionals.csv", "r");
	checkFile(fp_pro);
	if (fp_pro != NULL) {
		rows = countRows(fp_pro);
		rewind(fp_pro);
		professionals p[rows];
		readFilePro(fp_pro, p);
	}
	else{
		result = -1;
	}

	fclose(fp_pro);
	return result;
}

int updProFile() {
	FILE *fp_pro;
	fp_pro = fopen("professionals.csv", "a+");

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
