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
#include "misc.h" /**< For checkIfUserExpired */

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

	if (checkIfUserExpired(cl->reg_date, cl->id)) {
		// Set toDelete flag
		cl->toDelete = true;
	}

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
