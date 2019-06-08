/**
 * @file req_pr.c
 * @author Saverio Valerio
 * @date 1 June 2019
 * @brief Functions file containing prototypes related to the "request professionals' data" functions.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../utils.h"

/**
 * @brief Request the Codice Fiscale to the user.
 * "Codice fiscale" has also numbers, hence onlyAlpha is false.
 *
 * @see https://it.wikipedia.org/wiki/Codice_fiscale
 * @param pr "professional" type struct
 */
void reqProCF(professional *pr) {
	bool error = false;

	do {
		if (error) {
			setYellowColor();
			puts("\nInserisci un valore corretto.\nIl codice fiscale e' composto da 16 lettere e cifre.\n");
			resetColor();
		}

		printf("Codice fiscale: ");

		/** Validate CF length */
		if (readString(pr->id, false, false) != 16) {
			error = true;
		} else {
			error = false;
		}
	} while (error == true);

	convertToUpperCase(pr->id);

	clearScr();
}

/**
 * @brief Request professional's name from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProName(professional *pr) {
	printf("Nome: ");
	readString(pr->name, true, false);
	convertToUpperCase(pr->name);

	clearScr();
}

/**
 * @brief Request professional's surname from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProSurname(professional *pr) {
	printf("Cognome: ");
	readString(pr->surname, true, false);
	convertToUpperCase(pr->surname);

	clearScr();
}

/**
 * @brief Request professional's area from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProArea(professional *pr) {
	printf("Area: ");
	readString(pr->area, true, false);

	clearScr();
}

/**
 * @brief Request professional's phone number from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProPhone(professional *pr) {
	printf("Numero di telefono: ");
	readString(pr->phone, false, false);

	clearScr();
}

/**
 * @brief Request professional's email from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProEmail(professional *pr) {
	printf("Indirizzo e-mail: ");
	readString(pr->email, false, false);

	clearScr();
}

/**
 * @brief Request professional's number of buildings sold from stdin.
 *
 * @param pr "professional" type struct
 */
void reqProSoldBuildings(professional *pr) {
	printf("Immobili venduti: ");
	pr->buildingsSold = readInteger();

	clearScr();
}

/**
 * @brief Request professional's potential stdin.
 *
 * @param pr "professional" type struct
 * @param pt "potential" type struct
 */
void reqProPotential(professional *pr, potential *pt) {
	printf("Potenziale: ");

	strcpy(pt->id, pr->id);
	readString(pt->content, false, false);

	clearScr();
}


