/*
 * clients_misc.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdlib.h>
#include <stdio.h>

#include <time.h>

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
void saveLocalDate(clients *client) {
	time_t timeRightNow;

	// time function returns the current Epoch time (time_t)
	client->reg_date = time(&timeRightNow);
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

	saveClientToFile(&client);

	return 0;
}
