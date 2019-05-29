/**
 * @file misc.c
 * @author Saverio Valerio
 * @date 22 May 2019
 * @brief File containing misc functions used by the "client" entity.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /**< strcmp */
#include <time.h>
#include <stdbool.h>

#include "../../datatypes.h"
#include "../../utils.h"
#include "req.h"
#include "show.h"
#include "files.h"

/**
 * Get current system date and save the Epoch time value.
 *
 * @see https://en.wikipedia.org/wiki/Unix_time
 * @param client
 */
void saveLocalDate(client *cl) {
	time_t timeRightNow;

	// time function returns the current Epoch time (time_t)
	cl->reg_date = time(&timeRightNow);
}

int addClient() {
	client cl;

	clearScr();
	newLine();

	puts("--- AGGIUNTA CLIENTE --- ");

	reqName(&cl);

	reqSurname(&cl);

	reqType(&cl);

	reqID(&cl);

	reqCompanyName(&cl);

	reqBudget(&cl);

	reqPropertyType(&cl);

	saveLocalDate(&cl);

	showClientData(&cl);

	appendClientToFile(&cl);

	return 0;
}

/**
 * Check if user expired and delete it, if the user confirms.
 */
bool checkIfUserExpired(time_t epochTime, char id[]) {
	/** Array of 2 positions for keeping the newline "\n" */
	char deleteChoice[1];

	/** Temp "tm" struct required for parsing the date properly from the file */
	struct tm temp_date = { 0 };

	/**
	 * tm_mon is defined as a range between 0 to 11.
	 * tm_year starts from 1900.
	 *
	 * @see http://www.cplusplus.com/reference/ctime/tm/
	 */
	temp_date.tm_mon -= 1;
	temp_date.tm_year -= 1900;

	/** Delete flag */
	bool delete = false;

	/** Calculate how many days the client registration expired. */
	int diffDays = difftime(time(NULL), epochTime) / DAY_IN_SECONDS;

	/** const.h CLIENT_EXPIRE_DAYS is 30 (days) */
	if (diffDays > CLIENT_EXPIRE_DAYS) {
		setYellowColor();
		printf(
				"\nIl cliente risulta registrato da piu' di 30 giorni.\nVuoi eliminarlo? (s/n): ");
		resetColor();
		scanf("%s", deleteChoice);

		if (strcmp(deleteChoice, "s") == 0 || strcmp(deleteChoice, "y") == 0) {
			delete = true;
			printf("\nUtente con ID %s in eliminazione!\n", id);
		}
	}

	return delete;
}

/**
 * Initialize an array of structs of clients.
 * @param cl "client" type struct.
 * @param size How many elements the array of struct will keep.
 */
void initClientsArray(client *cl, int size) {
	for (int i = 0; i < size; i++) {
		strcpy(cl[i].id, "");
		strcpy(cl[i].name, "");
		strcpy(cl[i].surname, "");
		cl[i].cl_type = single;
		strcpy(cl[i].company_name, "");
		cl[i].budget = 0;
		cl[i].reg_date = 0;
		cl[i].building_type = flat;
		cl[i].toDelete = false;
	}
}
