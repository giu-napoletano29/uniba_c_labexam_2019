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

void reqID(client *cl) {
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
		if (cl->cl_type == 3) {
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

		strcpy(cl->id, value.val);
	} while (error == true);

	clearScr();
}

void reqName(client *cl) {
	bool error = false;

	/// NAME
	do {
		printf("Nome: ");
		str_result value = readString(true);
		strcpy(cl->name, value.val);
		error = value.error;
	} while (error == true);

	clearScr();
}

void reqSurname(client *cl) {
	bool error = false;

	// SURNAME
	do {
		printf("Cognome: ");
		str_result value = readString(true);
		strcpy(cl->surname, value.val);
		error = value.error;
	} while (error == true);

	clearScr();
}

void reqType(client *cl) {
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
			notFoundError();
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		// %u placeholders for enums
		// "Normally, the type is unsigned int if there are no negative values in the enumeration, otherwise int."
		// http://gcc.gnu.org/onlinedocs/gcc/Structures-unions-enumerations-and-bit_002dfields-implementation.html
		scanf("%u", &cl->cl_type);

		if (cl->cl_type < 1 || cl->cl_type > 4) {
			error = true;
		}
	} while (cl->cl_type < 1 || cl->cl_type > 4);

	clearScr();
}

void reqCompanyName(client *cl) {
	// COMPANY NAME
	// Ask for the company name if the user selected the company
	if (cl->cl_type == 3) {
		newLine();
		printf("Nome azienda: ");
		// numCheck is false because a company name can have numbers
		strcpy(cl->company_name, readString(false).val);
	} else {
		strcpy(cl->company_name, "-");
	}

	//TODO: Maybe add another field for saving the "state" name if the user selects type 4

	clearScr();
}

void reqBudget(client *cl) {
	bool error = false;

	// BUDGET
	do {
		if (error) {
			puts(
					"Inserisci un valore in euro tra 100 e 1 000 000 000 euro. \n");
		}

		printf("Budget in euro: ");
		cl->budget = readInteger().val;

		if (cl->budget < MIN_USER_BUDGET || cl->cl_type > MAX_USER_BUDGET) {
			error = true;
		}
	} while (cl->budget < MIN_USER_BUDGET || cl->cl_type > MAX_USER_BUDGET);

	clearScr();
}

void reqPropertyType(client *cl) {
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
			notFoundError();
		}

		printf("Inserisci il numero che identifica la tipologia: ");
		scanf("%u", &cl->building_type);

		if (cl->building_type < 1 || cl->building_type > 5) {
			error = true;
		}
	} while (cl->building_type < 1 || cl->building_type > 5);

	clearScr();
}
