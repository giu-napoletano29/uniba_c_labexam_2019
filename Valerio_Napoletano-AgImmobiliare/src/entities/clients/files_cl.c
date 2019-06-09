/**
 * @file files_cl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for handling the CSV file related to the clients.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../../datatypes.h"
#include "../../file_utils.h"
#include "../../utils.h"
#include "../../sort.h"
#include "show_cl.h"
#include "req_cl.h" // For reqID() and reqPIVA()

/**
 * @brief Parse "clients" file (clients.dat)
 *
 * @param filePtr Pointer to file initalized from fopen()
 * @param cl Client array of structs for storing parsed data.
 */
void parseClientFile(FILE *filePtr, client *cl) {
	char line[MAX_TEXT_SIZE] = "";
	char *token;

	int field = 0;
	// Client counter
	int clientsNum = 0;

	// Temp var for string to integer conversion (enum)
	int enumTmp = 0;

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
					strcpy((cl + clientsNum)->id, token);
					break;
				case 1:
					strcpy((cl + clientsNum)->name, token);
					convertToUpperCase((cl + clientsNum)->name);
					break;
				case 2:
					strcpy((cl + clientsNum)->surname, token);
					convertToUpperCase((cl + clientsNum)->surname);
					break;
				case 3:
					enumTmp = atoi(token);
					(cl + clientsNum)->clType = enumTmp;
					break;
				case 4:
					strcpy((cl + clientsNum)->companyName, token);
					convertToUpperCase((cl + clientsNum)->companyName);
					break;
				case 5:
					(cl + clientsNum)->budget = atoi(token);
					break;
				case 6:
					/*
					 *  Save parsed Epoch time into clients struct
					 */
					(cl + clientsNum)->regDate = parseDate(token);
					break;
				case 7:
					enumTmp = atoi(token);
					(cl + clientsNum)->buildingType = enumTmp;
					break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		// Initialize toDelete to false
		(cl + clientsNum)->toDelete = false;

		clientsNum++;

		newLine();
	}
}

/**
 * @brief Replace clients file contents with the data saved in the array of structs.
 * Can be useful for deleting/update data from the file.
 *
 * @param cl Client array of structs where the data is stored
 * @param rows How many clients are registered
 * @return -1 go back to main menu
 */
int rewriteClientsToFile(client *cl, int rows) {
	FILE *filePtr;
	filePtr = fopen("clients.dat", "w+");

	// Sort clients in the memory before writing
	sortClients(cl, rows);

	if (checkFile(filePtr)) {
		for (int i = 0; i < rows; i++) {
			// Save client to file only if the client is not marked for deletion
			if (!(cl + i)->toDelete) {
				fprintf(filePtr, "%s,%s,%s,%d,%s,%d", (cl + i)->id, (cl + i)->name, (cl + i)->surname,
						(cl + i)->clType, (cl + i)->companyName, (cl + i)->budget);

				formattedDateToFile(filePtr, &(cl + i)->regDate);

				fprintf(filePtr, "%d\n", (cl + i)->buildingType);
			}
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Append a new client to the "clients.dat" file
 *
 * @param cl Client struct where the data is stored
 * @return -1 go back to main menu
 */
int appendClientToFile(client *cl) {
	FILE *filePtr;
	filePtr = fopen("clients.dat", "a+");
	if (checkFile(filePtr)) {
		// Save to file only if the client is not marked for deletion
		if (!cl->toDelete) {
			fprintf(filePtr, "%s,%s,%s,%d,%s,%d", cl->id, cl->name, cl->surname, cl->clType,
					cl->companyName, cl->budget);

			formattedDateToFile(filePtr, &cl->regDate);

			fprintf(filePtr, "%d\n", cl->buildingType);
		}
	}

	fclose(filePtr);
	return -1;
}

/**
 * @brief Load the "clients.dat" file and run the parsing function
 *
 * @param cl Array of structs (client data type) where the data will be saved.
 * @return -1 going back to the menu
 */
int loadClientFile(client *cl) {
	FILE *filePtr;
	filePtr = fopen("clients.dat", "a+");
	if (checkFile(filePtr)) {
		parseClientFile(filePtr, cl);
		fclose(filePtr);
	}
	return -1;
}

/**
 * @brief Check for duplicates in the file.
 * If so ask the user to change one of the IDs.
 *
 * @param cl Clients array of structs where the data is stored
 * @param rows How many clients are registered
 * @return true if duplicates are found.
 */
bool checkDuplicateClients(client *cl, int rows) {
	bool result = false;
	bool error = false;
	short int choice = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < rows; j++) {
			if (strCompare((cl + i)->id, (cl + j)->id)) {
				clearScr();
				setRedColor();
				printf("\nERRORE: Il database contiene degli utenti con ID identico.\n");
				resetColor();

				setCyanColor();
				printf("\n--- CLIENTE 1 ---\n");
				resetColor();
				showClientData(cl + i, false);

				setCyanColor();
				printf("\n--- CLIENTE 2 ---\n");
				resetColor();
				showClientData(cl + j, false);

				do {
					if (error) {
						setRedColor();
						puts("\nScelta errata.");
						resetColor();
					}

					printf("\nScegli quale cliente modificare (1/2): ");
					choice = readInteger();

					// Set error boolean to true if choice is != 2 or != 1
					error = choice == 2 || choice == 1 ? false : true;
				} while (error == true);

				newLine();

				switch (choice) {
					case 1:
						// If client type is "company"
						if ((cl + i)->clType == 3) {
							reqPIVA(cl + i);
						} else {
							reqCF(cl + i);
						}
						break;
					case 2:
						// If client type is "company"
						if ((cl + j)->clType == 3) {
							reqPIVA(cl + j);
						} else {
							reqCF(cl + j);
						}
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
		rewriteClientsToFile(cl, rows);
	}
	return result;
}
