/*
 * clients.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <string.h>

#include "../utils.h"
#include "../datatypes.h"

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
	printf("Nome: %s \n", cl->name);
	printf("Cognome: %s \n", cl->surname);
	printf("Tipo cliente: ");
	showClientType(cl->cl_type);
	// Show company name only if registered
	if (cl->cl_type == 3) {
		printf("Nome azienda: %s \n", cl->company_name);
	}
	printf("Budget in euro: %d \n", cl->budget);
	printf("Tipologia immobile da cercare: ");
	showPropertyType(cl->pr_search_type);
}

void reqName(clients *client) {
	int status = 0;

	//TODO: Add check if the string is consistent (should not have any numbers/symbols)
	/// NAME
	do {
		printf("Nome: ");
		status = readString(&client->name);
	} while (status != 0);

	clearScr();
}

void reqSurname(clients *client) {
	// SURNAME
	printf("Cognome: ");
	readString(&client->name);

	clearScr();
}

void reqType(clients *client) {
	// TYPE
	puts("--- Tipo ---");
	printf("1. Famiglia \n");
	printf("2. Single \n");
	printf("3. Azienda \n");
	printf("4. Pubblica amministrazione \n");

	do {
		newLine();
		printf("Inserisci il numero che identifica la tipologia: ");
		// %u placeholders for enums
		// "Normally, the type is unsigned int if there are no negative values in the enumeration, otherwise int."
		// http://gcc.gnu.org/onlinedocs/gcc/Structures-unions-enumerations-and-bit_002dfields-implementation.html
		scanf("%u", &client->cl_type);
	} while (client->cl_type < 1 || client->cl_type > 4);

	clearScr();
}

void reqCompanyName(clients *client) {
	// COMPANY NAME
	// Ask for the company name if the user selected the company
	if (client->cl_type == 3) {
		newLine();
		printf("Nome azienda: ");
		readString(&client->company_name);
	} else {
		strcpy(client->company_name, "");
	}

	//TODO: Maybe add another field for saving the "state" name if the user selects type 4

	clearScr();
}

void reqBudget(clients *client) {
	// BUDGET
	// Limits are: 50 minimum and 1 bilion maximum (maybe needs some tuning)
	do {
		printf("Budget in euro: ");
		scanf("%d", &client->budget);
	} while (client->budget < 50 || client->cl_type > 1000000000);

	clearScr();
}

void reqPropertyType(clients *client) {
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
		printf("Inserisci il numero che identifica la tipologia: ");
		scanf("%u", &client->pr_search_type);
	} while (client->pr_search_type < 1 || client->pr_search_type > 5);

	clearScr();
}

int addClient() {
	clients client;

	clearScr();
	newLine();

	puts("--- AGGIUNTA CLIENTE --- ");

	reqName(&client);

	reqSurname(&client);

	reqType(&client);

	reqCompanyName(&client);

	reqBudget(&client);

	reqPropertyType(&client);

	showClientData(&client);

	return 0;
}
