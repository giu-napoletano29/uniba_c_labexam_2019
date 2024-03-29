/**
 * @file show_cl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief Functions for "showing" data to the user related to the clients.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // strcmp()

#include "../../utils.h"
#include "../../sort.h"
#include "../buildings/show_bl.h"
#include "files_cl.h" // rewriteClientsToFile
#include "misc_cl.h" // checkIfUserExpired()

/**
 * @brief Print out a string with the client type.
 * Check out the "clientType" in datatypes.h
 *
 * @param type Integer that represents the client type.
 */
void showClientType(unsigned short int type) {
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
 * @brief Print every field available in a client struct.
 *
 * @param cl client type struct
 * @param checkExpiration If true this function will also call checkIfUserExpired() 
 */
void showClientData(client *cl, bool checkExpiration) {
	setCyanColor();
	printf("\n-- CLIENTE --\n");
	if (cl->clType == 3) {
		printf("Partita IVA: ");
	} else {
		printf("Codice fiscale: ");
	}
	resetColor();
	printf("%s \n", cl->id);

	setCyanColor();
	printf("Nome e cognome: ");
	resetColor();
	printf("%s %s \n", cl->name, cl->surname);

	setCyanColor();
	printf("Tipo cliente: ");
	resetColor();
	showClientType(cl->clType);

	/** Show company name only if registered */
	if (cl->clType == 3) {
		setCyanColor();
		printf("Nome azienda: ");
		resetColor();
		printf("%s \n", cl->companyName);
	}

	setCyanColor();
	printf("Budget in euro: ");
	resetColor();
	printf("%d euro \n", cl->budget);

	setCyanColor();
	printf("Tipologia immobile da cercare: ");
	resetColor();
	showBuildingType(cl->buildingType);

	setCyanColor();
	printf("Data di registrazione: ");
	resetColor();
	printFormattedDate(cl->regDate);

	if (checkExpiration) {
		if (checkIfUserExpired(cl->regDate, cl->id)) {
			// Set toDelete flag
			cl->toDelete = true;
		}
	}
}

/**
 * @brief Print every client available in the array of structs.
 * Iterates on numClients calling the showClientData() function.
 *
 * @param allClients Array of structs (client type)
 * @param numClients Number of items (clients) saved in the array.
 * @return Value for returning back to the menu (-1)
 */
int showAllClients(client *allClients, unsigned int numClients) {
	bool runRewrite = false;
	bool checkExpiration = false;

	if (numClients != 0) {
		// Sort clients in the memory
		sortClients(allClients, numClients);

		// Rewrite ordered clients file
		rewriteClientsToFile(allClients, numClients, CLIENTS_FNAME);

		clearScr();
		printSectionName("Lista clienti", false);

		setYellowColor();
		printf("\nVuoi eliminare i clienti registrati da piu' di %d giorni? (quindi scaduti)\n(s/n): ",
		CLIENT_EXPIRE_DAYS);
		resetColor();
		if (askConfirm()) {
			checkExpiration = true;
		}

		for (unsigned int i = 0; i < numClients; i++) {
			showClientData((allClients + i), checkExpiration);

			// Check if some clients are ready for deletion.
			if ((allClients + i)->toDelete) {
				runRewrite = true;
			}
		}

		// Rewrite clients file without the deleted clients, if needed.
		if (runRewrite) {
			rewriteClientsToFile(allClients, numClients, CLIENTS_FNAME);
		}
		newLine();

	} else {
		dbEmptyError();
	}
	pause();
	return -1;
}
