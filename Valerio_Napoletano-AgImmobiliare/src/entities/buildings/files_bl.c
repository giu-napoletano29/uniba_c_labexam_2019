/**
 * @file files_bl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for handling the CSV file related to the buildings.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../../datatypes.h"
#include "../../file_utils.h"
#include "../../utils.h"

#include "show_bl.h"
#include "search_bl.h"

/**
 * @brief Parse "buildings" file
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param bl Buildings array of structs for storing parsed data.
 */
void parseBuildingsFile(FILE *filePtr, building *bl) {
	char line[MAX_TEXT_SIZE] = "";
	char *token;

	unsigned short int field = 0;
	// Buildings counter
	unsigned int builNum = 0;

	// Temp var for string to integer conversion (enum)
	unsigned short int enumTmp = 0;

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
					(bl + builNum)->id = atoi(token);
					break;
				case 1:
					strcpy((bl + builNum)->street, token);
					convertToUpperCase((bl + builNum)->street);
					break;
				case 2:
					(bl + builNum)->civic = atoi(token);
					break;
				case 3:
					strcpy((bl + builNum)->city, token);
					convertToUpperCase((bl + builNum)->city);
					break;
				case 4:
					strcpy((bl + builNum)->province, token);
					break;
				case 5:
					// Save parsed Epoch time into building struct
					(bl + builNum)->regDate = parseDate(token, false);
					break;
				case 6:
					(bl + builNum)->price = strtod(token, NULL);
					break;
				case 7:
					strcpy((bl + builNum)->owner, token);
					convertToUpperCase((bl + builNum)->owner);
					break;
				case 8:
					strcpy((bl + builNum)->phone, token);
					break;
				case 9:
					(bl + builNum)->soldOn = parseDate(token, false);

					// If parseDate failed we assume that the building is still on sale.
					if ((bl + builNum)->soldOn == -1) {
						(bl + builNum)->soldOn = 0;
					}
					break;
				case 10:
					enumTmp = atoi(token);
					(bl + builNum)->builType = enumTmp;
					break;
				case 11:
					enumTmp = atoi(token);
					(bl + builNum)->ctrType = enumTmp;
					break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		// Initialize toDelete to false
		(bl + builNum)->toDelete = false;

		builNum++;

		newLine();
	}
}

/**
 * @brief Load buildings file to memory.
 *
 * @param bl Array of structs (building datatype) where data will be stored.
 * @param filename Name of the file from which retrieving the data.
 * @return -1 for going back to the main menu.
 */
int loadBuildingsFile(building *bl, char *filename) {
	unsigned short int result = 0;
	
	FILE *filePtr;
	filePtr = fopen(filename, "a+");
	if (checkFile(filePtr)) {
		rewind(filePtr);
		parseBuildingsFile(filePtr, bl);
		result = 1;
	}

	fclose(filePtr);
	return result;
}

/**
 * @brief Replace buildings file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param bl Building array of structs where the data is stored
 * @param rows How many buildings are registered
 * @param filename Filename where data is stored
 * 
 */
int rewriteBuildingsToFile(building *bl, unsigned int rows, char *filename) {
	FILE *filePtr;
	//TODO: find a good solution to prevent data loss when file is opened in w+
	filePtr = fopen(filename, "w+");
	checkFile(filePtr);

	if (filePtr != NULL) {
		rewind(filePtr);

		for (unsigned int i = 0; i < rows; i++) {
			if (!(bl + i)->toDelete) {
				fprintf(filePtr, "%d,%s,%d,%s,%s", (bl + i)->id, (bl + i)->street, (bl + i)->civic,
						(bl + i)->city, (bl + i)->province);

				formattedDateToFile(filePtr, &(bl + i)->regDate);

				fprintf(filePtr, "%.2f,%s,%s", (bl + i)->price, (bl + i)->owner, (bl + i)->phone);

				// Save the purchase date if available, if not just save 0. (thus the building is still on sale)
				if ((bl + i)->soldOn != 0) {
					formattedDateToFile(filePtr, &(bl + i)->soldOn);
				} else {
					fprintf(filePtr, ",0,");
				}

				fprintf(filePtr, "%d,%d\n", (bl + i)->builType, (bl + i)->ctrType);
			}
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param bl Buildings array of structs where the data is stored
 * @param rows How many buildings are registered
 * @return -1 if duplicates are found.
 */
int checkDuplicateBuildings(building *bl, unsigned int rows) {
	bool result = false;
	bool error = false;
	unsigned short int choice = 0;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = i + 1; j < rows; j++) {
			if ((bl + i)->id == (bl + j)->id && !result) {
				clearScr();
				setRedColor();
				printf("\nERRORE: Il database contiene degli immobili con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- IMMOBILE 1 ---\n");
				resetColor();
				showBuildingData(bl + i);

				setCyanColor();
				printf("\n--- IMMOBILE 2 ---\n");
				resetColor();
				showBuildingData(bl + j);

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

				printf("Nuovo ID: ");
				switch (choice) {
					case 1:
						(bl + i)->id = readInteger();
						break;
					case 2:
						(bl + j)->id = readInteger();
						break;
					default:
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
		// Write on file only if needed
		rewriteBuildingsToFile(bl, rows, BUILDINGS_FNAME);
	}

	return result;
}

/**
 * @brief Append a new building to the chosen Filename
 *
 * @param filename Filename where data should be written
 * @param bl Building struct where the data is stored
 * @return -1 go back to main menu
 */
int appendBuildingToFile(building *bl, char *filename) {
	FILE *filePtr;
	filePtr = fopen(filename, "a+");
	if (checkFile(filePtr)) {
		// Save to file only if the building is not marked for deletion
		if (!bl->toDelete) {
			fprintf(filePtr, "%d,%s,%d,%s,%s", bl->id, bl->street, bl->civic, bl->city, bl->province);

			formattedDateToFile(filePtr, &bl->regDate);

			fprintf(filePtr, "%.2f,%s,%s", bl->price, bl->owner, bl->phone);

			// Save the purchase date if available, if not just save 0. (thus the building is still on sale)
			if (bl->soldOn != 0) {
				formattedDateToFile(filePtr, &(bl)->soldOn);
			} else {
				fprintf(filePtr, ",0,");
			}

			fprintf(filePtr, "%d,%d\n", bl->builType, bl->ctrType);
		}
	}

	fclose(filePtr);
	return -1;
}
