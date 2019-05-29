/**
 * @file show.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for "showing" data to the user related to the clients.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> /**< strcmp */

#include "../../utils.h"
#include "../buildings/show.h"
#include "misc.h" /**< For checkIfUserExpired */

/**
 * Print out a string with the client type.
 * Check out the "client_type" in datatypes.h
 *
 * @param type Integer that represents the client type.
 */
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

/**
 * Print every field available in a client struct.
 *
 * @param cl client type struct
 */
void showClientData(client *cl) {
	setCyanColor();
	printf("Codice fiscale: ");
	resetColor();
	printf("%s \n", cl->id);

	setCyanColor();
	printf("Nome: ");
	resetColor();
	printf("%s \n", cl->name);

	setCyanColor();
	printf("Cognome: ");
	resetColor();
	printf("%s \n", cl->surname);

	setCyanColor();
	printf("Tipo cliente: ");
	resetColor();
	showClientType(cl->cl_type);

	/** Show company name only if registered */
	if (cl->cl_type == 3) {
		setCyanColor();
		printf("Nome azienda: ");
		resetColor();
		printf("%s \n", cl->company_name);
	}

	setCyanColor();
	printf("Budget in euro: ");
	resetColor();
	printf("%d euro \n", cl->budget);

	setCyanColor();
	printf("Tipologia immobile da cercare: ");
	resetColor();
	showBuildingType(cl->building_type);

	setCyanColor();
	printf("Data di registrazione: ");
	resetColor();
	printFormattedDate(cl->reg_date);

	if (checkIfUserExpired(cl->reg_date, cl->id)) {
		// Set toDelete flag
		cl->toDelete = true;
	}
}

/**
 * Print every client available in the array of structs.
 * Iterates on num_clients calling the showClientData() function.
 *
 * @param cl Array of structs (building type)
 * @param num_clients Number of items (clients) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllClients(client *cl, int num_clients) {
	int i;

	clearScr();
	printSectionName("LISTA CLIENTI");

	for (i = 0; i < num_clients; i++) {
		setCyanColor();
		printf("\n-- CLIENTE %d --\n", i + 1);
		resetColor();
		showClientData(cl + i);
	}

	newLine();
	pause();
	return -1;
}
