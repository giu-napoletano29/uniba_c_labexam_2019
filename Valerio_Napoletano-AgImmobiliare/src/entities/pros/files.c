/*
 * pros/files.c
 *
 *  Created on: 23 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../datatypes.h"
#include "../../file_utils.h"
#include "../../utils.h"
#include "show.h"

void readProsFile(FILE *filePtr, professionals *pr) {
	char line[400];
	char *token;

	int field;
	// Pros counter
	int pr_num = 0;

	while (fgets(line, sizeof line, filePtr) != NULL) /* read a line */
	{
		// Fields counter (ID, name, etc..)
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
			case 0:
				strcpy(pr[pr_num].id, token);
				break;
			case 1:
				strcpy(pr[pr_num].name, token);
				break;
			case 2:
				strcpy(pr[pr_num].surname, token);
				break;
			case 3:
				strcpy(pr[pr_num].area, token);
				break;
			case 4:
				strcpy(pr[pr_num].phone, token);
				break;
			case 5:
				strcpy(pr[pr_num].email, token);
				break;
			case 6:
				/*
				 *  Save parsed Epoch time into clients struct
				 */
				pr[pr_num].reg_date = parseDateInFile(token);
				break;
			case 7:
				pr[pr_num].buildings_sold = atoi(token);
				break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		pr_num++;

		newLine();
	}

	showAllPros(pr, pr_num);
}


void readPotFile(FILE *fp_pot, potential *pr, char id[], int rows){
	char line[400];
	char *token;

	int field;
	// Pros counter
	int pr_num = 0;

	while (fgets(line, sizeof line, fp_pot) != NULL) /* read a line */
	{
		// Fields counter (ID, name, etc..)
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
			case 0:
				strcpy(pr[pr_num].id, token);
				break;
			case 1:
				strcpy(pr[pr_num].content, token);
				break;
			}
			// Read the other tokens
			token = strtok(NULL, ",");
			field++;
		}
		pr_num++;
	}
	findPot(id, pr, rows);
}

int loadProsFile() {
	int rows = 0;
	FILE *filePtr;
	filePtr = fopen("professionals.csv", "a+");
	// Maybe this is not needed because the file will automatically be created
	checkFile(filePtr);
	if (filePtr != NULL) {
		rows = countRows(filePtr);
		rewind(filePtr);
		professionals pr[rows];
		readProsFile(filePtr, pr);
	}

	fclose(filePtr);
	return -1;
}

int loadPotFile(char id[]) {
	int rows = 0;
	FILE *fp_pot;
	fp_pot = fopen("potential.csv", "r");
	checkFile(fp_pot);
	if (fp_pot != NULL) {
		rows = countRows(fp_pot);
		rewind(fp_pot);
		potential pr[rows];
		readPotFile(fp_pot, pr, id, rows);
	}
	fclose(fp_pot);
	return -1;
}

void findPot(char id[], potential *pr, int rows){
	for(int i=0; i < rows; i++){
		if(strcmp(id, pr[i].id) == 0){
			printf("\nPotenziale: %s\n", pr[i].content);
		}
	}
}
