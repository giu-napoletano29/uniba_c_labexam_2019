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
				//TODO: Complete
				// Enum - Client type
				//cl[cl_num].cl_type = token;
				cl[cl_num].cl_type = family;
				break;
			case 4:
				strcpy(cl[cl_num].company_name, token);
				break;
			case 5:
				cl[cl_num].budget = atoi(token);
				break;
			case 6:
				//TODO: Complete
				//Date
				//strcpy(cl[cl_num].date, token);
				break;
			case 7:
				//TODO: Complete
				// Enum - Building type
				//cl[cl_num].building_type = token;
				cl[cl_num].building_type = flat;
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
