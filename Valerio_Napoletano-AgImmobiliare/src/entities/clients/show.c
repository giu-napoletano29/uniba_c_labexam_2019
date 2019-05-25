/*
 * clients_show.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> /**< strcmp */

#include "../../utils.h"
#include "../buildings/show.h"

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

void checkIfUserExpired(time_t epochTime, char id[]) {
	/**
	 * Array of 2 positions for keeping the newline "\n"
	 */
	char deleteChoice[1];

	/**
	 * Temp "tm" struct required for parsing the date properly from the file
	 */
	struct tm temp_date = { 0 };

	/**
	 * tm_mon is defined as a range between 0 to 11.
	 * tm_year starts from 1900.
	 *
	 * @see http://www.cplusplus.com/reference/ctime/tm/
	 */
	temp_date.tm_mon -= 1;
	temp_date.tm_year -= 1900;

	/**
	 * Calculate how many days the client registration expired.
	 */
	int diffDays = difftime(time(NULL), epochTime) / DAY_IN_SECONDS;

	/**
	 * const.h CLIENT_EXPIRE_DAYS is 30 (days)
	 */
	if (diffDays > CLIENT_EXPIRE_DAYS) {
		printf("\n\nIl cliente risulta registrato da piu' di 30 giorni.\nVuoi eliminarlo? (s/n): ");
		scanf("%s", deleteChoice);

		if (strcmp(deleteChoice, "s") == 0 || strcmp(deleteChoice, "y") == 0) {
			//TODO: Add delete client from file logic
			printf("\nUtente con ID %s eliminato! (test)\n", id);
		}
	}
}

void showClientData(clients *cl) {
	//puts("--- RIEPILOGO ---");
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
	showBuildingType(cl->building_type);

	printf("Data di registrazione: ");
	printFormattedDate(cl->reg_date);

	checkIfUserExpired(cl->reg_date, cl->id);

	newLine();
	system("pause");
}

int showAllClients(clients *cl, int num_clients) {
	int i;

	clearScr();
	puts("--- LISTA CLIENTI ---");
	for (i = 0; i < num_clients; i++) {
		printf("\n-- CLIENTE %d --\n", i + 1);
		showClientData(cl + i);
	}

	return -1;
}
