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

/**
 * @brief Request the company "VAT number" to the user.
 *
 * Called by reqID() only if the client type is company.
 * The Italian VAT number (Partita IVA) is 11 digits (only numbers).
 * @see https://it.wikipedia.org/wiki/Partita_IVA
 * @param cl "client" type struct
 */
void reqPIVA(client *cl) {
	bool error = false;

	do {
		if (error) {
			setYellowColor();
			puts(
					"\nInserisci un valore corretto.\nLa partita IVA e' composta da 11 cifre.\n");
			resetColor();
		}

		printf("Partita IVA: ");

		/** Validate P.IVA length */
		//TODO: Add P.IVA only numbers validation
		if (strlen(cl->id) != 11) {
			error = true;
		} else {
			error = false;
		}
	} while (error == true);
}

/**
 * @brief Request the Codice Fiscale to the user.
 *
 * Called by reqID() only if the client type is NOT company.
 * "Codice fiscale" has also numbers, hence onlyAlpha is false.
 * @see https://it.wikipedia.org/wiki/Codice_fiscale
 * @param cl "client" type struct
 */
void reqCF(client *cl) {
	bool error = false;

	do {
		if (error) {
			setYellowColor();
			puts(
					"\nInserisci un valore corretto.\nIl codice fiscale e' composto da 16 lettere e cifre.\n");
			resetColor();
		}

		printf("Codice fiscale: ");

		/** Validate CF length */
		if (readString(cl->id, false) != 16) {
			error = true;
		} else {
			error = false;
		}
	} while (error == true);
}

void reqID(client *cl) {
	if (cl->cl_type == 3) {
		reqPIVA(cl);
	} else {
		reqCF(cl);
	}
	clearScr();
}

void reqName(client *cl) {
/// NAME
	printf("Nome: ");
	readString(cl->name, true);

	clearScr();
}

void reqSurname(client *cl) {
// SURNAME
	printf("Cognome: ");
	readString(cl->surname, true);

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
		cl->cl_type = readInteger();

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
		readString(cl->company_name, false);
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
			setRedColor();
			puts(
					"Inserisci un valore in euro tra 100 e 1 000 000 000 euro. \n");
			resetColor();
		}

		printf("Budget in euro: ");
		cl->budget = readInteger();

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
		cl->building_type = readInteger();

		if (cl->building_type < 1 || cl->building_type > 5) {
			error = true;
		}
	} while (cl->building_type < 1 || cl->building_type > 5);

	clearScr();
}

