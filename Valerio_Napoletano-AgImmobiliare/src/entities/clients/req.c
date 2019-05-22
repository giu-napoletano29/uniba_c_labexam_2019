/*
 * clients_req.c
 *
 *  Created on: 11 mag 2019
 *      Author: Saverio Valerio
 */

#include <stdio.h>
#include <string.h>
// Boolean (introduced in C99)
#include <stdbool.h>

#include "../../utils.h"
#include "../../datatypes.h"
#include "../../consts.h"

#include <stdlib.h>

void reqID(clients *client) {
	str_result value;
	bool error;

	do {
		if (error) {
			puts("\nInserisci un valore corretto. \n");
		}
		// Reset "error" value
		error = false;

		//TODO: Move these requests and checks to custom functions

		// Client type is "company"
		if (client->cl_type == 3) {
			printf("Partita IVA: ");
			// "VAT number" can only have numbers, numCheck is true
			// Italian PIVA is 11 digit
			// https://it.wikipedia.org/wiki/Partita_IVA
			value = readString(false);

			// Validate P.IVA length
			if (strlen(value.val) != 11) {
				error = true;
			}
		} else {
			printf("Codice fiscale: ");
			// "Codice fiscale" can have numbers, numCheck is false
			// https://it.wikipedia.org/wiki/Codice_fiscale
			value = readString(false);

			// Validate CF length
			if (strlen(value.val) != 16) {
				error = true;
			}

			//error = value.error;
		}
		strcpy(client->id, value.val);
	} while (error == true);

	clearScr();
}

void reqName(clients *client) {
	bool error = false;

	/// NAME
	do {
		printf("Nome: ");
		str_result value = readString(true);
		strcpy(client->name, value.val);
		error = value.error;
	} while (error == true);

	clearScr();
}

void reqSurname(clients *client) {
	bool error = false;

	// SURNAME
	do {
		printf("Cognome: ");
		str_result value = readString(true);
		strcpy(client->surname, value.val);
		error = value.error;
	} while (error == true);

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
		strcpy(client->company_name, readString(false).val);
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
			puts(
					"Inserisci un valore in euro tra 100 e 1 000 000 000 euro. \n");
		}

		printf("Budget in euro: ");
		client->budget = readInteger().val;

		if (client->budget < MIN_USER_BUDGET
				|| client->cl_type > MAX_USER_BUDGET) {
			error = true;
		}
	} while (client->budget < MIN_USER_BUDGET
			|| client->cl_type > MAX_USER_BUDGET);

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
		scanf("%u", &client->building_type);

		if (client->building_type < 1 || client->building_type > 5) {
			error = true;
		}
	} while (client->building_type < 1 || client->building_type > 5);

	clearScr();
}

int deleteClient() {
	clearScr();

	puts("--- ELIMINAZIONE CLIENTI --- ");

	// TODO: Add check for deleting old users (I think that one 6 months should be enough).

	// TODO: Ask for the client ID in order to delete the specific one.

	system("pause");
	return -1;
}
