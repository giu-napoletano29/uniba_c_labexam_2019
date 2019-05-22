/*
 * clients_misc.c
 *
 *  Created on: 22 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdlib.h>
#include <stdio.h>

// For getting local time on Windows (SYSTEMTIME struct and GetLocalTime() function)
#include <windows.h>

#include "../../utils.h"
#include "req.h"
#include "show.h"
#include "files.h"

// Get local system date and save in the related struct (only for Windows)
void saveLocalDate(clients *client) {
	// https://docs.microsoft.com/it-it/windows/desktop/api/minwinbase/ns-minwinbase-systemtime
	SYSTEMTIME t;

	// https://docs.microsoft.com/en-us/windows/desktop/api/sysinfoapi/nf-sysinfoapi-getlocaltime
	GetLocalTime(&t); // Fill out the struct so that it can be used

	// Save local system date to the struct
	client->reg_date.day = t.wDay;
	client->reg_date.month = t.wMonth;
	client->reg_date.year = t.wYear;
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

	return 0;
}
