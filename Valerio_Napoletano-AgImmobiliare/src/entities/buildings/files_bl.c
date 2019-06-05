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

/**
 * @brief Parse "buildings" file (buildings.dat)
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param bl Buildings array of structs for storing parsed data.
 */
void readBuildingsFile(FILE *filePtr, building *bl) {
	char line[MAX_TEXT_SIZE];
	char *token;

	int field;
	// Buildings counter
	int bl_num = 0;

	// Temp var for string to integer conversion (enum)
	int enum_tmp = 0;

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
					bl[bl_num].id = atoi(token);
					break;
				case 1:
					strcpy(bl[bl_num].street, token);
					break;
				case 2:
					bl[bl_num].civic = atoi(token);
					break;
				case 3:
					strcpy(bl[bl_num].city, token);
					convertToUpperCase(bl[bl_num].city);
					break;
				case 4:
					strcpy(bl[bl_num].province, token);
					break;
				case 5:
					// Save parsed Epoch time into clients struct
					bl[bl_num].reg_date = parseDateInFile(token);
					break;
				case 6:
					bl[bl_num].price = atoi(token);
					break;
				case 7:
					strcpy(bl[bl_num].owner, token);
					convertToUpperCase(bl[bl_num].owner);
					break;
				case 8:
					strcpy(bl[bl_num].phone, token);
					break;
				case 9:
					enum_tmp = atoi(token);
					bl[bl_num].b_type = enum_tmp;
					break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		bl_num++;

		newLine();
	}
}

/**
 * @brief Load buildings.dat file to memory.
 *
 * @param bl Array of structs (building datatype) where data will be stored.
 * @return -1 for going back to the main menu.
 */
int loadBuildingsFile(building *bl) {
	FILE *filePtr;
	filePtr = fopen("buildings.dat", "a+");
	if (checkFile(filePtr)) {
		rewind(filePtr);
		readBuildingsFile(filePtr, bl);
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Replace buildings file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param bl Building array of structs where the data is stored
 * @param rows How many buildings are registered
 */
int rewriteBuildingsToFile(building *bl, int rows) {
	FILE *filePtr;
	//TODO: find a good solution to prevent data loss when file is opened in w+
	filePtr = fopen("buildings.dat", "w+");
	checkFile(filePtr);

	if (filePtr != NULL) {
		rewind(filePtr);

		for (int i = 0; i < rows; i++) {
			if (!bl[i].toDelete) {
				fprintf(filePtr, "%d,%s,%d,%s,%s", bl[i].id, bl[i].street, bl[i].civic, bl[i].city,
						bl[i].province);

				formattedDateToFile(filePtr, &bl[i].reg_date);

				fprintf(filePtr, "%d,%s,%s,%d\n", bl[i].price, bl[i].owner, bl[i].phone, bl[i].b_type);
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
int checkDuplicateBuildings(building *bl, int rows) {
	bool result = false;
	bool error = false;
	short int choice = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (bl[i].id == bl[j].id) {
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
						readInteger((bl + i)->id);
						break;
					case 2:
						readInteger((bl + j)->id);
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
	rewriteBuildingsToFile(bl, rows);
	return result;
}
/**
 * @brief Get how many buildings are saved in the file.
 *
 * @return Number of buildings. (integer)
 */
int getBuildingsNumber() {
	FILE *filePtr;
	int rows = 0;
	filePtr = fopen("buildings.dat", "a+");
	if (checkFile(filePtr)) {
		rewind(filePtr);
		rows = countRows(filePtr);
	}
	fclose(filePtr);
	return rows;
}

/**
 * @brief Search for a specific building using a criteria.
 *
 * @param allBuildings Array of structs of all registered buildings.
 * @param num_buildings Number of buildings registered.
 */
int searchBuilding(building *allBuildings, int num_buildings) {
	short int choice = 0;
	bool error = false;
	// Boolean for keeping track if at least one record has been found
	bool found = false;
	int price = 0;
	char city[MAX_STRING_SIZE];

	clearScr();
	printSectionName("Ricerca immobili", false);

	if (num_buildings != 0) {
		do {
			newLine();

			puts("Scegli un'operazione:");
			puts("1. Prezzo");
			puts("2. Localita'");
			puts("3. Torna indietro");

			newLine();
			printf("Operazione: ");
			choice = readInteger();

			switch (choice) {
				case 1:
					printf("\nInserisci il prezzo massimo dell'immobile: ");
					price = readInteger();

					for (int i = 0; i < num_buildings; i++) {
						if (allBuildings[i].price < price) {
							found = true;
							showBuildingData(allBuildings + i);
						}
					}

					if (!found) {
						setYellowColor();
						printf("\nNessun record trovato.\n");
						resetColor();
					}

					pause();
					break;
				case 2:
					printf("\nInserisci la localita' dell'immobile: ");
					readString(city, false, false);
					convertToUpperCase(city);

					for (int i = 0; i < num_buildings; i++) {
						if (strstr(allBuildings[i].city, city) != NULL) {
							found = true;
							showBuildingData(allBuildings + i);
						}
					}

					if (!found) {
						setYellowColor();
						printf("\nNessun record trovato.\n");
						resetColor();
					}

					pause();
					break;
				case 3:
					// This is used as a flag for the "go back" choice
					// It's not that likely that an user will manually insert -1 as a choice.
					choice = -1;
					error = false;
					break;
				default:
					error = true;
					break;
			}
		} while (error == true);
	} else {
		dbEmptyError();
		pause();
	}

	return -1;
}

/**
 * @brief Append a new building to the "buildings.dat" file
 *
 * @param bl Building struct where the data is stored
 * @return -1 go back to main menu
 */
int appendBuildingToFile(building *bl) {
	FILE *filePtr;
	filePtr = fopen("buildings.dat", "a+");
	if (checkFile(filePtr)) {
		// Save to file only if the client is not marked for deletion
		if (!bl->toDelete) {
			fprintf(filePtr, "%d,%s,%d,%s,%s", bl->id, bl->street, bl->civic, bl->city, bl->province);

			formattedDateToFile(filePtr, &bl->reg_date);

			fprintf(filePtr, "%d,%s,%s,%d\n", bl->price, bl->owner, bl->phone, bl->b_type);
		}
	}

	fclose(filePtr);
	return -1;
}
