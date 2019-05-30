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
#include "show_cl.h"

void parseClientFile(FILE *filePtr, client *cl) {
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
				convertToUpperCase(cl[cl_num].name);
				break;
			case 2:
				strcpy(cl[cl_num].surname, token);
				convertToUpperCase(cl[cl_num].surname);
				break;
			case 3:
				enum_tmp = atoi(token);
				cl[cl_num].cl_type = enum_tmp;
				break;
			case 4:
				strcpy(cl[cl_num].company_name, token);
				convertToUpperCase(cl[cl_num].company_name);
				break;
			case 5:
				cl[cl_num].budget = atoi(token);
				break;
			case 6:
				/*
				 *  Save parsed Epoch time into clients struct
				 */
				cl[cl_num].reg_date = parseDateInFile(token);
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
}

/*
 * Overwrite the client file with the data loaded in memory.
 * Useful for deleting a client.
 * @return success
 */
int rewriteClientsToFile(client *cl, int rows) {
	FILE *filePtr;
	filePtr = fopen("clients.csv", "w+");
	//TODO: Handle file "empty"
	//if (!checkFile(filePtr)) {
	// --- These variables are only needed if the file is available. ---

	// Buffer for printing out the date (required by strftime)
	// day/month/year (eg. 22/05/2019)
	char dateBuffer[11];

	// Pointer to time struct for handling Epoch time
	struct tm *clDate;

	for (int i = 0; i < rows; i++) {
		// Fill time struct getting date/time info from the Epoch time
		clDate = localtime(&cl[i].reg_date);

		// Get formatted date
		strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

		// Save client to file only if the client is not marked for deletion
		if (!cl[i].toDelete) {
			fprintf(filePtr, "%s,%s,%s,%d,%s,%d,%s,%d\n", cl[i].id, cl[i].name,
					cl[i].surname, cl[i].cl_type, cl[i].company_name,
					cl[i].budget, dateBuffer, cl[i].building_type);
		}
	}
	//}

	fclose(filePtr);
	return -1;
}

/*
 * Append a new client to the clients file
 * @return success
 */
int appendClientToFile(client *cl) {
	FILE *filePtr;
	filePtr = fopen("clients.csv", "a+");
	if (!checkFile(filePtr, true)) {
		// --- These variables are only needed if the file is available. ---
		// Buffer for printing out the date (required by strftime)
		// day/month/year (eg. 22/05/2019)
		char dateBuffer[11];

		// Pointer to time struct for handling Epoch time
		// Fill time struct getting date/time info from the Epoch time
		struct tm *clDate = localtime(&cl->reg_date);

		// Get formatted date
		strftime(dateBuffer, 11, "%d/%m/%Y", clDate);

		// Save to file only if the client is not marked for deletion
		if (!cl->toDelete) {
			fprintf(filePtr, "%s,%s,%s,%d,%s,%d,%s,%d\n", cl->id, cl->name,
					cl->surname, cl->cl_type, cl->company_name, cl->budget,
					dateBuffer, cl->building_type);
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * Get how many clients are saved in the file.
 * @return Number of clients. (integer)
 */
int getClientsNumber() {
	FILE *filePtr;
	int rows = 0;
	// Read only
	filePtr = fopen("clients.csv", "r");
	if (!checkFile(filePtr, true)) {
		rows = countRows(filePtr);
		fclose(filePtr);
	}
	return rows;
}

/**
 * Load "clients.csv" internal file and run the parsing function
 */
int loadClientFile(client *cl) {
	FILE *filePtr;
	// Read only
	filePtr = fopen("clients.csv", "r");
	if (!checkFile(filePtr, true)) {
		parseClientFile(filePtr, cl);
		fclose(filePtr);
	}
	return -1;
}

bool checkDuplicateClients(client *cl, int rows) {
	bool result = false;
	bool error = false;
	short int choice = 0;
	char id[STRING_SIZE];

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (strCompare(cl[i].id, cl[j].id)) {
				clearScr();
				setRedColor();
				printf(
						"\nERRORE: Il database contiene degli utenti con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- CLIENTE 1 ---\n");
				resetColor();
				showClientData(cl + i);

				setCyanColor();
				printf("\n--- CLIENTE 2 ---\n");
				resetColor();
				showClientData(cl + j);

				do {
					if (error) {
						setRedColor();
						puts("\nScelta errata.");
						resetColor();
					}

					printf("\nScegli quale cliente modificare (1/2): ");
					choice = readInteger();

					error = choice == 2 || choice == 1 ? false : true;
				} while (error == true);

				newLine();
				printf("Inserisci il nuovo ID: ");
				readString(id, false);
				convertToUpperCase(id);
				switch (choice) {
				case 1:
					strcpy(cl[i].id, id);
					break;
				case 2:
					strcpy(cl[j].id, id);
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
	rewriteClientsToFile(cl, rows);
	return result;
}