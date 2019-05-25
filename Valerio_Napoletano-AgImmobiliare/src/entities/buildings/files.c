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

	showAllBuildings(bl, bl_num);
}

int loadBuildingsFile() {
	int rows = 0;
	FILE *filePtr;
	filePtr = fopen("buildings.csv", "a+");
	if (!checkFile(filePtr)) {
		rows = countRows(filePtr);
		rewind(filePtr);
		building bl[rows];
		readBuildingsFile(filePtr, bl);
	}

	fclose(filePtr);
	return -1;
}
