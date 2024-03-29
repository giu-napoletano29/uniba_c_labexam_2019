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
 * @brief Parse "professional" file
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param allPros Array of structs (professionals data type)
 */
void parseProsFile(FILE *filePtr, professional *allPros) {
	char line[MAX_TEXT_SIZE] = "";
	char *token;

	unsigned short int field = 0;
	// Pros counter
	unsigned int proNum = 0;

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
					strcpy((allPros + proNum)->id, token);
					break;
				case 1:
					strcpy((allPros + proNum)->name, token);
					convertToUpperCase((allPros + proNum)->name);
					break;
				case 2:
					strcpy((allPros + proNum)->surname, token);
					convertToUpperCase((allPros + proNum)->surname);
					break;
				case 3:
					strcpy((allPros + proNum)->area, token);
					break;
				case 4:
					strcpy((allPros + proNum)->phone, token);
					break;
				case 5:
					strcpy((allPros + proNum)->email, token);
					convertToLowerCase((allPros + proNum)->email);
					break;
				case 6:
					/*
					 *  Save parsed Epoch time into professional struct
					 */
					(allPros + proNum)->regDate = parseDate(token, false);
					break;
				case 7:
					(allPros + proNum)->buildingsSold = atoi(token);
					break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		// Initialize toDelete to false
		(allPros + proNum)->toDelete = false;
		
		proNum++;

		newLine();
	}
}

/**
 * @brief Load professional file to memory.
 *
 * @param allPros Array of structs (professional datatype) where data will be stored.
 * @param filename Name of the file from which retrieving the data.
 * @return -1 for going back to the main menu.
 */
int loadProsFile(professional *allPros, char *filename) {
	FILE *prosFilePtr;

	prosFilePtr = fopen(filename, "a+");

	if (checkFile(prosFilePtr)) {
		rewind(prosFilePtr);

		parseProsFile(prosFilePtr, allPros);
	}

	fclose(prosFilePtr);
	return -1;
}

/**
 * @brief Append a new professional to the professionals file
 *
 * @param pr Professional struct where the data is stored
 * @param filename Filename where data should be written
 * @return -1 go back to main menu
 */
int appendProToFile(professional *pr, char *filename) {
	FILE *filePtr;
	filePtr = fopen(filename, "a+");

	if (checkFile(filePtr)) {
		// Save to file only if the client is not marked for deletion
		if (!pr->toDelete) {
			// Write professionals file
			fprintf(filePtr, "%s,%s,%s,%s,%s,%s", pr->id, pr->name, pr->surname, pr->area, pr->phone,
					pr->email);

			formattedDateToFile(filePtr, &pr->regDate);

			fprintf(filePtr, "%d\n", pr->buildingsSold);
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
 * @param filename Filename where data is storeds
 */
void rewriteProsToFile(professional *allPros, unsigned int rows, char *filename) {
	FILE *filePtr;
	filePtr = fopen(filename, "w+");

	if (checkFile(filePtr)) {
		rewind(filePtr);
		for (unsigned int i = 0; i < rows; i++) {
			// Write to file only if toDelete bool is false
			if (!(allPros + i)->toDelete) {
				fprintf(filePtr, "%s,%s,%s,%s,%s,%s", (allPros + i)->id, (allPros + i)->name,
						(allPros + i)->surname, (allPros + i)->area, (allPros + i)->phone,
						(allPros + i)->email);

				formattedDateToFile(filePtr, &(allPros + i)->regDate);

				fprintf(filePtr, "%d\n", (allPros + i)->buildingsSold);
			}
		}
	}

	fclose(filePtr);
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param allPros Array of structs where all professionals are stored
 * @param allPts Array of structs where all professionals' potentials are stored
 * @param rows How many professionals/potentials are registered
 * @return -1 if duplicates are found.
 */
int checkDuplicatePros(professional *allPros, potential *allPts, unsigned int rows) {
	bool result = false;
	bool error = false;
	short unsigned int choice = 0;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = i + 1; j < rows; j++) {
			if (strCompare((allPros + i)->id, (allPros + j)->id)) {
				clearScr();
				setRedColor();
				printf("\nERRORE: Il database contiene dei professionisti con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- PROFESSIONISTA 1 ---\n");
				resetColor();
				showProData(allPros + i, allPts, rows);

				setCyanColor();
				printf("\n--- PROFESSIONISTA 2 ---\n");
				resetColor();
				showProData((allPros + j), allPts, rows);

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

	if (result) {
		rewriteProsToFile(allPros, rows, PROS_FNAME);
	}
	return result;
}
