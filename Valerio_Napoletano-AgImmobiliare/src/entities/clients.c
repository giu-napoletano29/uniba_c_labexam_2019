/*
 * clients.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <string.h>
// Boolean (introduced in C99)
#include <stdbool.h>

// For getting local time on Windows (SYSTEMTIME struct and GetLocalTime() function)
#include <windows.h>

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"
#include "../file_utils.h"

#include <stdlib.h>

void readFileCli(FILE *fp_build, clients *pro) {
	char line[400];
	char *token;
	char *dtoken;
	char date[10];

	int field;
	int dfield = 0;
	// Professional nums counter
	int b_num = 0;

	while (fgets(line, sizeof line, fp_build) != NULL) /* read a line */
	{
		// Fields counter
		field = 0;

		/* Tokenize and load in the internal struct */
		// Get first token
		token = strtok(line, ",");

		while (token != NULL) {
			switch (field) {
			case 0:
				strcpy(pro[b_num].id, token);
				break;
			case 1:
				strcpy(pro[b_num].name, token);
				break;
			case 2:
				strcpy(pro[b_num].surname, token);
				break;
			case 3:
				strcpy(pro[b_num].company_name, token);
				break;
			case 4:
				pro[b_num].budget = atoi(token);
				break;
			case 5:
				strcpy(date, token);
				dfield = 0;
				dtoken = strtok(date, "/");

				while( dtoken != NULL ) {
					switch (dfield) {
					case 0:
						pro[b_num].reg_date.day = atoi(dtoken);
						break;
					case 1:
						pro[b_num].reg_date.month = atoi(dtoken);
						break;
					case 2:
						pro[b_num].reg_date.year = atoi(dtoken);
						break;
					}

				   dtoken = strtok(NULL, "/");

				   dfield++;
				}
				break;
			}

			// Read the other tokens
			token = strtok(NULL, ",");

			field++;
		}

		printf("\n--- CLIENTE %d ---\n", b_num + 1);
		printf("\nID: %s\n", pro[b_num].id);
		printf("\nNAME: %s\n", pro[b_num].name);
		printf("\nSURNAME: %s\n", pro[b_num].surname);
		printf("\nC_NAME: %s\n", pro[b_num].company_name);
		printf("\nDATE: %d/%d/%d\n", pro[b_num].reg_date.day, pro[b_num].reg_date.month, pro[b_num].reg_date.year);

		b_num++;

		newLine();
		system("pause");
	}
}

int loadCliFile() {
	int rows = 0;
	int result = 0; //detects the failure or success of the function
	FILE *fp_cli;
	fp_cli = fopen("clients.csv", "a+");
	checkFile(fp_cli);
	if (fp_cli != NULL) {
		rows = countRows(fp_cli);
		rewind(fp_cli);
		clients p[rows];
		readFileCli(fp_cli, p);
	}
	else{
		result = -1;
	}

	fclose(fp_cli);
	return result;
}


void showPropertyType(int type) {
	switch (type) {
	case 1:
		printf("Appartamento");
		break;
	case 2:
		printf("Appartamento a due piani");
		break;
	case 3:
		printf("Villa");
		break;
	case 4:
		printf("Casa di campagna");
		break;
	case 5:
		printf("Attico");
		break;
	default:
		printf("Dato non corretto");
		break;
	}

	printf("\n");
}

void showClientType(int type) {
	switch (type) {
	case 1:
		printf("Famiglia");
		break;
	case 2:
		printf("Single");
		break;
	case 3:
		printf("Azienda");
		break;
	case 4:
		printf("Pubblica amministrazione");
		break;
	default:
		printf("Dato non corretto");
		break;
	}

	printf("\n");
}

void showClientData(clients *cl) {
	puts("--- RIEPILOGO ---");
	printf("Codice fiscale: %s \n", cl->id);
	printf("Nome: %s \n", cl->name);
	printf("Cognome: %s \n", cl->surname);
	printf("Tipo cliente: ");
	showClientType(cl->cl_type);
	// Show company name only if registered
	if (cl->cl_type == 3) {
		printf("Nome azienda: %s \n", cl->company_name);
	}
	printf("Budget in euro: %d euro \n", cl->budget);
	printf("Tipologia immobile da cercare: ");
	showPropertyType(cl->building_type);
	printf("Data di registrazione: %hd/%hd/%hd \n", cl->reg_date.day,
			cl->reg_date.month, cl->reg_date.year);

	system("pause");
}

int showAllClients() {
	clearScr();
	puts("--- LISTA CLIENTI ---");

	system("PAUSE");
	return -1;
}

void reqID(clients *client) {
	str_result value;
	bool error;

	do {
		if (error) {
			puts("\nInserisci un valore corretto. \n");
		}
		// Reset "error" value
		error = false;

		//TODO: Move these requests and checks to custom functions

		// Client type is "company"
		if (client->cl_type == 3) {
			printf("Partita IVA: ");
			// "VAT number" can only have numbers, numCheck is true
			// Italian PIVA is 11 digit
			// https://it.wikipedia.org/wiki/Partita_IVA
			value = readString(false);

			// Validate P.IVA length
			if (strlen(value.val) != 11) {
				error = true;
			}
		} else {
			printf("Codice fiscale: ");
			// "Codice fiscale" can have numbers, numCheck is false
			// https://it.wikipedia.org/wiki/Codice_fiscale
			value = readString(false);

			// Validate CF length
			if (strlen(value.val) != 16) {
				error = true;
			}

			//error = value.error;
		}
		strcpy(client->id, value.val);
	} while (error == true);

	clearScr();
}

void reqName(clients *client) {
	bool error = false;

	/// NAME
	do {
		printf("Nome: ");
		str_result value = readString(true);
		strcpy(client->name, value.val);
		error = value.error;
	} while (error == true);

	clearScr();
}

void reqSurname(clients *client) {
	bool error = false;

	// SURNAME
	do {
		printf("Cognome: ");
		str_result value = readString(true);
		strcpy(client->surname, value.val);
		error = value.error;
	} while (error == true);

	clearScr();
}

void reqType(clients *client) {
	bool error = false;

	// TYPE
	puts("--- Tipo ---");
	printf("1. Famiglia \n");
	printf("2. Single \n");
	printf("3. Azienda \n");
	printf("4. Pubblica amministrazione \n");

	do {
		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		// %u placeholders for enums
		// "Normally, the type is unsigned int if there are no negative values in the enumeration, otherwise int."
		// http://gcc.gnu.org/onlinedocs/gcc/Structures-unions-enumerations-and-bit_002dfields-implementation.html
		scanf("%u", &client->cl_type);

		if (client->cl_type < 1 || client->cl_type > 4) {
			error = true;
		}
	} while (client->cl_type < 1 || client->cl_type > 4);

	clearScr();
}

void reqCompanyName(clients *client) {
	// COMPANY NAME
	// Ask for the company name if the user selected the company
	if (client->cl_type == 3) {
		newLine();
		printf("Nome azienda: ");
		// numCheck is false because a company name can have numbers
		strcpy(client->company_name, readString(false).val);
	} else {
		strcpy(client->company_name, "");
	}

	//TODO: Maybe add another field for saving the "state" name if the user selects type 4

	clearScr();
}

void reqBudget(clients *client) {
	bool error = false;

	// BUDGET
	do {
		if (error) {
			puts(
					"Inserisci un valore in euro tra 100 e 1 000 000 000 euro. \n");
		}

		printf("Budget in euro: ");
		client->budget = readInteger().val;

		if (client->budget < MIN_USER_BUDGET
				|| client->cl_type > MAX_USER_BUDGET) {
			error = true;
		}
	} while (client->budget < MIN_USER_BUDGET
			|| client->cl_type > MAX_USER_BUDGET);

	clearScr();
}

void reqPropertyType(clients *client) {
	bool error = false;

	// TYPE PROPERTY
	printf("Tipologia immobile da cercare: ");
	newLine();
	printf("1. Appartamento");
	newLine();
	printf("2. Appartamento a due piani");
	newLine();
	printf("3. Villa");
	newLine();
	printf("4. Casa di campagna");
	newLine();
	printf("5. Attico");

	newLine();

	do {
		newLine();

		if (error) {
			puts("Tipologia non trovata, per favore riprova. \n");
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		scanf("%u", &client->building_type);

		if (client->building_type < 1 || client->building_type > 5) {
			error = true;
		}
	} while (client->building_type < 1 || client->building_type > 5);

	clearScr();
}

// Get local system date and save in the related struct (only for Windows)
void saveLocalDate(clients *client) {
	// https://docs.microsoft.com/it-it/windows/desktop/api/minwinbase/ns-minwinbase-systemtime
	SYSTEMTIME t;

	// https://docs.microsoft.com/en-us/windows/desktop/api/sysinfoapi/nf-sysinfoapi-getlocaltime
	GetLocalTime(&t); // Fill out the struct so that it can be used

	// Save local system date to the struct
	client->reg_date.day = t.wDay;
	client->reg_date.month = t.wMonth;
	client->reg_date.year = t.wYear;
}

int deleteClient() {
	clearScr();

	puts("--- ELIMINAZIONE CLIENTI --- ");

	// TODO: Add check for deleting old users (I think that one 6 months should be enough).

	// TODO: Ask for the client ID in order to delete the specific one.

	system("pause");
	return -1;
}

int addClient() {
	clients client;

	clearScr();
	newLine();

	puts("--- AGGIUNTA CLIENTE --- ");

	reqName(&client);

	reqSurname(&client);

	reqType(&client);

	reqID(&client);

	reqCompanyName(&client);

	reqBudget(&client);

	reqPropertyType(&client);

	saveLocalDate(&client);

	showClientData(&client);

	return 0;
}
