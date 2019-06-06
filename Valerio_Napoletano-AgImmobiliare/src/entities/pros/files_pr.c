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
 * @brief Parse "professional" file (professionals.dat)
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param allPros Array of structs (professionals data type)
 */
void parseProsFile(FILE *filePtr, professional *allPros) {
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
					strcpy(allPros[pr_num].id, token);
					break;
				case 1:
					strcpy(allPros[pr_num].name, token);
					convertToUpperCase(allPros[pr_num].name);
					break;
				case 2:
					strcpy(allPros[pr_num].surname, token);
					convertToUpperCase(allPros[pr_num].surname);
					break;
				case 3:
					strcpy(allPros[pr_num].area, token);
					break;
				case 4:
					strcpy(allPros[pr_num].phone, token);
					break;
				case 5:
					strcpy(allPros[pr_num].email, token);
					break;
				case 6:
					/*
					 *  Save parsed Epoch time into clients struct
					 */
					allPros[pr_num].reg_date = parseDateInFile(token);
					break;
				case 7:
					allPros[pr_num].buildings_sold = atoi(token);
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
 * @brief Load professional file to memory.
 *
 * @param allPros Array of structs (professional datatype) where data will be stored.
 * @return -1 for going back to the main menu.
 */
int loadProsFile(professional *allPros) {
	FILE *prosFilePtr;

	prosFilePtr = fopen("professionals.dat", "a+");

	if (checkFile(prosFilePtr)) {
		rewind(prosFilePtr);

		parseProsFile(prosFilePtr, allPros);
	}

	fclose(prosFilePtr);
	return -1;
}

/**
 * @brief Append a new professional to the "pros_potential.dat" file
 *
 * @param pr Professional struct where the data is stored
 * @return -1 go back to main menu
 */
int appendProToFile(professional *pr) {
	FILE *filePtr;
	filePtr = fopen("professionals.dat", "a+");

	if (checkFile(filePtr)) {
		// Save to file only if the client is not marked for deletion
		if (!pr->toDelete) {
			// Write professionals file
			fprintf(filePtr, "%s,%s,%s,%s,%s,%s", pr->id, pr->name, pr->surname, pr->area, pr->phone,
					pr->email);

			formattedDateToFile(filePtr, &pr->reg_date);

			fprintf(filePtr, "%d\n", pr->buildings_sold);
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Replace professionals file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param allPros Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 */
void rewriteProsToFile(professional *allPros, int rows) {
	FILE *filePtr;
	filePtr = fopen("pros_potential.dat", "w+");

	if (checkFile(filePtr)) {
		rewind(filePtr);
		for (int i = 0; i < rows; i++) {
			// Write professionals file
			fprintf(filePtr, "%s,%s,%s,%s,%s,%s", allPros->id, allPros->name, allPros->surname, allPros->area,
					allPros->phone, allPros->email);

			formattedDateToFile(filePtr, &allPros->reg_date);

			fprintf(filePtr, "%d\n", allPros->buildings_sold);
		}
	}

	fclose(filePtr);
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param allPros Professional array of structs where the data is stored
 * @param rows How many professionals are registered
 * @return -1 if duplicates are found.
 */
int checkDuplicatePros(professional *allPros, int rows) {
	bool result = false;
	bool error = false;
	short int choice = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (strCompare(allPros[i].id, allPros[j].id)) {
				clearScr();
				setRedColor();
				printf("\nERRORE: Il database contiene dei professionisti con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- PROFESSIONISTA 1 ---\n");
				resetColor();
				showProData(allPros + i);

				setCyanColor();
				printf("\n--- PROFESSIONISTA 2 ---\n");
				resetColor();
				showProData(allPros + j);

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
						reqProCF(allPros + i);
						break;
					case 2:
						reqProCF(allPros + j);
						break;
				}
				i = 0;
				j = i + 1;
				result = true;
				pause();
			}
		}
	}
	rewriteProsToFile(allPros, rows);
	return result;
}
