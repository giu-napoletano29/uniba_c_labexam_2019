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
#include <time.h>

#include "../../datatypes.h"
#include "../../file_utils.h"
#include "../../utils.h"
#include "misc_pr.h"
#include "show_pr.h"

void readProsFile(FILE *filePtr, professional *pr) {
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
				convertToUpperCase(pr[pr_num].name);
				break;
			case 2:
				strcpy(pr[pr_num].surname, token);
				convertToUpperCase(pr[pr_num].surname);
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
}

void findPot(char id[], potential *pr, int rows) {
	for (int i = 0; i < rows; i++) {
		if (strcmp(id, pr[i].id) == 0) {
			printf("\nPotenziale: %s\n", pr[i].content);
		}
	}
}

void readPotFile(FILE *fp_pot, potential *pr, char id[], int rows) {
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

int loadProsFile(professional *pr) {
	//int rows = 0;
	FILE *filePtr;
	filePtr = fopen("professionals.csv", "a+");
	if (!checkFile(filePtr, true)) {
		//rows = countRows(filePtr);
		rewind(filePtr);
		//professionals pr[rows];
		readProsFile(filePtr, pr);
	}

	fclose(filePtr);
	return -1;
}

int getProfessionalsNumber() {
	FILE *filePtr;
	int rows = 0;
	// Read only
	filePtr = fopen("professionals.csv", "r");
	//TODO: Makes the program crash
	//if (!checkFile(filePtr)) {
	checkFile(filePtr, true);
	if (filePtr != NULL) {
		rewind(filePtr);
		rows = countRows(filePtr);
	}
	fclose(filePtr);
	return rows;
}

int loadPotFile(char id[]) {
	int rows = 0;
	FILE *fp_pot;
	fp_pot = fopen("potential.csv", "a+");
	if (!checkFile(fp_pot, true)) {
		rows = countRows(fp_pot);
		rewind(fp_pot);

		potential pr[rows];
		initPotentialsArray(pr, rows);

		readPotFile(fp_pot, pr, id, rows);
	}
	fclose(fp_pot);
	return -1;
}

int rewriteProfessionalsToFile(professional *pr, int rows) {
	FILE *filePtr;
	filePtr = fopen("professionals.csv", "w+");
	//checkFile(filePtr);

	if (filePtr != NULL) {
		rewind(filePtr);
		// --- These variables are only needed if the file is available. ---

		// Buffer for printing out the date (required by strftime)
		// day/month/year (eg. 22/05/2019)
		char dateBuffer[11];

		// Pointer to time struct for handling Epoch time
		struct tm *clDate;

		for (int i = 0; i < rows; i++) {
			// Fill time struct getting date/time info from the Epoch time
			clDate = localtime(&pr[i].reg_date);

			// Get formatted date
			strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

			fprintf(filePtr, "%s,%s,%s,%s,%s,%s,%s,%d\n", pr[i].id, pr[i].name,
					pr[i].surname, pr[i].area, pr[i].phone, pr[i].email,
					dateBuffer, pr[i].buildings_sold);
		}
	}

	fclose(filePtr);
	return -1;
}

int checkDuplicatePro(professional *pr, int rows) {
	short int resDup = 0;
	short int choice = 0;
	//int j=0;
	char id[STRING_SIZE];

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (strcmp(pr[i].id, pr[j].id) == 0) {
				printf("\nERRORE: ");
				printf("\nIl database contiene degli ID duplicati");
				newLine();
				printf("\n1-");
				showProData(pr + i);
				printf("\n2-");
				showProData(pr + j);
				newLine();

				do {
					printf("\nScegli quale record modificare (1-2): ");
					choice = readInteger();
					newLine();
					printf("Inserisci il nuovo ID: ");
					readString(id, false);
					convertToUpperCase(id);
					switch (choice) {
					case 1:
						strcpy(pr[i].id, id);
						break;
					case 2:
						strcpy(pr[j].id, id);
						break;
					default:
						break;
					}
				} while (choice > 2 || choice < 1);
				i = 0;
				j = i + 1;
				resDup = -1;
				pause();
			}
		}
	}
	rewriteProfessionalsToFile(pr, rows);
	return resDup;
}