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
#include <time.h>

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

		/*
		 * Temp "tm" struct required for parsing the date properly from the file
		 */
		struct tm temp_date = { 0 };

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

				sscanf(token, "%d/%d/%d", &temp_date.tm_mday, &temp_date.tm_mon,
						&temp_date.tm_year);

				/*
				 * tm_mon is defined as a range between 0 to 11.
				 * tm_year starts from 1900.
				 *
				 * @see http://www.cplusplus.com/reference/ctime/tm/
				 */
				temp_date.tm_mon -= 1;
				temp_date.tm_year -= 1900;

				/*
				 *  Save parsed Epoch time into clients struct
				 */
				cl[cl_num].reg_date = mktime(&temp_date);

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

/*
 * Append a new client to the clients file
 * @return success
 */
int saveClientToFile(clients *cl) {
	FILE *filePtr;
	filePtr = fopen("clients.csv", "a+");
	checkFile(filePtr);
	if (filePtr != NULL) {
		// --- These variables are only needed if the file is available. ---

		// Clients counter
		int i = 0;

		// Buffer for printing out the date (required by strftime)
		// day/month/year (eg. 22/05/2019)
		char dateBuffer[11];

		// Pointer to time struct for handling Epoch time
		// Fill time struct getting date/time info from the Epoch time
		struct tm *clDate = localtime(&cl->reg_date);

		// Get formatted date
		strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

		fprintf(filePtr, "%s,%s,%s,%d,%s,%d,%s,%d\n", cl[i].id, cl[i].name,
				cl[i].surname, cl[i].cl_type, cl[i].company_name, cl[i].budget,
				dateBuffer, cl[i].building_type);
	}

	fclose(filePtr);
	return -1;
}

