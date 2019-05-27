/*
 * buildings/files.c
 *
 *  Created on: 22 mag 2019
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
#include "show.h"

void readBuildingsFile(FILE *filePtr, building *bl) {
	char line[400];
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
				strcpy(bl[bl_num].id, token);
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
				/*
				 *  Save parsed Epoch time into clients struct
				 */
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

	//showAllBuildings(bl, bl_num);
}

int loadBuildingsFile(building *bl) {
	FILE *filePtr;
	filePtr = fopen("buildings.csv", "a+");
	if (!checkFile(filePtr)) {
		rewind(filePtr);
		readBuildingsFile(filePtr, bl);
	}

	fclose(filePtr);
	return -1;
}

int rewriteBuildingsToFile(building *bl, int rows) {
	FILE *filePtr;
	filePtr = fopen("buildings.csv", "w+");
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
			clDate = localtime(&bl[i].reg_date);

			// Get formatted date
			strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

			fprintf(filePtr, "%s,%s,%d,%s,%s,%s,%d,%s,%s,%d\n", bl[i].id,
					bl[i].street, bl[i].civic, bl[i].city, bl[i].province,
					dateBuffer, bl[i].price, bl[i].owner, bl[i].phone,
					bl[i].b_type);
		}
	}

	fclose(filePtr);
	return -1;
}

int checkDuplicateBuildings(building *bl, int rows) {
	short int resDup = 0;
	short int choice = 0;
	int j = 0;
	char id[STRING_SIZE];

	for (int i = 0; i < rows; i++) {
		for (j = i + 1; j < rows; j++) {
			if (strcmp(bl[i].id, bl[j].id) == 0) {
				printf("\nERRORE: ");
				printf("\nIl database contiene degli ID duplicati");
				newLine();
				printf("\n1-");
				showBuildingData(bl + i);
				printf("\n2-");
				showBuildingData(bl + j);
				newLine();

				do {
					printf("\nScegli quale record modificare (1-2): ");
					scanf("%hu", &choice);
					newLine();
					printf("Inserisci il nuovo ID: ");
					scanf("%s", id);
					convertToUpperCase(id);
					switch (choice) {
					case 1:
						strcpy(bl[i].id, id);
						break;
					case 2:
						strcpy(bl[j].id, id);
						break;
					default:
						break;
					}
				} while (choice > 2 || choice < 1);
				i = 0;
				j = i + 1;
				resDup = -1;
				system("pause");
			}
		}
	}
	rewriteBuildingsToFile(bl, rows);
	return resDup;
}

int getBuildingsNumber() {
	FILE *filePtr;
	int rows = 0;
	// Read only
	filePtr = fopen("buildings.csv", "r");
	//TODO: Makes the program crash
	//if (!checkFile(filePtr)) {
	checkFile(filePtr);
	if (filePtr != NULL) {
		rewind(filePtr);
		rows = countRows(filePtr);
	}
	fclose(filePtr);
	return rows;
}

void searchBuilding(building *bl, int n_bui) {
	short int choice = 0;
	int price = 0;
	char city[STRING_SIZE];

	puts("--- RICERCA IMMOBILI ---");
	newLine();

	puts("Scegli un'operazione:");
	puts("1. Prezzo");
	puts("2. Localita'");

	newLine();
	printf("Operazione: ");
	scanf("%hu", &choice);

	switch (choice) {
	case 1:
		printf("\ninserisci il prezzo massimo dell'immobile: ");
		scanf("%d", &price);

		for (int i = 0; i < n_bui; i++) {
			if (bl[i].price < price) {
				showBuildingData(bl + i);
			}
		}
		break;
	case 2:
		printf("\nInserisci la localita' dell'immobile: ");
		scanf("%s", city);
		convertToUpperCase(city);

		for (int i = 0; i < n_bui; i++) {
			if (strstr(bl[i].city, city) != NULL) {
				showBuildingData(bl + i);
			}
		}
		break;
	default:
		break;
	}
	system("pause");
}
