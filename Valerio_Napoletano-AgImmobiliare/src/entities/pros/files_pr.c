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
#include "req_pr.h"

/**
 * @brief Parse "professional" file (pros_potential.dat)
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 */
void readProsFile(FILE *filePtr, professional *pr) {
	char line[MAX_TEXT_SIZE];
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
void findPotential(char id[], potential *pr, int num_profess) {
	for (int i = 0; i < num_profess; i++) {
		if (strCompare(id, pr[i].id)) {
			setCyanColor();
			printf("Potenziale: ");
			resetColor();
			printf("%s \n", pr[i].content);
		}
	}
}

/**
 * @brief Parse "potential" file (potentials.dat)
 * Check out findPotential() for more information about the "potential".
 *
 * @param fp_pot Pointer to file initalized from fopen()
 * @param pr Professional array of structs for storing parsed data.
 * @param id ID of the professional connected to a specific potential record.
 * @param rows Number of professionals registered
 */
void parsePotentialsFile(FILE *fp_pot, potential *pr, char id[], int rows) {
	char line[MAX_TEXT_SIZE];
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
	findPotential(id, pr, rows);
}

/**
 * @brief Load professional.csv file to memory.
 *
 * @param pr Array of structs (professional datatype) where data will be stored.
 * @return -1 for going back to the main menu.
 */
int loadProsFile(professional *pr) {
	FILE *filePtr;
	filePtr = fopen("pros_potential.dat", "a+");
	if (checkFile(filePtr)) {
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
int getProsNumber() {
	FILE *filePtr;
	int rows = 0;
	filePtr = fopen("pros_potential.dat", "a+");
	if (checkFile(filePtr)) {
		if (filePtr != NULL) {
			rewind(filePtr);
			rows = countRows(filePtr);
		}
	}
	fclose(filePtr);
	return rows;
}

/**
 * @brief Get how many potentials are saved in the file.
 *
 * @return Number of potentials. (integer)
 */
int getPotsNumber() {
	FILE *filePtr;
	int rows = 0;
	filePtr = fopen("potentials.dat", "a+");
	if (checkFile(filePtr)) {
		if (filePtr != NULL) {
			rewind(filePtr);
			rows = countRows(filePtr);
		}
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
	fp_pot = fopen("pros_potential.dat", "a+");
	if (checkFile(fp_pot)) {
		rows = countRows(fp_pot);
		rewind(fp_pot);

		potential pr[rows];
		initPotentialsArray(pr, rows);

		parsePotentialsFile(fp_pot, pr, id, rows);
	}
	fclose(fp_pot);
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param pr Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 * @return -1 if duplicates are found.
 */
int checkDuplicatePros(professional *pr, int rows) {
	bool result = false;
	bool error = false;
	short int choice = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (strCompare(pr[i].id, pr[j].id)) {
				clearScr();
				setRedColor();
				printf("\nERRORE: Il database contiene dei professionisti con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- PROFESSIONISTA 1 ---\n");
				resetColor();
				showProData(pr + i);

				setCyanColor();
				printf("\n--- PROFESSIONISTA 2 ---\n");
				resetColor();
				showProData(pr + j);

				do {
					if (error) {
						setRedColor();
						puts("\nScelta errata.");
						resetColor();
					}

					printf("\nScegli quale immobile modificare (1/2): ");
					choice = readInteger();

					// Set error boolean to true if choice is != 2 or != 1
					error = choice == 2 || choice == 1 ? false : true;
				} while (error == true);

				newLine();

				switch (choice) {
					case 1:
						reqProCF(pr + i);
						break;
					case 2:
						reqProCF(pr + j);
						break;
				}
				i = 0;
				j = i + 1;
				result = true;
				pause();
			}
		}
	}
	rewriteProsToFile(pr, rows);
	return result;
}

/**
 * @brief Append a new professional to the "pros_potential.dat" file
 *
 * @param cl Client struct where the data is stored
 * @return -1 go back to main menu
 */
int appendProToFile(professional *pr, potential *pt) {
	FILE *clientsFilePtr, potentialsFilePtr;
	clientsFilePtr = fopen("pros_potential.dat", "a+");
	potentialsFilePtr = fopen("potentials.dat", "a+");

	if (checkFile(clientsFilePtr) && checkFile(potentialsFilePtr)) {
		// Save to file only if the client is not marked for deletion
		if (!pr->toDelete) {
			// Write professionals file
			fprintf(clientsFilePtr, "%s,%s,%s,%s,%s,%s", pr->id, pr->name, pr->surname, pr->area, pr->phone,
					pr->email);

			formattedDateToFile(clientsFilePtr, &pr->reg_date);

			fprintf(clientsFilePtr, "%d\n", pr->buildings_sold);

			// Write potentials file
			fprintf(potentialsFilePtr, "%s,%s", pt->id, pt->content);
		}
	}

	fclose(clientsFilePtr);
	fclose(potentialsFilePtr);
	return -1;
}

/**
 * @brief Replace professionals file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param pr Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 */
void rewriteProsToFile(professional *allPros, potential *allPts, int rows) {
	FILE *clientsFilePtr, *potentialsFilePtr;
	clientsFilePtr = fopen("pros_potential.dat", "w+");
	potentialsFilePtr = fopen("potentials.dat", "w+");

	if (checkFile(clientsFilePtr) && checkFile(potentialsFilePtr)) {
		rewind(clientsFilePtr);
		rewind(potentialsFilePtr);
		for (int i = 0; i < rows; i++) {
			// Write professionals file
			fprintf(clientsFilePtr, "%s,%s,%s,%s,%s,%s", allPros->id, allPros->name, allPros->surname, allPros->area, allPros->phone,
					allPros->email);

			formattedDateToFile(clientsFilePtr, &allPros->reg_date);

			fprintf(clientsFilePtr, "%d\n", allPros->buildings_sold);

			// Write potentials file
			fprintf(potentialsFilePtr, "%s,%s", allPts->id, allPts->content);
		}
	}

	fclose(clientsFilePtr);
	fclose(potentialsFilePtr);
}
