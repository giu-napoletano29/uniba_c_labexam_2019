/**
 * @file files_pr.c
 * @author Saverio Valerio
 * @date 23 May 2019
 * @brief Functions for handling the CSV file related to the professionals.
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

/**
 * @brief Parse "professional" file (professionals.csv)
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 */
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

/**
 * @brief Print potential string of a specific professional.
 * The "potential" of a pro is a simple string that explains what are his "strenghts".
 * E.g. "He's able to sell quickly houses located on the beach."
 *
 * @param id Professional's ID
 * @param pr Potentials array of structs
 * @param num_profess Number of professionals registered
 */
void findPot(char id[], potential *pr, int num_profess) {
	for (int i = 0; i < num_profess; i++) {
		if (strcmp(id, pr[i].id) == 0) {
			printf("\nPotenziale: %s\n", pr[i].content);
		}
	}
}

/**
 * @brief Parse "potential" file (potentials.csv)
 * Check out findPot() for more information about the "potential".
 *
 * @param fp_pot Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 * @param id ID of the professional connected to a specific potential record.
 * @param rows Number of professionals registered
 */
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

/**
 * @brief Load professional.csv file to memory.
 *
 * @param pr Array of structs (professional datatype) where data will be stored.
 * @return -1 for going back to the main menu.
 */
int loadProsFile(professional *pr) {
	FILE *filePtr;
	filePtr = fopen("professionals.csv", "a+");
	if (!checkFile(filePtr, true)) {
		rewind(filePtr);
		readProsFile(filePtr, pr);
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Get how many professionals are saved in the file.
 *
 * @return Number of professionals. (integer)
 */
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

/**
 * @brief Initialize potential array of structs and parse professionals' potential file.
 *
 * @param id ID of the professional connected to a specific potential record.
 */
void loadPotFile(char id[]) {
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
}

/**
 * @brief Replace professionals file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param pr Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 */
void rewriteProfessionalsToFile(professional *pr, int rows) {
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

			fprintf(filePtr, "%s,%s,%s,%s,%s,%s,%s,%d\n", pr[i].id, pr[i].name, pr[i].surname, pr[i].area,
					pr[i].phone, pr[i].email, dateBuffer, pr[i].buildings_sold);
		}
	}

	fclose(filePtr);
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param pr Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 * @return -1 if duplicates are found.
 */
int checkDuplicatePro(professional *pr, int rows) {
	short int resDup = 0;
	short int choice = 0;
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
					readString(id, false, false);
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
