/**
 * @file misc_cl.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief File containing misc functions used by the "client" entity.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // For using strcmp()
#include <time.h>
#include <stdbool.h>

#include "../../datatypes.h"
#include "../../utils.h"
#include "../../sort.h"
#include "../../file_utils.h"

#include "files_cl.h"
#include "req_cl.h"
#include "show_cl.h"
#include "misc_cl.h"

/**
 * @brief Get current system date and save the UNIX Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param cl "client" type struct
 */
void saveLocalDate(client *cl) {
	time_t timeRightNow;

	// time function returns the current Epoch time (time_t)
	cl->regDate = time(&timeRightNow);
}

/**
 * @brief Append an user to the user file.
 * Initializes a client struct and calls the "req" functions for filling the latter.
 *
 * allClients and num_clients parameters are needed
 * for calling sortClients() and rewriteClientsToFile()
 *
 * @param allClients Array of structs (client type)
 * @param num_clients Number of items (clients) saved in the array.
 * @return -1 for going back to the main menu.
 */
int addClient(client *allClients, int num_clients) {
	client cl = { "", "", "", 1, "", 0, 0, 1, false };
	int newClientsNum = 0;

	clearScr();
	printSectionName("Aggiunta cliente", false);
	newLine();

	reqName(&cl);

	reqSurname(&cl);

	reqType(&cl);

	reqID(&cl);

	reqCompanyName(&cl);

	reqBudget(&cl);

	reqPropertyType(&cl);

	saveLocalDate(&cl);

	appendClientToFile(&cl);

	/** Sort clients in the memory */
	sortClients(allClients, num_clients);

	/** - Re-declare and re-initialize the array of structs with the newly created client */
	newClientsNum = countFileRows("clients");
	client newAllClients[newClientsNum];
	initClientsArray(newAllClients, newClientsNum);

	/** - Load client file and stores the parsed data in the memory. */
	loadClientFile(newAllClients);

	/** Rewrite ordered array of structs from memory to the clients file */
	rewriteClientsToFile(newAllClients, newClientsNum);

	return -1;
}

/**
 * Delete a client identified by his ID inputted by the user.
 *
 * @param allClients Array of structs of all clients registered.
 * @param num_clients Number of clients registered.
 * @return -1 for going back to the menu
 */
int deleteClient(client *allClients, int num_clients) {
	bool found = false;

	clearScr();
	printSectionName("Eliminazione cliente", false);

	char toDeleteID[MAX_STRING_SIZE];
	printf("\nInserisci Codice Fiscale o Partita IVA del cliente da eliminare: ");
	readString(toDeleteID, false, false);

	for (int i = 0; i < num_clients; i++) {
		if (strCompare(toDeleteID, (allClients + i)->id)) {
			(allClients + i)->toDelete = true;
			found = true;
		}
	}

	if (found) {
		rewriteClientsToFile(allClients, num_clients);

		setGreenColor();
		printf("\nCliente eliminato!\n");
		resetColor();
	} else {
		setRedColor();
		printf("\nNessun cliente trovato con l'ID inserito.\n");
		resetColor();
	}
	newLine();
	pause();
	return -1;
}

/**
 * @brief Check if user expired and sets the delete flag, if the user confirms.
 *
 * @param epochTime Registration date of the user encoded in UNIX Epoch time
 * @param id Client's ID
 * @return true if user is expired, false otherwise
 */
bool checkIfUserExpired(time_t epochTime, char id[]) {
	/** Temp "tm" struct required for parsing the date properly from the file */
	struct tm tempDate = { 0 };

	/**
	 * tm_mon is defined as a range between 0 to 11.
	 * tm_year starts from 1900.
	 *
	 * @see http://www.cplusplus.com/reference/ctime/tm/
	 */
	tempDate.tm_mon -= 1;
	tempDate.tm_year -= 1900;

	bool delete = false;

	/** Calculates how many days the client registration expired. */
	int diffDays = difftime(time(NULL), epochTime) / DAY_IN_SECONDS;

	/** const.h CLIENT_EXPIRE_DAYS is 30 (days) */
	if (diffDays > CLIENT_EXPIRE_DAYS) {

		setYellowColor();
		printf("\nIl cliente risulta registrato da piu' di 30 giorni.\nVuoi eliminarlo? (s/n): ");
		resetColor();

		if (askConfirm()) {
			delete = true;

			setYellowColor();
			printf("\nCliente con ID %s pronto per l'eliminazione!\n", id);
			printf("Non chiudere il software prima dello scorrimento completo della lista.\n");
			resetColor();
			newLine();
			pause();
		}
	}

	return delete;
}

/**
 * @brief Initialize an array of structs of clients.
 *
 * @param cl "client" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initClientsArray(client *cl, int size) {
	for (int i = 0; i < size; i++) {
		strcpy((cl + i)->id, "");
		strcpy((cl + i)->name, "");
		strcpy((cl + i)->surname, "");
		(cl + i)->clType = single;
		strcpy((cl + i)->companyName, "");
		(cl + i)->budget = 0;
		(cl + i)->regDate = 0;
		(cl + i)->buildingType = flat;
		(cl + i)->toDelete = false;
	}
}
