/**
 * @file req_cl.c
 * @author Saverio Valerio
 * @date 1 June 2019
 * @brief Functions file containing prototypes related to the "request professionals' data" functions.
 */

#include <stdbool.h>
#include <stdio.h>
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
}
