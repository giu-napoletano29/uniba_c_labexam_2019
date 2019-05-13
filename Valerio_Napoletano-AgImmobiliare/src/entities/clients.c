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

#include "../utils.h"
#include "../datatypes.h"
#include "../consts.h"

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
	printf("Budget in euro: %d \n", cl->budget);
	printf("Tipologia immobile da cercare: ");
	showPropertyType(cl->pr_search_type);
}

void reqID(clients *client) {
	bool error = false;

	//TODO: Validate codice fiscale.(regex + length validation?)
	do {
		printf("Codice fiscale: ");
		// "Codice fiscale" can have numbers, numCheck is false
		error = readString(client->id, false);
	} while (error == true);

	clearScr();
}

void reqName(clients *client) {
	bool error = false;

	/// NAME
	do {
		printf("Nome: ");
		error = readString(client->name, true);
	} while (error == true);

	clearScr();
}

void reqSurname(clients *client) {
	// SURNAME
	printf("Cognome: ");
	readString(client->name, true);

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
		readString(client->company_name, false);
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
			puts("Inserisci un valore in euro tra 100 e 1 000 000 000 euro. \n");
		}

		printf("Budget in euro: ");
		scanf("%d", &client->budget);

		if (client->budget < MIN_USER_BUDGET || client->cl_type > MAX_USER_BUDGET) {
			error = true;
		}
	} while (client->budget < MIN_USER_BUDGET || client->cl_type > MAX_USER_BUDGET);

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
		scanf("%u", &client->pr_search_type);

		if (client->pr_search_type < 1 || client->pr_search_type > 5) {
			error = true;
		}
	} while (client->pr_search_type < 1 || client->pr_search_type > 5);

	clearScr();
}

int addClient() {
	clients client;

	clearScr();
	newLine();

	puts("--- AGGIUNTA CLIENTE --- ");

	reqID(&client);

	reqName(&client);

	reqSurname(&client);

	reqType(&client);

	reqCompanyName(&client);

	reqBudget(&client);

	reqPropertyType(&client);

	showClientData(&client);

	return 0;
}
