/*
 * clients_files.c
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

void readClientFile(FILE *filePtr, clients *cl) {
	char line[400];
	char *token;

	int field;
	// Client counter
	int cl_num = 0;

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
				strcpy(cl[cl_num].id, token);
				break;
			case 1:
				strcpy(cl[cl_num].name, token);
				break;
			case 2:
				strcpy(cl[cl_num].surname, token);
				break;
			case 3:
				enum_tmp = atoi(token);
				cl[cl_num].cl_type = enum_tmp;
				break;
			case 4:
				strcpy(cl[cl_num].company_name, token);
				break;
			case 5:
				cl[cl_num].budget = atoi(token);
				break;
			case 6:
				/**
				 * Parse date in Italian format (day/month/year)
				 */
				sscanf(token, "%hu/%hu/%hu", &cl[cl_num].reg_date.day,
						&cl[cl_num].reg_date.month, &cl[cl_num].reg_date.year);
				break;
			case 7:
				enum_tmp = atoi(token);
				cl[cl_num].building_type = enum_tmp;
				break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		cl_num++;

		newLine();
	}

	showAllClients(cl, cl_num);
}

int loadClientFile() {
	int rows = 0;
	FILE *filePtr;
	filePtr = fopen("clients.csv", "a+");
	// Maybe this is not needed because the file will automatically be created
	//checkFile(filePtr);
	if (filePtr != NULL) {
		rows = countRows(filePtr);
		rewind(filePtr);
		clients cl[rows];
		readClientFile(filePtr, cl);
	}

	fclose(filePtr);
	return -1;
}
