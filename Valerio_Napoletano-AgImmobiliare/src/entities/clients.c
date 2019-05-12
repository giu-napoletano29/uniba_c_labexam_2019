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

int addClient() {
	clients client;
	int status = 0;

	clearScr();
	newLine();

	puts("--- AGGIUNTA CLIENTE --- ");

	//TODO: Add check if the string is consistent (should not have any numbers/symbols)
	do {
		printf("Nome: ");
		status = readString(&client.name);
	} while (status != 0);

	newLine();

	printf("Cognome: ");
	readString(&client.name);

	newLine();

	printf("Tipo: ");
	newLine();
	printf("1. Famiglia");
	newLine();
	printf("2. Single");
	newLine();
	printf("3. Azienda");
	newLine();
	printf("4. Pubblica amministrazione");

	newLine();

	do {
		newLine();
		printf("Inserisci il numero che identifica la tipologia: ");
		// %u placeholders for enums
		// "Normally, the type is unsigned int if there are no negative values in the enumeration, otherwise int."
		// http://gcc.gnu.org/onlinedocs/gcc/Structures-unions-enumerations-and-bit_002dfields-implementation.html
		scanf("%u", &client.cl_type);
	} while (client.cl_type < 1 || client.cl_type > 4);

	// Ask for the company name if the user selected the company
	if (client.cl_type == 3) {
		newLine();
		printf("Nome azienda: ");
		readString(&client.company_name);
	} else {
		strcpy(client.company_name, "");
	}

	//TODO: Maybe add another field for saving the "state" name if the user selects type 4

	newLine();

	// Limits are: 50 minimum and 1 bilion maximum (maybe needs some tuning)
	do {
		printf("Budget in euro: ");
		scanf("%d", &client.budget);
	} while (client.budget < 50 || client.cl_type > 1000000000);

	newLine();

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
		scanf("%u", &client.cl_type);
	} while (client.pr_search_type < 1 || client.pr_search_type > 5);

	// FOR TESTING

	newLine();
	printf("--- RIEPILOGO ---");
	newLine();
	newLine();
	printf("Nome: %s", client.name);
	newLine();
	printf("Cognome: %s", client.surname);
	newLine();
	printf("Tipo cliente: %d", client.cl_type);
	newLine();
	printf("Nome azienda: %s", client.company_name);
	newLine();
	printf("Budget in euro: %d", client.budget);
	newLine();
	printf("Tipologia immobile da cercare: %d", client.pr_search_type);
	newLine();
	newLine();

	return 0;
}
